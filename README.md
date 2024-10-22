<img align="right" width="150" height="150" src="assets/logo.png">

# vtconsole
[![No Maintenance Intended](http://unmaintained.tech/badge.svg)](http://unmaintained.tech/)

**vtconsole** is an **ansi** escape code parser and renderer for hobby operating systems.

**vtconsole** alow you to add easily a rich console to your kernel.

**vtconsole** support changing color and do cursor movement.

**vtconsole** work like your traditional UNIX terminal using **ansi/vt100** escape sequences like `\033[1m`.
## 👨‍🏫 Example

### 👨‍💻 C code
```c
print("\033[1;34m    _____   \033[1;34muser\033[1;37m@\033[1;34mcore\n");
print("\033[1;34m   / ____|  \033[1;37mOS:       \033[0;37mskift\n");
print("\033[1;34m  | (___    \033[1;37mKERNEL:   \033[0;37mhjert\n");
print("\033[1;34m   \\___ \\   \033[1;37mUPTIME:   \033[0;37m00:00\n");
print("\033[1;34m   ____) |  \033[1;37mSHELL:    \033[0;37m/bin/sh\n");
print("\033[1;34m  |_____/   \n");
print("\033[1;34m            \033[1;30;40m##\033[1;41;31m##\033[1;42;32m##\033[1;43;33m##\033[1;44;34m##\033[1;45;35m##\033[1;46;36m##\033[1;47;37m##\033[0m\n");
```

### 💻 Result
![](assets/preview.png)

The kernel use for this exemple is the a barebone kernel from [Kernels 101 –
Let’s write a Kernel](https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel) located in the **exemple** directory.

## Usage
 1. Implement callbacks functions
    ```c
    /**
     * This function is call by vtconsole when a console cell update.
     * 
     * Parameters
     * ----------
     * vtc: the calling vtconsole object
     * cell: the cell being updated
     * x, y: position of the cell on the screen
     */
    void paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y)
    {
        // Your code here!
    }

    /**
     * This function is call by vtconsole when the cursor move on the screen. 
     * 
     * Parameters
     * ----------
     * vtc: the calling vtconsole object
     * vtcursor: the new state of the cursor
     */
    void cursor_move_callback(vtconsole_t *vtc, vtcursor_t *cur)
    {
        // Your code here!
    }
    ```
 2. instantiate the vtconsole_t object
    ```c
    vtc = vtconsole(SCREEN_WIDTH, SCREEN_HEIGHT, paint_callback, cursor_move_callback);
    ```
 3. Enjoy!
    ```c
    vtconsole_write(vtc, "Hello, world!", 13);
    ```
 

## ✨ Features (description from [wikipedia](https://en.wikipedia.org/wiki/ANSI_escape_code))

- `\033[n;mH` CUP – Cursor Position
  >Moves the cursor to row n, column m. The values are 1-based, and default to 1 (top left corner) if omitted. A sequence such as CSI ;5H is a synonym for CSI 1;5H as well as CSI 17;H is the same as CSI 17H and CSI 17;1H
- `\033[nJ` ED – Erase in Display
    > Clears part of the screen. If n is 0 (or missing), clear from cursor to end of screen. If n is 1, clear from cursor to beginning of the screen. If n is 2, clear entire screen.
- `\033[nK` EL – Erase in Line
    > Erases part of the line. If n is 0 (or missing), clear from cursor to the end of the line. If n is 1, clear from cursor to beginning of the line. If n is 2, clear entire line. Cursor position does not change.
- `\033[nm` SGR – Select Graphic Rendition
    > Sets the appearance of the following characters, see SGR parameters below.

## Supported SGR parameters

| code  | effet                             |
| ----- | --------------------------------- |
| 0     | Reset / Normal	all attributes off |
| 1     | Bold or increased intensity       |
| 30–37 | Set foreground color              |
| 40–47 | Set background color              |

## 🎨 Supported Colors

| name    | id  | color                                              |
| ------- | --- | -------------------------------------------------- |
| Black   | 0   | ![#000](https://placehold.it/15/000/000000?text=+) |
| Red     | 1   | ![#000](https://placehold.it/15/f00/000000?text=+) |
| Green   | 2   | ![#000](https://placehold.it/15/0f0/000000?text=+) |
| Yellow  | 3   | ![#000](https://placehold.it/15/ff0/000000?text=+) |
| Blue    | 4   | ![#000](https://placehold.it/15/00f/000000?text=+) |
| Magenta | 5   | ![#000](https://placehold.it/15/f0f/000000?text=+) |
| Cyan    | 6   | ![#000](https://placehold.it/15/0ff/000000?text=+) |
| White   | 7   | ![#fff](https://placehold.it/15/fff/000000?text=+) |

## 👐 Contributing
Feel free to open an issue or a pull request if you would like to contribute or ask a question.

## ✌ Thanks

- To [https://github.com/64/cansid](https://github.com/64/cansid) which this project was originaly based on
