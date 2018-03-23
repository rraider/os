//
// Created by patrick on 22.03.18.
//

#include "memory.h"

void* memcpy(void* destination, const void* source, unsigned int num) {
    const char* csrc = (const char*)source;
    char* cdest = (char*)destination;

    for(unsigned int i = 0; i < num; i++) {
        cdest[i] = csrc[i];
    }
    return destination;
}

void* memmove(void* destination, const void* source, unsigned int num) {
    const char* csrc = (const char*)source;
    char* cdest = (char*)destination;

    if(source + num >= destination) {
        for(int i = num; i != 0; i--) {
            cdest[i - 1] = csrc[i - 1];
        }
    } else {
        memcpy(destination, source, num);
    }

    return destination;
}

void* memset(void* ptr, int value, unsigned int num) {
    char* cptr = (char*)ptr;
    for(unsigned int i = 0; i < num; ++i) {
        cptr[i] = (unsigned char)value;
    }
    return ptr;
}