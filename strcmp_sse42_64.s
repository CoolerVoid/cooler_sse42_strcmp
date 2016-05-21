bits 64
    section .text

    global strcmp_sse42_64
;
; by Cooler_  c00f3r[at]gmail[dot]com
; 64 bit
; $ nasm -f elf64 code.s -o code.o
;
; int strcmp_sse42_64(const char *, const char *);  // declare in C code
;
strcmp_sse42_64:
    mov       rax, rdi
    mov       rdx, rsi

    sub       rax, rdx
    sub       rdx, 16
   
strloop_64:
    add       rdx, 16
    movdqu    xmm0, [rdx]
    pcmpistri xmm0, [rdx+rax], 0b00011000 ;compare... jump again if above...
    ja        strloop_64
    jc        blockmov_64                 ; jump 2 movzx
    xor       eax, eax                    ; clear return result (smaller instruction)...
    ret
  
blockmov_64:
    add       rax, rdx    
    movzx     rax, byte [rax+rcx]         ; move with zero
    movzx     rdx, byte [rdx+rcx]
    sub       rax, rdx    

quit:
    ret

