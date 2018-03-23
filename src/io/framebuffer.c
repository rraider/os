#include "framebuffer.h"
#include "io.h"
#include "../memory.h"

unsigned int current_cell = 0;
unsigned char current_fg = 15;
unsigned char current_bg = 0;
short * const fb = (short*)0x000B8000;

const unsigned short FB_COMMAND_PORT = 0x3D4;
const unsigned short FB_DATA_PORT = 0x3D5;
const unsigned char FB_HIGH_COMMAND = 14;
const unsigned char FB_LOW_COMMAND = 15;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = (short)((bg & 0x7) << 12 | (fg & 0xF) << 8 | c);
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_COMMAND);
    outb(FB_DATA_PORT, (unsigned char)(((pos & 0xFF00) >> 8) & 0xFF));
    outb(FB_COMMAND_PORT, FB_LOW_COMMAND);
    outb(FB_DATA_PORT, (unsigned char)(pos & 0xFF));
}

int putchar(int character) {
    fb_write_cell(current_cell++, (char)(character & 0xFF), current_fg, current_bg);
    fb_move_cursor((short)current_cell);
    return character;
}

int puts(const char* str) {
    while(*str) {
        if(*str == '\n') {
            current_cell = ((current_cell / 80) + 1) * 80;
        } else {
            fb_write_cell(current_cell++, *str, current_fg, current_bg);
        }

        if(current_cell > 80*25) {
            scroll(5);
        }
        ++str;
    }
    fb_move_cursor((short)current_cell);
    return 1;
}

void scroll(unsigned int lines) {
    memcpy(fb, fb + 80*lines, 80*(25-lines)*2);
    current_cell -= lines*80;
    for(short* fbptr = fb + current_cell; fbptr < fb + 80*25; ++fbptr) {
        *fbptr = (short)((current_bg & 0x7) << 12 | (current_fg & 0xF) << 8 | ' ');
    }
}

int puthex(int num) {
    static const char lookup[] = "0123456789ABCDEF";
    puts("0x");
    putchar(lookup[(num >> 28) & 0xF]);
    putchar(lookup[(num >> 24) & 0xF]);
    putchar(lookup[(num >> 20) & 0xF]);
    putchar(lookup[(num >> 16) & 0xF]);
    putchar(lookup[(num >> 12) & 0xF]);
    putchar(lookup[(num >> 8) & 0xF]);
    putchar(lookup[(num >> 4) & 0xF]);
    putchar(lookup[(num >> 0) & 0xF]);
    return num;
}