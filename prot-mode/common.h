.altmacro

/* Helpers */

/* Push registers ax, bx, cx and dx. Lightweight `pusha`. */
.macro PUSH_ADX
    push %ax
    push %bx
    push %cx
    push %dx
.endm

/* Pop registers dx, cx, bx, ax. Inverse order from PUSH_ADX,
 * so this cancels that one.
 */
.macro POP_DAX
    pop %dx
    pop %cx
    pop %bx
    pop %ax
.endm

.macro PUSH_EADX
    push %eax
    push %ebx
    push %ecx
    push %edx
.endm

.macro POP_EDAX
    pop %edx
    pop %ecx
    pop %ebx
    pop %eax
.endm

/* Structural. */

/* Setup a sane initial state.
 *
 * Should be the first thing in every file.
 *
 * Discussion of what is needed exactly: http://stackoverflow.com/a/32509555/895245
 */
.macro BEGIN
    LOCAL after_locals
    .code16
    cli
    /* Set %cs to 0. TODO Is that really needed? */
    ljmp $0, $1f
    1:
    xor %ax, %ax
    /* We must zero %ds for any data access. */
    mov %ax, %ds
    /* TODO is it really need to clear all those segment registers, e.g. for BIOS calls? */
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    /* TODO What to move into BP and SP?
     * http://stackoverflow.com/questions/10598802/which-value-should-be-used-for-sp-for-booting-process
     */
    mov %ax, %bp
    /* Automatically disables interrupts until the end of the next instruction. */
    mov %ax, %ss
    /* We should set SP because BIOS calls may depend on that. TODO confirm. */
    mov %bp, %sp
    /* Store the initial dl to load stage 2 later on. */
    mov %dl, initial_dl
    jmp after_locals
    initial_dl: .byte 0
after_locals:
.endm

/* Enter protected mode. Use the simplest GDT possible. */
.macro PROTECTED_MODE
    /* Must come before they are used. */
    .equ CODE_SEG, 8
    .equ DATA_SEG, gdt_data - gdt_start

    /* Tell the processor where our Global Descriptor Table is in memory. */
    lgdt gdt_descriptor

    /* Set PE (Protection Enable) bit in CR0 (Control Register 0),
     * effectively entering protected mode.
     */
    mov %cr0, %eax
    orl $0x1, %eax
    mov %eax, %cr0

    ljmp $CODE_SEG, $protected_mode
/* Our GDT contains:
 *
 * * a null entry to fill the unusable entry 0:
 * http://stackoverflow.com/questions/33198282/why-have-the-first-segment-descriptor-of-the-global-descriptor-table-contain-onl
 * * a code and data. Both are necessary, because:
 * +
 * --
 * ** it is impossible to write to the code segment
 * ** it is impossible execute the data segment
 * --
 * +
 * Both start at 0 and span the entire memory,
 * allowing us to access anything without problems.
 *
 * A real OS might have 2 extra segments: user data and code.
 *
 * This is the case for the Linux kernel.
 *
 * This is better than modifying the privilege bit of the GDT
 * as we'd have to reload it several times, losing cache.
 */
gdt_start:
gdt_null:
    .long 0x0
    .long 0x0
gdt_code:
    .word 0xffff //limit 00:15
    .word 0x0 //base 00:15
    .byte 0x0 //base 16:23
    .byte 0b10011010 //P;DPL;S;TYPE;ACCEDIDO
    .byte 0b11001111 //G;D/B;0;AVL;LIM 16:19
    .byte 0x0 //base 24:31
gdt_data:
    .word 0xffff
    .word 0x0
    .byte 0x0
    .byte 0b10010010
    .byte 0b11001111
    .byte 0x0
gdt_end:
gdt_descriptor:
    .word gdt_end - gdt_start //limit 0:15
    .long gdt_start //base 00:32
vga_current_line:
    .long 0
.code32
protected_mode://salta a ejecutar esto
    /* Setup the other segments.
     * Those movs are mandatory because they update the descriptor cache:
     * http://wiki.osdev.org/Descriptor_Cache
     */
    mov $DATA_SEG, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    /* TODO detect the last memory address available properly.
     * It depends on how much RAM we have.
     */
    mov $0X7000, %ebp
    mov %ebp, %esp
.endm

/* Setup a single page directory, which give us 2^10 * 2^12 == 4MiB
 * of identity memory starting at address 0.
 * The currently executing code is inside that range, or else we'd jump somewhere and die.
 */
.equ page_directory, __end_align_4k
.equ page_table, __end_align_4k + 0x1000
.macro SETUP_PAGING_4M
    LOCAL page_setup_start page_setup_end
    PUSH_EADX

    /* Page directory steup. */
    /* Set the top 20 address bits. */
    mov $page_table, %eax
    /* Zero out the 4 low flag bits of the second byte (top 20 are address). */
    and $0xF000, %ax
    mov %eax, page_directory
    /* Set flags for the first byte. */
    mov $0b00100111, %al
    mov %al, page_directory

    /* Page table setup. */
    mov $0, %eax
    mov $page_table, %ebx
page_setup_start:
    cmp $0x400, %eax
    je page_setup_end
    /* Top 20 address bits. */
    mov %eax, %edx
    shl $12, %edx
    /* Set flag bits 0-7. We only set to 1:
     * * bit 0: Page present
     * * bit 1: Page is writable.
     *  Might work without this as the permission also depends on CR0.WP.
     */
    mov $0b00000011, %dl
    /* Zero flag bits 8-11 */
    and $0xF0, %dh
    mov %edx, (%ebx)
    inc %eax
    add $4, %ebx
    jmp page_setup_start
page_setup_end:
    POP_EDAX
.endm

/* * Turn paging on.
 * Registers are not saved because memory will be all messed up.
 *
 * ## cr3
 *
 * The cr3 register does have a format, it is not simply the address of the page directory:
 *
 * * 20 top bits: 4KiB address. Since those are the only address bits,
 *   this implies that the page directory must be aligned to 4Kib.
 * * bits 3 and 4: TODO some function I don't understand yet
 * * all others: ignored
 *
 * Many tutorials simply ignore bits 3 and 4, and do a direct address mov to `cr3`.
 *
 * This sets the 20 top address bits to their correct value, and puts trash in bits 3 and 4,
 * but it generally works.
 */
.macro PAGING_ON
    /* Tell the CPU where the page directory is. */
    mov $page_directory, %eax
    mov %eax, %cr3

    /* Turn paging on. */
    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0
.endm

/* Turn paging off. */
.macro PAGING_OFF
    mov %cr0, %eax
    and $0x7FFFFFFF, %eax
    mov  %eax, %cr0
.endm

/* Clear the screen, move to position 0, 0. */
.macro CLEAR
    PUSH_ADX
    mov $0x0600, %ax
    mov $0x7, %bh
    mov $0x0, %cx
    mov $0x184f, %dx
    int $0x10
    CURSOR_POSITION
    POP_DAX
.endm