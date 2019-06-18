/*
*  kernel.c
*/

/* --- vtconsole dependancies ----------------------------------------------- */

#define true 1
#define false 0

typedef unsigned int uint;
typedef _Bool bool;

int isdigit(int c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }

    return 0;
}

extern uint __kernel_end;
uint heap = 0;

void* malloc(uint size)
{
    uint ptr = __kernel_end + heap;
    heap+= size;
    return (void*)ptr;
}

void free(void* addr)
{
    // Do nothing
}

uint strlen(const char *str)
{
    uint lenght = 0;
    while (str[lenght])
        lenght++;
    return lenght;
}

#define min(a, b) ((a) < (b) ? (a) : (b))

#include "../sources/vtconsole.c"

/* --- vga text mode driver ------------------------------------------------- */

#define VGA_FRAME_BUFFER 0XB8000

#define VGA_SCREEN_WIDTH 80
#define VGA_SCREEN_HEIGHT 25

#define VGACOLOR_BLACK         0X0
#define VGACOLOR_BLUE          0X1
#define VGACOLOR_GREEN         0X2
#define VGACOLOR_CYAN          0X3
#define VGACOLOR_RED           0X4
#define VGACOLOR_MAGENTA       0X5
#define VGACOLOR_BROWN         0X6
#define VGACOLOR_LIGHT_GRAY    0X7
#define VGACOLOR_GRAY          0X8
#define VGACOLOR_LIGHT_BLUE    0X9
#define VGACOLOR_LIGHT_GREEN   0XA
#define VGACOLOR_LIGHT_CYAN    0XB
#define VGACOLOR_LIGHT_RED     0XC
#define VGACOLOR_LIGHT_MAGENTA 0XD
#define VGACOLOR_LIGHT_YELLOW  0XE
#define VGACOLOR_WHITE         0XF

#define VGA_COLOR(__fg, __bg) (__bg << 4 | __fg)
#define VGA_ENTRY(__c, __fg, __bg) ((((__bg) & 0XF) << 4 | ((__fg) & 0XF)) << 8 | ((__c) & 0XFF))

unsigned short *buffer = (unsigned short *)VGA_FRAME_BUFFER;

void outb(unsigned short port, char data)
{
    asm volatile("out %0,%1"
                 :
                 : "a"(data), "d"(port));
}

void vga_cell(unsigned int x, unsigned int y, unsigned short entry)
{
    if (x < VGA_SCREEN_WIDTH)
    {
        if (y < VGA_SCREEN_WIDTH)
        {
            buffer[y * VGA_SCREEN_WIDTH + x] = (unsigned short)entry;
        }
    }
}

void vga_cursor(int x, int y)
{
    unsigned short cursorLocation = y * VGA_SCREEN_WIDTH + x;

    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, (char)(cursorLocation >> 8)); // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, (char)(cursorLocation));      // Send the low cursor byte.
}

/* --- vtconsole callbacks -------------------------------------------------- */

static char colors[] =
{
    [VTCOLOR_BLACK] = VGACOLOR_BLACK,
    [VTCOLOR_RED] = VGACOLOR_RED,
    [VTCOLOR_GREEN] = VGACOLOR_GREEN,
    [VTCOLOR_YELLOW] = VGACOLOR_BROWN,
    [VTCOLOR_BLUE] = VGACOLOR_BLUE,
    [VTCOLOR_MAGENTA] = VGACOLOR_MAGENTA,
    [VTCOLOR_CYAN] = VGACOLOR_CYAN,
    [VTCOLOR_GREY] = VGACOLOR_LIGHT_GRAY,
};

static char brightcolors[] =
{
    [VTCOLOR_BLACK] = VGACOLOR_GRAY,
    [VTCOLOR_RED] = VGACOLOR_LIGHT_RED,
    [VTCOLOR_GREEN] = VGACOLOR_LIGHT_GREEN,
    [VTCOLOR_YELLOW] = VGACOLOR_LIGHT_YELLOW,
    [VTCOLOR_BLUE] = VGACOLOR_LIGHT_BLUE,
    [VTCOLOR_MAGENTA] = VGACOLOR_LIGHT_MAGENTA,
    [VTCOLOR_CYAN] = VGACOLOR_LIGHT_CYAN,
    [VTCOLOR_GREY] = VGACOLOR_WHITE,
};

void paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y)
{
    if (cell->attr.bright)
    {
        vga_cell(x, y, VGA_ENTRY(cell->c, brightcolors[cell->attr.fg], colors[cell->attr.bg]));
    }
    else
    {
        vga_cell(x, y, VGA_ENTRY(cell->c, colors[cell->attr.fg], colors[cell->attr.bg]));
    }
}

void cursor_move_callback(vtconsole_t *vtc, vtcursor_t *cur)
{
    vga_cursor(cur->x, cur->y);
}


/* --- Kernel --------------------------------------------------------------- */

vtconsole_t* vtc;

void print(const char* s)
{
    vtconsole_write(vtc, s, strlen(s));
}

void kmain(void)
{

    vtc = vtconsole(VGA_SCREEN_WIDTH, VGA_SCREEN_HEIGHT, paint_callback, cursor_move_callback);

    // Clear the screen
    print("\033[H\033[2J");

    // Simple hello world.
    // print("Hello, world!\n");

    // A neoftech like interface
    print("\033[1;34m    _____   \033[1;34muser\033[1;37m@\033[1;34mcore\n");
    print("\033[1;34m   / ____|  \033[1;37mOS:       \033[0;37mskift\n");
    print("\033[1;34m  | (___    \033[1;37mKERNEL:   \033[0;37mhjert\n");
    print("\033[1;34m   \\___ \\   \033[1;37mUPTIME:   \033[0;37m00:00\n");
    print("\033[1;34m   ____) |  \033[1;37mSHELL:    \033[0;37m/bin/sh\n");
    print("\033[1;34m  |_____/   \n");
    print("\033[1;34m            \033[1;30;40m##\033[1;41;31m##\033[1;42;32m##\033[1;43;33m##\033[1;44;34m##\033[1;45;35m##\033[1;46;36m##\033[1;47;37m##\033[0m\n");

    print("\nFAILLED\rSUCCESS\n");

	return;
}