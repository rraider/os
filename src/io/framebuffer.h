#ifndef OS_FRAMEBUFFER_H
#define OS_FRAMEBUFFER_H
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_move_cursor(unsigned short pos);
void scroll(unsigned int lines);

int putchar(int character);
int puts(const char* str);
int puthex(int num);
#endif //OS_FRAMEBUFFER_H
