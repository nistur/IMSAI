    ;; Quick attempt at replicating CP/M's BDOS call to provide a form of output
    ;; so that cpudiag will run correctly. Also contains a quick bootloader that
    ;; will boot cpudiag from location $0100
    ;; Hand assembled in comments and then copied into bdos.bin
    ORG $0000

START:                          ;  $00
    JMP BOOT                    ; c3 13 00

FLAG:                           ;  $03
    NOP                         ; 00
    NOP                         ; 00
 
BDOS:                           ;  $05
    XCHG                        ; eb
    PUSH PSW                    ; f5

LOOP:                           ;  $07
    MOV A,M                     ; 7e
    OUT $02                     ; d3 02
    INX H                       ; 23
    CPI $24                     ; fe 24
    JNZ LOOP                    ; c2 07 00
    POP PSW                     ; f1
    XCHG                        ; eb
    RET                         ; c9

BOOT:                           ;  $13
    LDA FLAG                    ; 3a 03 00
    ADI $0                      ; c6 00
    JZ BOOT_INNER               ; ca 1c 00
    HLT                         ; 76

BOOT_INNER:                     ;  $1c
    LXI H,FLAG                  ; 21 03 00
    MVI M,$1                    ; 36 01
    JMP $0100                   ; c3 00 01
