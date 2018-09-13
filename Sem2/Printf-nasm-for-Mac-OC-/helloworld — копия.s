DEFAULT REL
section .data

Parameter       dq      '{%dd = %bb = %oo = %x%s} $'
.len            equ     $ - Parameter
ValN            dq      15
.len            equ     $ - ValN
ValC            dq      'h big p$'
.len            equ     $ - ValC

PEREMEN         dq      0
.len            equ     $ - PEREMEN
PEREMEN_SAVE    dq      0
.len            equ     $ - PEREMEN_SAVE

FirstOne        dq      0
.len            equ     $ - FirstOne


Safe_FurPar     dq      0
.len            equ     $ - Safe_FurPar

Safe1_rbp       dq      0
.len            equ     $ - Safe1_rbp
Safe2_rbp       dq      0
.len            equ     $ - Safe2_rbp


section .text
global start

start: 
jmp Main

extern printf

;====================== Printf ==========================================
;First parameter:
;       %d -> 10
;       %c -> char
;       %s -> string
;       %x -> 16
;       %o -> 8
;       %b -> 2
;Second parameter:
;       value or address of the string
;out:   -
;destr: rbp, rsi, rax, rdi, rdx, rbx
;
;========================================================================

global MyPrintf
MyPrintf:
    xor rsi, rsi
    mov     rbp,    rsp
    mov     [Safe1_rbp], rbp
    add     rbp,    8
    mov     rsi,    [rbp]
    add     rbp,    8

PrintfMain:


    mov     bl,     '$'
    cmp byte [esi], bl
    je ENDPrintf

    mov     bl,     '%'
    cmp byte [esi], bl
    jne PrintfDump

    inc     esi

    mov     [Safe_FurPar], rsi

    mov     bl,     'd'
    cmp byte [esi], bl
    je TenSys


    mov     bl,     'c'
    cmp byte [esi], bl
    je ChaSys

    mov     bl,     's'
    cmp byte [esi], bl
    je StrSys

    mov     bl,     'x'
    cmp byte [esi], bl
    je SixSys

    mov     bl,     'o'
    cmp byte [esi], bl
    je EigSys

    mov     bl,     'b'
    cmp byte [esi], bl
    je BinSys

    inc     esi

    jmp PrintfMain

PrintfDump:
    call PrintCHAR

    inc esi
    jmp PrintfMain


TenSys:
    mov     rsi,    [rbp]

    add     rbp,    8
    call PrintTen
    mov     rsi,    [Safe_FurPar]
    inc     esi
    jmp PrintfMain

ChaSys:
    mov     rsi,    [rbp]

    add     rbp,    8
    call PrintCha
    mov     esi,    [Safe_FurPar]
    inc     esi
    jmp PrintfMain

StrSys:
    mov     rsi,    [rbp]

    add     rbp,    8
    call PrintStr
    mov     esi,    [Safe_FurPar]
    inc     esi
    jmp PrintfMain

SixSys:
    mov     rsi,    [rbp]

    add     rbp,    8
    call PrintSix
    mov     esi,    [Safe_FurPar]
    inc     esi
    jmp PrintfMain

EigSys:
    mov     rsi,    [rbp]

    add     rbp,    8

    call PrintEig
    mov     esi,    [Safe_FurPar]
    inc     esi
    jmp PrintfMain

BinSys:
    mov     rsi,    [rbp]

    add     rbp,    8

    call PrintBin


    mov     esi,    [Safe_FurPar]
    inc     esi
    jmp PrintfMain

ENDPrintf:

    ret

;====================== PrintTen=========================================
;Parameter: rsi
;out:   -
;destr: rcx, rbx, rdx,
;   (edx,eax)/ecx = eax, edx
;========================================================================

global PrintTen
PrintTen:
    mov     rbx,    [rsi]
    mov     [PEREMEN], rbx
    mov     [PEREMEN_SAVE], rbx
    mov     rax,    '+'
    Push rax
    xor     rax,    rax
    mov     ecx,    10d            ;dl
    mov     rax,    [PEREMEN]       ; Get symbol

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
    mov     [rsi],  rdx
    call PrintCHAR
    Pop rdx
    cmp rdx, '+'            ; if(ah != '$')
    jne T_end1              ;   jump T_end1

    mov rax, [PEREMEN_SAVE]
    mov [rsi], rax

    ret

;====================== PrintCha=========================================
;Parameter: rsi
;out:   -
;destr: rcx
;
;========================================================================

global PrintCha
PrintCha:
    call PrintCHAR
ret

;====================== PrintStr=========================================
;Parameter: rsi
;out:   -
;destr: rbx
;
;========================================================================

global PrintStr
PrintStr:
    mov     [PEREMEN], rsi
    mov     [PEREMEN_SAVE], rsi
S_start:
    call PrintCHAR
    inc rsi
    mov     bl,     '$'
    cmp byte [esi], bl
    jne S_start


ret

;====================== PrintSix=========================================
;Parameter: rsi
;out:   -
;destr: rdx, rbx, r8, rcx, rax
;
;========================================================================

global PrintSix
    PrintSix:

    mov     rbx,    0
    mov     [FirstOne], rbx
    mov     rbx,    [rsi]
    mov     [PEREMEN], rbx
    mov     [PEREMEN_SAVE], rbx
    xor     rcx,     rcx
H_start:

    xor     rdx,     rdx            ; dx = 0
    or      edx,     11110000000000000000000000000000b
    and     rdx,     [PEREMEN]
    shr     edx,     28d

    mov     rbx,    [PEREMEN]
    shl     rbx,    4h            ; Pick 4 bits
    mov     [PEREMEN], rbx

    cmp edx, 0h
    jne Six_First_one1
Six_First_one2:

    cmp     edx,     0ah
    jb H_num

    add     rdx,     'A'            ; if rdx >= 10
    sub     rdx,     0ah
    jmp H_end

H_num:
    add     rdx,     '0'            ; if rdx < 10

H_end:

    mov     r8,     [FirstOne]
    cmp r8, 1h
    je Six_PrintBinV1
Six_PrintBinV2:

    add rcx, 1
    cmp rcx, 8
    jne H_start

    mov     rax,    [PEREMEN_SAVE]
    mov     [rsi], rax

ret

Six_First_one1:
    mov     r8,     1h
    mov     [FirstOne], r8
    jmp Six_First_one2

Six_PrintBinV1:

    Push rcx
    mov     [rsi],  rdx
    call PrintCHAR
    Pop rcx

    jmp Six_PrintBinV2

;====================== PrintEig=========================================
;Parameter: rsi
;out:   -
;destr: rbx, rdx, rcx, rax
;
;========================================================================

global PrintEig
PrintEig:
    mov     rbx,    0
    mov     [FirstOne], rbx
    mov     rbx,    [rsi]
    mov     [PEREMEN], rbx
    mov     [PEREMEN_SAVE], rbx
    xor rcx, rcx

    jmp Eig_JMP2

Eig_start:

    xor     rdx,    rdx
    or      edx,    11100000000000000000000000000000b ; {0} - 31, {1} - 1
    and     rdx,    [PEREMEN]
    shr     edx,    29d

    mov     rbx,    [PEREMEN]
    shl     rbx,    3h            ; Pick 3 bits
    mov     [PEREMEN], rbx

    jmp Eig_JMP1
Eig_JMP2:

    xor     rdx,    rdx
    or      edx,    11000000000000000000000000000000b
    and     rdx,    [PEREMEN]
    shr     edx,    30d

    mov     rbx,    [PEREMEN]
    shl     rbx,    2d
    mov     [PEREMEN], rbx
Eig_JMP1:

    cmp edx, 0h
    jne Eig_First_one1
    Eig_First_one2:
    mov     r8,     [FirstOne]
    cmp r8, 1h
    je Eig_PrintBinV1
    Eig_PrintBinV2:

    add rcx, 1
    cmp rcx, 11            ; do it again
    jne Eig_start

    mov rax, [PEREMEN_SAVE]
    mov [rsi], rax

ret

Eig_First_one1:
    mov     r8,     1h
    mov     [FirstOne], r8
    jmp Eig_First_one2

Eig_PrintBinV1:

    Push rcx
    add     rdx,    '0'
    mov     [rsi],  rdx
    call PrintCHAR
    Pop rcx

    jmp Eig_PrintBinV2

;====================== PrintBin=========================================
;Parameter: rsi
;out:   -
;destr: rsi, rdx, rax, rbx, rcx, r8
;
;========================================================================

global PrintBin
PrintBin:
    mov     rbx,    0
    mov     [FirstOne], rbx
    mov     rbx,    [rsi]
    mov     [PEREMEN], rbx
    mov     [PEREMEN_SAVE], rbx

    xor     rcx,    rcx
Bin_start:

    xor     rdx,    rdx
    or      edx,    10000000000000000000000000000000b; {0} - 31, {1} - 1
    and     rdx,    [PEREMEN]
    shr     edx,    31d
    mov     rbx,    [PEREMEN]
    shl     rbx,    1h            ; Get the leftest bit
    mov     [PEREMEN], rbx

    cmp rdx, 1h
    je Bin_First_one1
Bin_First_one2:
    mov     r8,     [FirstOne]
    cmp r8, 1h
    je Bin_PrintBinV1
Bin_PrintBinV2:

    add rcx, 1
    cmp rcx, 32            ; do it again
    jne Bin_start

    mov rax, [PEREMEN_SAVE]
    mov [rsi], rax


ret

Bin_First_one1:
    mov     r8,     1h
    mov     [FirstOne], r8
    jmp Bin_First_one2

Bin_PrintBinV1:

    Push rcx
    add     rdx,    '0'
    mov     [rsi],  rdx
    call PrintCHAR
    Pop rcx

    jmp Bin_PrintBinV2

;====================== PrintCHAR=========================================
;Parameter: rsi
;out:   -
;destr: rdx, rdi, rax
;
;========================================================================

global PrintCHAR
PrintCHAR:

mov rax, 0x2000004      ; System call write = 4
mov rdi, 1              ; Write to standard out = 1
mov rdx, 1              ; The size to write
syscall                 ; Invoke the kernel

ret
;========================================================================
;=========================== int MAIN () { ==============================
;========================================================================
Main:
    mov rax, 10
    mov rbx, "%i\n"
    push rax;
    push rbx
    call printf
    add esp, 16

    mov     rax,    ValC
    sub     rax,    ValN.len
    sub     rax,    Parameter.len
    Push    rax
    
    mov     rax,    ValN
    sub     rax,    Parameter.len
    
    Push    rax
    Push    rax
    Push    rax
    Push    rax
    
    mov     rax,    Parameter
    Push    rax
    
    ;call MyPrintf
    jmp Mem_end

Mem_end:
    mov rax, 0x2000001      ; System call number for exit = 1
    mov rdi, 0              ; Exit success = 0
    syscall                 ; Invoke the kernel

;========================================================================
;=========================== return 0; ==================================
;= } ====================================================================
;========================================================================