section .bss
section .data
format db "Value: %d", 10, 0
section .text
global main
extern printf
main:
; Processing instruction at line 4
; ASSIGN
; Processing instruction at line 5
; Return statement found
mov rax, 0
mov rdi, format
mov rsi, rbx
xor rax, rax
call printf
xor rdi, rdi
ret
