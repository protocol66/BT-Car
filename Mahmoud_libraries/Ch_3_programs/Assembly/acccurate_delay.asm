;*****************************************************************
;* This stationery serves as the framework for a                 *
;* user application (single file, absolute assembly application) *
;* For a more comprehensive program that                         *
;* demonstrates the more advanced functionality of this          *
;* processor, please see the demonstration applications          *
;* located in the examples subdirectory of the                   *
;* Freescale CodeWarrior for the HC12 Program directory          *
;*****************************************************************

; export symbols
            XDEF Entry, _Startup            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point



; Include derivative-specific definitions 
		INCLUDE 'mc9s12dg256.inc' 

ROMStart    EQU  $4000  ; absolute address to place my code/constant data

; variable/data section

            ORG RAMStart
 ; Insert here your data definition.

; code section
            ORG   ROMStart


Entry:
_Startup:
            LDS   #RAMEnd+1       ; initialize the stack pointer

            CLI                     ; enable interrupts
main:   bset DDRJ,$02 ;configure PJ1 pin for output
        bclr PTJ,$02 ;enable LEDs to light
        movb #$FF,DDRP ; disable 7 segments that are connected
        movb #$0F,PTP ; ‘’ ‘’ ‘’
        bset DDRB,#%11111111 ;configure PB0 pin for output
flip:
        ldaa PORTB_
        eora #01
        staa PORTB
        
        nop
        nop
        nop
        
      ldx #5997
loop: dex
      bne loop
      bra flip
     