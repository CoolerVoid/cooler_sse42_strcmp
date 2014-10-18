global strcmp_sse42_64
; by Cooler_  c00f3r[at]gmail[dot]com
; 64 bit
; nasm -f elf64 code.s -o code.o
; int strcmp_sse42_64(const char *, const char *);  // declare in C code
strcmp_sse42_64:
	push		rbp
	mov		rbp, rsp
	mov		rax, rdi
	mov		rdx, rsi
	sub		rax, rdx
	sub		rdx, 16
 
strloop_64:
	add		rdx, 16
	movdqu		xmm0, [rdx]
	pcmpistri	xmm0, [rdx+rax], 0011000b
	ja		strloop_64
	jc		blockmov_64
	xor		rax, rax
	jmp		quit

blockmov_64:
	add		rax, rdx	
	movzx		rax, byte[rax+rcx]
	movzx		rdx, byte[rdx+rcx]
	sub		rax, rdx	
	
quit:
	pop		rbp
	ret