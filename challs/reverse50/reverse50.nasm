bits 64
global _start

%macro sneakyFlag 1
	mov byte [rdi+rcx], %1
	inc rcx
%endmacro

%macro quit 1
	mov rax, 60		; sys_exit
	mov rdi, %1		; exit status
	syscall 		; call kernel	
%endmacro

%macro stdOutPrint 2
	mov rsi, %1		; message
	mov rdx, %2 		; length
	mov rax, 1		; sys_write
	mov rdi, 1		; stdout
	syscall 		; call kernel
%endmacro

section .text
_start:
	mov rbp, rsp 		; backup rsp
	mov rdi, rsp		; rdi = char*
	cmp qword [rsp], 3	; three or more arguments? 
	jge .ok			; if yes jmp ok
	stdOutPrint helpMessage, helpLength
	quit 1
.ok:	mov rax, [rbp+16]	; rax = first argument
	mov rax, [rax]		; dereference the char * into rax
	mov rbx, [rbp+24]	; rbx = second argument
	mov rbx, [rbx]		; dereference the char * into rbx
	add rax, rbx		; add them together
	jmp .arev		; anti-reversing magic
	db 0xe8
.arev:  mov rbx, magic
	cmp rax, [rbx]		; 92149d87 83ca02b2
	jne .fail
	mov rax, rbp
	call win
.fail:  quit 0

%define flag "iftac16{8d847d58-6091-41aa-896f-bba3ef32f133}"
%strlen flaglen flag
win:
        ; register | parameter
        ; rsi      | char*    (encr)
        ; rdx      | length
	;
	mov rbp, rsp		; backup rsp
	sub rsp, flaglen	; make room on the stack
	mov rdi, rbp		; copy a pointer to the local variable

	xor rcx, rcx
	%assign i 1
	%rep flaglen
		%substr f flag i
		sneakyFlag f
		%assign i i+1
	%endrep

	add rsp, flaglen	; restore the stack
	stdOutPrint rbp, flaglen
	quit 0

section .data
	magic dq 0x699a966995946571
	helpMessage db "usage: reverse50 serial-key activation-key", 0xa
	helpLength equ $-helpMessage
