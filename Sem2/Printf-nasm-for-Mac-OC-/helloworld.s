section .data
Text:       dq      0
.len        equ     $ - Text
f_str:      db      10d, 10d

extern         _printf

;=======================================================================
;=======================================================================
;=======================================================================



section .text

;====================== Printf =========================================
;Parameter: r9, r8, rcx, rdx, rsi, rdi
;       %d -> 10
;       %c -> char
;       %s -> string
;       %x -> 16
;       %o -> 8
;       %b -> 2
;       value or address of the string
;out:   -
;destr: rbp, rsi, rax, rdi, rdx, rbx, r9, r11, r12, r13, rcx, r15
;
;=======================================================================

global _MyPrintf
_MyPrintf:

    pop r15

    push r9
    push r8
    push rcx
    push rdx
    push rsi
    push rdi

    call    C_printf
    call    _printf

    call Printf

    call    C_printf
    call    _printf

    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi

    push r15
ret


Printf:
    xor rsi, rsi
    mov     rbp,    rsp
    add     rbp,    8
    mov     rsi,    [rbp]
    add     rbp,    8

PrintfMain:



    cmp [rsi], byte 0
    je ENDPrintf


    cmp [rsi], byte '%'
    jne PrintfDump

    inc     rsi

    mov     r11, rsi


    cmp [rsi], byte 'd'
    je TenSys



    cmp [rsi], byte 'c'
    je ChaSys


    cmp [rsi], byte 's'
    je StrSys



    cmp [rsi], byte 'x'
    je SixSys


    cmp [rsi], byte 'o'
    je EigSys


    cmp [rsi], byte 'b'
    je BinSys

    cmp [rsi], byte '%'
    je PrintfDump

    inc     rsi

    jmp PrintfMain

PrintfDump:
    call PrintCHAR

    inc     rsi
    jmp PrintfMain


TenSys:
    mov     rsi,    [rbp]

    add     rbp,    8
    call PrintTen
    mov     rsi,    r11
    inc     rsi
    jmp PrintfMain

ChaSys:
    mov     rsi,    [rbp]

    add     rbp,    8
    call PrintCha
    mov     rsi,    r11
    inc     rsi
    jmp PrintfMain

StrSys:
    mov     rsi,    [rbp]

    add     rbp,    8
    call PrintStr
    mov     rsi,    r11
    inc     rsi
    jmp PrintfMain

SixSys:
    mov     rsi,    [rbp]

    add     rbp,    8
    call PrintSix
    mov     rsi,    r11
    inc     rsi
    jmp PrintfMain

EigSys:

    mov     rsi,    [rbp]

    add     rbp,    8

    call PrintEig
    mov     rsi,    r11
    inc     rsi
    jmp PrintfMain

BinSys:
    mov     rsi,    [rbp]

    add     rbp,    8

    call PrintBin

    mov     rsi,    r11
    inc     rsi
    jmp PrintfMain

ENDPrintf:

    ret
;====================== C_Printf========================================
; call C printf
;Parameter: -
;out:   -
;destr: rdi, rax, rsi
;=======================================================================
global C_printf
C_printf:
    mov     rdi,    f_str                ; printf("\n")
    sub     rdi,    Text.len
    xor     rax,    rax
ret

;====================== PrintTen========================================
;Parameter: rsi
;out:   -
;destr: rcx, rbx, rdx,
;   (edx,eax)/ecx = eax, edx
;=======================================================================

global PrintTen
PrintTen:
    mov     r12,    rsi
;   mov     [PEREMEN_SAVE], rbx
    mov     rax,    '+'
    Push rax
    xor     rax,    rax
    mov     ecx,    10d            ;dl
    mov     rax,    r12       ; Get symbol

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
    call PrintCHAR
    Pop r11
    Pop rdx
    cmp rdx, '+'            ; if(ah != '$')
    jne T_end1              ;   jump T_end1

    ret

;====================== PrintCha========================================
;Parameter: rsi
;out:   -
;destr: rcx, rdx
;
;=======================================================================

global PrintCha
PrintCha:
    Push r11
    mov     rdx,    rsi
    mov     rsi,    Text
    mov     [rsi],  rdx
    call PrintCHAR
    Pop r11
ret

;====================== PrintStr========================================
;Parameter: rsi
;out:   -
;destr: rbx
;
;=======================================================================

global PrintStr
PrintStr:
    mov     r12, rsi
S_start:
    Push r11
    call PrintCHAR
    Pop r11
    inc rsi
    cmp byte [rsi], 0
    jne S_start

ret

;====================== PrintSix========================================
;Parameter: rsi
;out:   -
;destr: rdx, rbx, r8, rcx, rax
;
;=======================================================================

global PrintSix
    PrintSix:
    mov     r13,    0
    mov     r12,    rsi
    xor     rcx,    rcx

H_start:

    xor     rdx,    rdx            ; dx = 0
    or      edx,    11110000000000000000000000000000b
    and     rdx,    r12
    shr     rdx,    28d

    shl     r12,    4h            ; Pick 4 bits

    cmp rdx, 0h
    jne Six_First_one1
Six_First_one2:

    cmp     rdx,     0ah
    jb H_num

    add     rdx,     'A'            ; if rdx >= 10
    sub     rdx,     0ah
    jmp H_end

H_num:
    add     rdx,     '0'            ; if rdx < 10

H_end:

    mov     r8,     r13
    cmp r8, 1h
    je Six_PrintBinV1
Six_PrintBinV2:

    add rcx, 1
    cmp rcx, 8
    jne H_start

ret

Six_First_one1:
    mov     r13,    1
    jmp Six_First_one2

Six_PrintBinV1:

    Push r11
    Push rcx
    mov     rsi,    Text
    mov     [rsi], rdx
    call PrintCHAR
    Pop rcx
    Pop r11

    jmp Six_PrintBinV2

;====================== PrintEig========================================
;Parameter: rsi
;out:   -
;destr: rbx, rdx, rcx, rax
;
;=======================================================================

global PrintEig
PrintEig:
    mov     rbx,    0
    mov     r13,    rbx
    mov     r12,    rsi
;   mov     [PEREMEN_SAVE], rbx
    xor rcx, rcx

    jmp Eig_JMP2

Eig_start:

    xor     rdx,    rdx
    or      edx,    11100000000000000000000000000000b ; {0} - 31, {1} - 1
    and     rdx,    r12
    shr     edx,    29d

    mov     rbx,    r12
    shl     rbx,    3h            ; Pick 3 bits
    mov     r12,    rbx

    jmp Eig_JMP1
Eig_JMP2:

    xor     rdx,    rdx
    or      edx,    11000000000000000000000000000000b
    and     rdx,    r12
    shr     edx,    30d

    mov     rbx,    r12
    shl     rbx,    2d
    mov     r12,    rbx
Eig_JMP1:

    cmp edx, 0h
    jne Eig_First_one1
    Eig_First_one2:
    mov     r8,     r13
    cmp r8, 1h
    je Eig_PrintBinV1
    Eig_PrintBinV2:

    add rcx, 1
    cmp rcx, 11            ; do it again
    jne Eig_start

;   mov rax, [PEREMEN_SAVE]
;   mov [rsi], rax

ret

Eig_First_one1:
    mov     r8,     1h
    mov     r13,    r8
    jmp Eig_First_one2

Eig_PrintBinV1:

    Push r11
    Push rcx
    add     rdx,    '0'
    mov     rsi,    Text
    mov     [rsi], rdx
    call    PrintCHAR
    Pop rcx
    Pop r11

    jmp Eig_PrintBinV2

;====================== PrintBin========================================
;Parameter: rsi
;out:   -
;destr: rsi, rdx, rax, rbx, rcx, r8
;
;=======================================================================

global PrintBin
PrintBin:
    mov     rbx,    0
    mov     r13,    rbx
    mov     r12,    rsi
;   mov     [PEREMEN_SAVE], rbx

    xor     rcx,    rcx
Bin_start:

    xor     rdx,    rdx
    or      edx,    10000000000000000000000000000000b; {0} - 31, {1} - 1
    and     rdx,    r12
    shr     edx,    31d
    mov     rbx,    r12
    shl     rbx,    1h            ; Get the leftest bit
    mov     r12,    rbx

    cmp rdx, 1h
    je Bin_First_one1
Bin_First_one2:
    mov     r8,     r13
    cmp r8, 1h
    je Bin_PrintBinV1
Bin_PrintBinV2:

    add rcx, 1
    cmp rcx, 32            ; do it again
    jne Bin_start


ret

Bin_First_one1:
    mov     r8,     1h
    mov     r13,    r8
    jmp Bin_First_one2

Bin_PrintBinV1:

    Push r11
    Push rcx
    add     rdx,    '0'
    mov     rsi,    Text
    mov     [rsi], rdx
    call PrintCHAR
    Pop rcx
    Pop r11

    jmp Bin_PrintBinV2

;====================== PrintCHAR=======================================
;Parameter: rsi
;out:   -
;destr: rdx, rdi, rax
;
;=======================================================================

global PrintCHAR
PrintCHAR:

mov rax, 0x2000004      ; System call write = 4
mov rdi, 1              ; Write to standard out = 1
mov rdx, 1              ; The size to write
syscall                 ; Invoke the kernel

ret

;=======================================================================
;=======================================================================
;=======================================================================

