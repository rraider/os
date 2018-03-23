//
// Created by patrick on 22.03.18.
//

#include "interrupts.h"
#include "../memory.h"
#include "load_idt.h"
#include "../io/io.h"
#include "../io/framebuffer.h"
#include "interrupt_handlers.h"

struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
}__attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
}__attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtr;

struct cpu_state
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void irq_remap() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}

void pic_acknowledge(unsigned int interrupt) {
    if (interrupt < 0x20 || interrupt > 0x28 + 7) {
        return;
    }

    if (interrupt >= 0x28) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}

void sti() {
    asm volatile ( "sti" );
}

void cli() {
    asm volatile ("cli");
}

void setup_interrupts() {
    idtr.limit = (6 * 256) - 1;
    idtr.base = (unsigned int) &idt;

    memset(idt, 0, sizeof(struct idt_entry) * 256);

    load_idt(&idtr);

    irq_remap();
    idt_set_gate(0, (unsigned int) &interrupt_handler_0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned int) &interrupt_handler_1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned int) &interrupt_handler_2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned int) &interrupt_handler_3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned int) &interrupt_handler_4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned int) &interrupt_handler_5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned int) &interrupt_handler_6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned int) &interrupt_handler_7, 0x08, 0x8E);
    idt_set_gate(8, (unsigned int) &interrupt_handler_8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned int) &interrupt_handler_9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned int) &interrupt_handler_10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned int) &interrupt_handler_11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned int) &interrupt_handler_12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned int) &interrupt_handler_13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned int) &interrupt_handler_14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned int) &interrupt_handler_15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned int) &interrupt_handler_16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned int) &interrupt_handler_17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned int) &interrupt_handler_18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned int) &interrupt_handler_19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned int) &interrupt_handler_20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned int) &interrupt_handler_21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned int) &interrupt_handler_22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned int) &interrupt_handler_23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned int) &interrupt_handler_24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned int) &interrupt_handler_25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned int) &interrupt_handler_26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned int) &interrupt_handler_27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned int) &interrupt_handler_28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned int) &interrupt_handler_29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned int) &interrupt_handler_30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned int) &interrupt_handler_31, 0x08, 0x8E);
    idt_set_gate(32, (unsigned int) &interrupt_handler_32, 0x08, 0x8E);
    idt_set_gate(33, (unsigned int) &interrupt_handler_33, 0x08, 0x8E);
    idt_set_gate(34, (unsigned int) &interrupt_handler_34, 0x08, 0x8E);
    idt_set_gate(35, (unsigned int) &interrupt_handler_35, 0x08, 0x8E);
    idt_set_gate(36, (unsigned int) &interrupt_handler_36, 0x08, 0x8E);
    idt_set_gate(37, (unsigned int) &interrupt_handler_37, 0x08, 0x8E);
    idt_set_gate(38, (unsigned int) &interrupt_handler_38, 0x08, 0x8E);
    idt_set_gate(39, (unsigned int) &interrupt_handler_39, 0x08, 0x8E);
    idt_set_gate(40, (unsigned int) &interrupt_handler_40, 0x08, 0x8E);
    idt_set_gate(41, (unsigned int) &interrupt_handler_41, 0x08, 0x8E);
    idt_set_gate(42, (unsigned int) &interrupt_handler_42, 0x08, 0x8E);
    idt_set_gate(43, (unsigned int) &interrupt_handler_43, 0x08, 0x8E);
    idt_set_gate(44, (unsigned int) &interrupt_handler_44, 0x08, 0x8E);
    idt_set_gate(45, (unsigned int) &interrupt_handler_45, 0x08, 0x8E);
    idt_set_gate(46, (unsigned int) &interrupt_handler_46, 0x08, 0x8E);
    idt_set_gate(47, (unsigned int) &interrupt_handler_47, 0x08, 0x8E);

    // mask interrupts
    outb(0x21, 0xFD);
    outb(0xA1, 0xFF);

    sti();
}

void interrupt_handler(struct cpu_state *state) {
    puthex(state->int_no);
    puts("\n");
    pic_acknowledge(state->int_no);
}