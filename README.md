<img align="right" width="150" height="150" src="assets/logo.png">

# vtconsole
A **ansi** escape code parser and renderer for hobby operating systems.

## Features (description from [wikipedia](https://en.wikipedia.org/wiki/ANSI_escape_code))

- CSI sequences `\033[`
- `CSI n ; m H` CUP – Cursor Position
  >Moves the cursor to row n, column m. The values are 1-based, and default to 1 (top left corner) if omitted. A sequence such as CSI ;5H is a synonym for CSI 1;5H as well as CSI 17;H is the same as CSI 17H and CSI 17;1H
- `CSI n J` ED – Erase in Display
    > Clears part of the screen. If n is 0 (or missing), clear from cursor to end of screen. If n is 1, clear from cursor to beginning of the screen. If n is 2, clear entire screen (and moves cursor to upper left on DOS ANSI.SYS). If n is 3, clear entire screen and delete all lines saved in the scrollback buffer (this feature was added for xterm and is supported by other terminal applications).
- `CSI n K` EL – Erase in Line
    > Erases part of the line. If n is 0 (or missing), clear from cursor to the end of the line. If n is 1, clear from cursor to beginning of the line. If n is 2, clear entire line. Cursor position does not change.
- `CSI n m` SGR – Select Graphic Rendition
    > Sets the appearance of the following characters, see SGR parameters below.

## Supported SGR parameters

| code  | effet                             |
| ----- | --------------------------------- |
| 0     | Reset / Normal	all attributes off |
| 1     | Bold or increased intensity       |
| 30–37 | Set foreground color              |
| 40–47 | Set background color              |

## Supported Colors

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