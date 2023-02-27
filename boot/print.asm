[bits 16]
print:
    pusha

start:
    mov al, [bx] ; bx is base address for string
    cmp al, 0
    je done

    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp start

done:
    popa
    ret

print_nl:
    pusha
    mov ah, 0x0e
    mov al, 0x0a ; nl char
    int 0x10
    mov al, 0x0d ; cr char
    int 0x10

    popa
    ret