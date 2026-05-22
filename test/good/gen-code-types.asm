section .bss
    somme resd 1
    produit resd 1
    quotient resd 1
    reste resd 1
    difference resd 1
    letter resb 1
    digit resb 1
    punct resb 1
    uppercase resd 1

section .text
global main

; ===== Built-in I/O =====

; putchar(char c) : affiche le caractère passé dans rdi
putchar:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 16
    mov     byte [rbp-1], dil
    mov     rax, 1
    mov     rdi, 1
    lea     rsi, [rbp-1]
    mov     rdx, 1
    syscall
    leave
    ret

; putint(int i) : affiche l'entier passé dans rdi suivi d'un newline
putint:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 32
    mov     rax, rdi
    lea     r9, [rbp-21]
    mov     byte [r9], 10
    dec     r9
    test    rax, rax
    jns     .putint_pos
    neg     rax
    mov     r10, 1
    jmp     .putint_loop
.putint_pos:
    mov     r10, 0
.putint_loop:
    xor     rdx, rdx
    mov     rcx, 10
    div     rcx
    add     dl, '0'
    mov     byte [r9], dl
    dec     r9
    test    rax, rax
    jnz     .putint_loop
    test    r10, r10
    jz      .putint_write
    mov     byte [r9], '-'
    dec     r9
.putint_write:
    inc     r9
    lea     rdx, [rbp-20]
    sub     rdx, r9
    add     rdx, 2
    mov     rax, 1
    mov     rdi, 1
    mov     rsi, r9
    syscall
    leave
    ret

; getchar() : lit un caractère depuis stdin, retourne dans rax
getchar:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 16
    mov     rax, 0
    mov     rdi, 0
    lea     rsi, [rbp-1]
    mov     rdx, 1
    syscall
    test    rax, rax
    jle     .getchar_eof
    movzx   rax, byte [rbp-1]
    leave
    ret
.getchar_eof:
    mov     rax, -1
    leave
    ret

; getint() : lit un entier décimal depuis stdin, retourne dans rax
getint:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 16
    xor     r8, r8
    mov     r9, 1
    mov     rax, 0
    mov     rdi, 0
    lea     rsi, [rbp-1]
    mov     rdx, 1
    syscall
    movzx   rcx, byte [rbp-1]
    cmp     rcx, '-'
    je      .getint_minus
    cmp     rcx, '+'
    je      .getint_plus
    cmp     rcx, '0'
    jl      .getint_err
    cmp     rcx, '9'
    jg      .getint_err
    sub     rcx, '0'
    mov     r8, rcx
    jmp     .getint_loop
.getint_minus:
    mov     r9, -1
.getint_plus:
    mov     rax, 0
    mov     rdi, 0
    lea     rsi, [rbp-1]
    mov     rdx, 1
    syscall
    movzx   rcx, byte [rbp-1]
    cmp     rcx, '0'
    jl      .getint_err
    cmp     rcx, '9'
    jg      .getint_err
    sub     rcx, '0'
    mov     r8, rcx
.getint_loop:
    mov     rax, 0
    mov     rdi, 0
    lea     rsi, [rbp-1]
    mov     rdx, 1
    syscall
    movzx   rcx, byte [rbp-1]
    cmp     rcx, 10
    je      .getint_done
    cmp     rcx, '0'
    jl      .getint_err
    cmp     rcx, '9'
    jg      .getint_err
    sub     rcx, '0'
    imul    r8, r8, 10
    add     r8, rcx
    jmp     .getint_loop
.getint_done:
    imul    r8, r9
    mov     rax, r8
    leave
    ret
.getint_err:
    mov     rax, 60
    mov     rdi, 5
    syscall


main:
    mov     rax, 12
    mov     dword [somme], eax
    mov     rax, 24
    mov     dword [produit], eax
    mov     rax, 24
    push    rax
    mov     rax, 12
    mov     rbx, rax
    pop     rax
    cqo
    idiv    rbx
    mov     dword [quotient], eax
    mov     rax, 99
    mov     byte [letter], al
    mov     rax, 48
    mov     byte [digit], al
    movzx   eax, byte [letter]
    movsxd  rax, eax
    push    rax
    mov     rax, 65
    push    rax
    mov     rax, 97
    mov     rbx, rax
    pop     rax
    sub     rax, rbx
    mov     rbx, rax
    pop     rax
    add     rax, rbx
    mov     dword [uppercase], eax
    call    getint
    mov     dword [reste], eax
    mov     rax, 10
    push    rax
    pop     rdi
    call    putchar
    mov     rax, 0
    jmp     .main_epilogue
.main_epilogue:
    mov     rdi, rax
    mov     rax, 60
    syscall
