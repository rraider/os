//
// Created by patrick on 23.03.18.
//

#include "keyboard.h"
#include "io.h"

unsigned char read_scan_code() {
    return inb(0x60);
}