DEFAULT REL
section .data
Text        dq      0
.len            equ     $ - Text
array       dq      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

section .text
global start

start:
;
;       rsi
;

nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
push 12d
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
mov     r15,    array
sub     r15,    Text.len
mov qword [r15+2],    1d
push [r15+2]
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
pop     rsi
mov     rax,    '+'
Push rax
xor     rax,    rax
mov     ecx,    10d            ;dl
mov     rax,    rsi      ; Get symbol
T_start:
xor     rdx,    rdx
div ecx                ;dl
cmp eax, 0h            ; if end of num
je T_end1            ; break
Push rdx
xor     edx,    edx
jmp T_start
T_end1:
add     rdx,    '0'
mov     rsi,    Text
mov     [rsi],  rdx
Push r11
mov rax, 0x2000004      ; System call write = 4
mov rdi, 1              ; Write to standard out = 1
mov rdx, 1              ; The size to write
syscall                 ; Invoke the kernel
Pop r11
Pop rdx
cmp rdx, '+'            ; if(ah != '$')
jne T_end1              ;   jump T_end1
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop


mov rax, 0x2000001      ; System call number for exit = 1
mov rdi, 0              ; Exit success = 0
syscall                 ; Invoke the kernel
