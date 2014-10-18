; by Cooler_  c00f3r[at]gmail[dot]com
global strcmp_sse42_32
; nasm -f elf32 code.s -o code.o
; 32 bit
; static int strcmp_sse42_32(const char *, const char *);  // declare in C code
;
; thanks Joao Victorino n code fellas
strcmp_sse42_32:
	push	ebp
	mov	ebp, esp
	
	mov	eax, [ebp+8]
	mov	edx, [ebp+12]
	
	sub	eax, edx
	sub	edx, 16
 
strLoop:
	add		edx, 16
	movdqu		xmm0, [edx]
	pcmpistri	xmm0, [edx+eax], 0011000b
	ja		strLoop
	jc		blockMov
	xor		eax, eax
	jmp		quit

blockMov:
	add	eax, edx	
	movzx	eax, byte[eax+ecx]
	movzx	edx, byte[edx+ecx]
	sub	eax, edx
	
quit:
	pop		ebp
	ret
