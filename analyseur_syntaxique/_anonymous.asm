section .data
format db "Value: %d", 10, 0
section .text
global _start
extern printf
_start:
; Processing instruction at line 0
; ASSIGN
push 10
push 5
; Expression evaluation would go here
pop rbx
pop rax
; After expression evaluation, we would have the value in rax and the variable address in rbx
sub rbx, rax
; Processing instruction at line 0
; Return statement found
mov rax, 0
mov rdi, format
mov rsi, rbx
xor rax, rax
call printf
mov rax, 60
xor rdi, rdi
syscall
