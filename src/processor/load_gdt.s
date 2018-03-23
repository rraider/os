global load_gdt

;segment .data

gdt:
.null:
    dq 0
.code:
    dw 0xffff
    dw 0
    db 0
    db 0x9a
    db 11001111b
    db 0
.data:
    dw 0xffff
    dw 0
    db 0
    db 0x92
    db 11001111b
    db 0
.end:

gdtr:
    .limit:
    dw 24
    .base:
    dd gdt


segment .text

load_gdt:
    lgdt [gdtr]
    jmp 0x08:flush_gdt

flush_gdt:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret