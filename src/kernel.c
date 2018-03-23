//
// Created by patrick on 22.03.18.
//

#include "kernel.h"
#include "io/framebuffer.h"
#include "processor/load_gdt.h"
#include "processor/interrupts.h"

void kernel_main() {
    cli();
    puts("Loading GDT\n");
    load_gdt();
    puts("GDT loaded\n");
    puts("Loading IDT\n");
    setup_interrupts();
    puts("IDT set up\n");
}

