# VT2040-keyb
Gherkin keyboard driver, created for the VT2040 terminal

## Default layout

![Default layout](layout.png)

Z and Enter function as normal shift keys, accessing the upper-case letters. The two space keys and V access three further cases, labelled in orange, purple and green respectively. In the code they're called the mega, super and ultra cases.

### Why is the layout so weird?

I first discovered the Gherkin keyboard after I got a [Unihertz Titan Pocket](https://www.unihertz.com/products/titan-pocket), and found that its 29-key keyboard was surprisingly usable once I got the Z and Enter keys working as shift keys.

The mega-case numbers and symbols match the labels on the Unihertz Titan Pocket keys, which I can't change. I don't think matching the phone keyboard is necessarily the best option here; typing numbers with one hand is possible but uncomfortable, and they're upside-down compared to a regular numeric keypad.

The super case contains all the other symbols on a "normal" keyboard, plus æ. Finally, the ultra case has the arrow keys on HJKL (I'm a vi user), and other cursor movement and Ctrl-* keys:
* **Q** Escape
* **W** Reverse-video mode
* **E** End
* **R** Rotate screen
* **T** Brightness down
* **Y** Brightness up
* **U** Delete to beginning of line
* **I** Tab
* **A** Ctrl-A
* **S** Home
* **D** Ctrl-D
* **F** Page Down
* **Z** Ctrl-Z
* **C** Ctrl-C
* **B** Page Up
