[BITS 16]
[org 0x7c00]

    push ax
    push bx
    push cx
    push dx

    mov ax, 0x0600
    mov bh, 0x7
    mov cx, 0x0
    mov dx, 0x184f
    int 0x10  

    push ax
    push bx
    push cx
    push dx
    mov ah, 0x02
    mov bh, 0x00
    mov dh, 0x0
    mov dl, 0x0
    int 0x10
    pop dx
    pop cx
    pop bx
    pop ax

    pop dx
    pop cx
    pop bx
    pop ax

    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or al,1
    mov cr0, eax
    jmp CODE_SEG:b32

[BITS 32]
print32:
    pusha
    mov edx, 0xb8000
.loop:
    mov al, [ebx]
    mov ah, 0x0f
    cmp al, 0
    je .done
    mov [edx], ax
    add ebx, 1
    add edx, 2
    jmp .loop
.done:
    popa
    ret

b32:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x2000
    mov esp, ebp

    mov ebx, msg1
    call print32
    jmp CODE_SEG:mp

mp: 
    in al,60h
    dec al
    jnz mp

    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x2000
    mov esp, ebp
    mov ebx, msg2
    call print32

    mov eax,cr0
    and al,0feh

    mov cr0,eax
    jmp short $+2

    sti
    mov ah, 4ch
    int 21h

gdt_start:

gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b    ;solo lectura, se rompe porque estoy poniendo un seg no escribible en ss
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

msg1 db 'entro modo protegido', 0
msg2 db 'salgo modo protegido', 0

[SECTION signature start=0x7dfe]
dw 0AA55h

;un programa con dos descriptores de memoria diferentes p/ c/ seg (uno p/ datos y otro p/ codigo) 
;en espacios de mem diferenciados sería como este

;en modo protegido, los regs de seg se cargan con el indice que apunta a la entrada de dicho segmento en
;la tabla de descriptores, que se obtiene cargando TI: local TI=1 global TI=1
;los ultimos 2 bits son para el RPL
;es así porque en modo protegido ya no apuntan a la base del segmento/16 sino que estan descriptos
;por un descriptor ya que las propiedades que tienen son muchas y no se pueden contener mas en 16 bits