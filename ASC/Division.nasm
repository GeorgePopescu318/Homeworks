section .text

global _start

_start:
    mov eax, 3
    mov ebx, 0
    mov ecx, a
    mov edx, 3
    int 0x80
    
    mov edx, 0
    mov eax, 0
    mov al, [a]
    sub al, '0'
    mov ebx, 0
    mov bl, [b]
    sub bl, '0'
    div ebx
    add al, '0'
    add dl, '0'
    mov [cat],al
    mov [r],dl
    mov eax, 4
    mov ebx, 1
    mov ecx, cat
    mov edx, 1
    int 0x80
    
    mov eax, 1
    int 0x80
    

section .data
    a db 0,0
    b db 0
    cat db 0,10
    r db 0