//
// Created by patrick on 22.03.18.
//

#ifndef OS_MEMORY_H
#define OS_MEMORY_H
void* memcpy(void* destination, const void* source, unsigned int num);
void* memmove(void* destination, const void* source, unsigned int num);
void* memset(void* ptr, int value, unsigned int num);
#endif //OS_MEMORY_H
