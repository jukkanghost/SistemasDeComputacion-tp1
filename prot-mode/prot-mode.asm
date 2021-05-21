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
    int 0x10                ;se limpia la pantalla

    push ax
    push bx
    push cx
    push dx
    mov ah, 0x02
    mov bh, 0x00
    mov dh, 0x0
    mov dl, 0x0
    int 0x10                ;se vuelve el cursor al principio    
    pop dx
    pop cx
    pop bx
    pop ax

    pop dx
    pop cx
    pop bx
    pop ax

    cli                     ;desactivo interrupcions
    lgdt[gdt_descriptor]    ;cargo la gdt
    mov eax, cr0            
    or al,1
    mov cr0, eax            ;activo bit 0 del cr0
    jmp short $+2           ;vacio pipeline
    jmp CODE_SEG:b32        ;salto al codigo de 32 bits

[BITS 32]
print32:                    ;funcion para imprimir un mensaje en pantalla
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

b32:                        ;codigo que se ejecuta en modo protegido
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax              ;le aviso a los selectores que manejan datos
    mov ss, ax              ;el offset del data seg en la gdt

    mov ebp, 0x2000         ;hago espacio para la pila
    mov esp, ebp

    mov ebx, msg1           ;imprimo mensaje 1
    call print32
    jmp CODE_SEG:mp

mp: 
    in al,60h               ;espero que se pulse "esc" para poder continuar
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
    call print32            ;imprimo mensaje 2

    mov eax,cr0     
    and al,0feh
    mov cr0,eax             ;salgo de modo protegido
    jmp short $+2

    sti                     ;activo interrupciones
    mov ah, 4ch
    int 21h                 ;similar a return 0

gdt_start:

gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff               ;limit 00:15
    dw 0x0                  ;base 00:15
    db 0x0                  ;base 16:23
    db 10011010b            ;P;DPL;S;TYPE;ACCEDIDO
    db 11001111b            ;G;D/B;0;AVL;LIM 16:19
    db 0x0                  ;base 24:31

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b            ;solo lectura, se rompe porque estoy poniendo un seg no escribible en ss
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