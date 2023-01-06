; bootloader not included go get your own

bits 32
section .text
    ; multiboot compliancy
    align 4
    dd 0x1BADB002              ;magic
    dd 0x00                    ;flags
    dd - (0x1BADB002 + 0x00)   ;checksum

global start
global keyboard_handler
global read_port
global write_port
global write_port_word
global load_idt
global outsw
global insw

extern main
extern keyboard_handler_main

read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

write_port_word:
    mov edx, [esp + 4]
    mov ax, [esp + 4 + 4]
    out dx, ax
    ret

insw:
    push   edi
    ; movl    8(%esp), %edx  # port
    mov edx, [esp+8]
    ; movl    12(%esp), %edi # addr
    mov edi, [esp+12]
    ; movl    16(%esp), %ecx # count
    mov ecx, [esp+16]

    xor    eax, eax
.insw_startLoop:
    cmp    eax, ecx
    je      .insw_end

    insw

    inc    eax
    jmp     .insw_startLoop

.insw_end:
    pop    edi
    ret

; .type outsw, @function
;     # void outsw(uint16_t port, void *addr, unsigned int count)
outsw:
    push   esi
    ; movl    8(%esp), %edx  # port
    mov edx, [esp+8]
    ; movl    12(%esp), %esi # addr
    mov esi, [esp+12]
    ; movl    16(%esp), %ecx # count
    mov ecx, [esp+16]

    xor    eax, eax
.outsw_startLoop:
    cmp    eax, ecx
    je      .outsw_end

    outsw

    inc    eax
    jmp     .outsw_startLoop

.outsw_end:
    pop    esi
    ret

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret

keyboard_handler:                 
	call    keyboard_handler_main
	iretd

start:
	cli
	mov esp, stack_space
	call main
	hlt

section .bss
resb 8192; 8KB for stack
stack_space: