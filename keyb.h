// Keyboard row and column pins
// On Gherkin keyboard these don't correspond to physical rows and columns
#define KEYB_PIN_R1 7
#define KEYB_PIN_R2 6
#define KEYB_PIN_R3 5
#define KEYB_PIN_R4 4
#define KEYB_PIN_R5 3
#define KEYB_PIN_C1 29
#define KEYB_PIN_C2 28
#define KEYB_PIN_C3 27
#define KEYB_PIN_C4 26
#define KEYB_PIN_C5 15
#define KEYB_PIN_C6 14

// Timing thresholds (in ms)
#define KEYB_MS_DEBOUNCE 10
#define KEYB_MS_DELAY 600 // Key repeat initial delay
#define KEYB_MS_REPEAT 84 // Key repeat time
#define KEYB_MS_CANCEL 200 // If shift key is held down for this long
                           // without pressing another key, don't do
                           // anything when it is released

// Special keycodes
#define KEYB_KC_INVERT 0xe100
#define KEYB_KC_ROTATE 0xe101
#define KEYB_KC_DARKEN 0xe102
#define KEYB_KC_BRIGHTEN 0xe103

// Keymaps
// 30 keys each, left-to-right, top-to-bottom, keycodes are Unicode
// See term.h for keycodes 0xe000-0xe0ff

#define KEYB_CASE_LOWER L"qwertyuiopasdfghjkl\x8zxcv  bnm\r"

#define KEYB_SHIFT_UPPER 20 // Z
#define KEYB_MS_UPPER 80 // Only shift if held for 80ms
#define KEYB_CASE_UPPER L"QWERTYUIOPASDFGHJKL\x8ZXCV  BNM\r"

#define KEYB_SHIFT_SUPER 24 // Left space
#define KEYB_MS_SUPER 80
#define KEYB_CASE_SUPER L"0123()-_/:@456*#+\"'\x08!789  .,?\r"

#define KEYB_SHIFT_HYPER 25 // Right space
#define KEYB_MS_HYPER 200 // Longer to avoid accidental presses
#define KEYB_CASE_HYPER L"\x1b\xe100\xe007\xe101\xe102\xe103\x15\x9\0\0\x1\xe006\x4\xe005\0\xe003\xe001\xe000\xe002\x8\x1a\0\x3\0\0\0\xe004\0\0\r"

#define KEYB_SHIFT_ULTRA 23 // V
#define KEYB_MS_ULTRA 80
#define KEYB_CASE_ULTRA L"\xb0""1\xe6\xa3[]{}\\;@$%^*~=\"`\x8|&89  <>?\r"

#define KEYB_SHIFT_EXTRA 29 // Enter
#define KEYB_MS_EXTRA 80
#define KEYB_CASE_EXTRA KEYB_CASE_UPPER

void keyb_init();
int32_t keyb_scan();
