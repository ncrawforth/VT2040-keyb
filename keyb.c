#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "keyb.h"

int cols[] = {KEYB_PIN_C1, KEYB_PIN_C2, KEYB_PIN_C3, KEYB_PIN_C4, KEYB_PIN_C5, KEYB_PIN_C6};
int colc = 6;
int rows[] = {KEYB_PIN_R1, KEYB_PIN_R2, KEYB_PIN_R3, KEYB_PIN_R4, KEYB_PIN_R5};
int rowc = 5;

int shifts[] = {KEYB_SHIFT_UPPER, KEYB_SHIFT_HYPER, KEYB_SHIFT_MEGA, KEYB_SHIFT_SUPER, KEYB_SHIFT_ULTRA, KEYB_SHIFT_EXTRA};
int shift_mses[] = {KEYB_MS_UPPER, KEYB_MS_HYPER, KEYB_MS_MEGA, KEYB_MS_SUPER, KEYB_MS_ULTRA, KEYB_MS_EXTRA};
int shiftc = 6;
int key_mses[30];
int keyc = 30;
int shift = -1;
int shift_ms = KEYB_MS_DEBOUNCE;

int32_t map_key(int key, int shift) {
  switch (shift) {
    case KEYB_SHIFT_UPPER:
      return (KEYB_CASE_UPPER)[key];
    case KEYB_SHIFT_HYPER:
      return (KEYB_CASE_HYPER)[key];
    case KEYB_SHIFT_MEGA:
      return (KEYB_CASE_MEGA)[key];
    case KEYB_SHIFT_SUPER:
      return (KEYB_CASE_SUPER)[key];
    case KEYB_SHIFT_ULTRA:
      return (KEYB_CASE_ULTRA)[key];
    case KEYB_SHIFT_EXTRA:
      return (KEYB_CASE_EXTRA)[key];
    default:
      return (KEYB_CASE_LOWER)[key];
  }
}

int32_t process_keys() {
  if (shift == -1) {
    for (int i = 0; i < shiftc; i++) {
      if (key_mses[shifts[i]] == KEYB_MS_DEBOUNCE) {
        shift = shifts[i];
        shift_ms = shift_mses[i];
        break;
      }
    }
  } else if (key_mses[shift] < 0) { // Shift key released
    int key = shift;
    int key_ms = -key_mses[key];
    for (int i = 0; i < keyc; i++) {
      if (key_mses[i] > KEYB_MS_DEBOUNCE - 1 && key_mses[i] <= shift_ms) {
        key_mses[i] = KEYB_MS_DEBOUNCE - 1; // Ensure other keys register
      }
    }
    shift = -1;
    shift_ms = KEYB_MS_DEBOUNCE;
    key_mses[key] = 0;
    if (key_ms < KEYB_MS_CANCEL) { // Perform shift key tap action
      return map_key(key, 0);
    }
  }
  for (int key = 0; key < keyc; key++) {
    if (shift == -1 || key != shift) {
      int key_ms = key_mses[key];
      if (key_ms < 0) { // Key released
        key_ms = -key_ms;
        key_mses[key] = 0;
        if (key_ms > KEYB_MS_DEBOUNCE && key_ms < shift_ms) { // Key was tapped
          if (shift != -1) {
            key_mses[shift] = KEYB_MS_CANCEL; // Cancel shift key tap action
          }
          return map_key(key, shift);
        }
        key_mses[key] = 0;
      } else {
        if (key_mses[key] == shift_ms || (key_mses[key] > (shift_ms + KEYB_MS_DELAY) && key_mses[key] % KEYB_MS_REPEAT == 0)) {
          if (shift != -1) {
            key_mses[shift] = KEYB_MS_CANCEL; // Cancel the shift key tap action
          }
          return map_key(key, shift);
        }
      }
    }
  }
  return 0;
}

void keyb_init() {
  for (int c = 0; c < colc; c++) {
    gpio_init(cols[c]);
    gpio_set_dir(cols[c], GPIO_OUT);
  }
  for (int r = 0; r < rowc; r++) {
    gpio_init(rows[r]);
    gpio_set_dir(rows[r], GPIO_IN);
    gpio_pull_down(rows[r]);
  }
}

int32_t keyb_scan() {
  for (int c = 0; c < colc; c++) {
    gpio_put(cols[c], 1);
    sleep_us(1);
    for (int r = 0; r < rowc; r++) {
      int key = r * colc + c;
      if (key_mses[key] >= 0) {
        if (gpio_get(rows[r])) {
          key_mses[key]++;
        } else {
          key_mses[key] = 0 - key_mses[key];
        }
      }
    }
    gpio_put(cols[c], 0);
  }
  return process_keys();
}
