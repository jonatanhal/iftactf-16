bits 64

global _start

section .text
_start:
	mov rbp, rsp		; save stack-pointer
	xor rax, rax		; zero out rax
	mov rcx, 47		; length
	sub rsp, rcx		; make room on the stack
	mov rsi, rbp		; char*
l00p:   mov bl, byte [enc+rax]	; load encrypted char
	xor bl, byte [key+rax]	; decrypt char
	mov [rsi+rax], byte bl	; store decrypted
	inc rax			; i++
	cmp rax, rcx		; if(i == length)
	je print		; goto print
	jmp l00p		; else, continue
	
	; at this point, rsi = char*
print:  mov rax, 1		; sys_write
	mov rdi, 1		; stdout
	mov rdx, rcx		; length
	syscall 		; call kernel
	jmp quit

quit:	mov rax, 60		; sys_exit
	mov rdi, 0		; exit status
	syscall 		; call kernel
	
section .data
	key db 0xc3, 0x93, 0xa7, 0x1, 0x8c, 0x2c, 0xff, 0xd0, 0x8e, 0x82, 0x3, 0x55, 0xac, 0xf2, 0x73, 0x3c, 0x3e, 0x15, 0x84, 0x1d, 0x84, 0x85, 0x9f, 0x9e, 0x54, 0x9f, 0x61, 0x9, 0x1e, 0x83, 0x5f, 0x6d, 0xa6, 0xfe, 0xf7, 0x87, 0x63, 0x6d, 0x61, 0xd2, 0x1b, 0x7d, 0xe1, 0xf3, 0xb0, 0x5f, 0xc0
	enc db 0xaa, 0xf5, 0xd3, 0x60, 0xef, 0x58, 0x99, 0xab, 0xed, 0xb6, 0x37, 0x34, 0x9b, 0xc1, 0x17, 0xe, 0x13, 0x2c, 0xb0, 0x2b, 0xe7, 0xa8, 0xab, 0xfd, 0x31, 0xfe, 0x4c, 0x6b, 0x29, 0xb3, 0x6f, 0x40, 0xc3, 0x9b, 0xc0, 0xbe, 0x6, 0xb, 0x2, 0xb7, 0x2e, 0x1e, 0xd6, 0xc3, 0xcd, 0x55, 0xc0

