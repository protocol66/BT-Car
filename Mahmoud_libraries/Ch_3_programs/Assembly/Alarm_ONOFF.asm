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

 ifdef _HCS12_SERIALMON
            ORG $3FFF - (RAMEnd - RAMStart)
 else
            ORG RAMStart
 endif
 ; Insert here your data definition.
counter ds.b 1


; code section
            ORG   ROMStart


Entry:
_Startup:
            ; remap the RAM &amp; EEPROM here. See EB386.pdf
 ifdef _HCS12_SERIALMON
            ; set registers at $0000
            CLR   $11                  ; INITRG= $0
            ; set ram to end at $3FFF
            LDAB  #$39
            STAB  $10                  ; INITRM= $39

            ; set eeprom to end at $0FFF
            LDAA  #$9
            STAA  $12                  ; INITEE= $9


            LDS   #$3FFF+1        ; See EB386.pdf, initialize the stack pointer
 else
            LDS   #RAMEnd+1       ; initialize the stack pointer
 endif

            CLI                     ; enable interrupts

	bset	DDRT,#%00100000; configure PT5 pin for output
	movb #0,DDRH	; configure port A for input
forever: brclr PTH,#%00000001,forever ; wait here if bit0 = 0
 ldx	#250	;0.5 second should have 250 cycles from 500 Hz signal
tone1: bset	PTT,#%00100000 ; pull PT5 pin to high
	ldy	#1
	jsr	Delay_yms
	bclr	PTT,#%00100000
	ldy	#1
	jsr	Delay_yms
	dbne	x,tone1
	ldx	#125	;0.5 second should have 125 cycles from 250Hz signal
tone2: bset	PTT,#%00100000
	ldy	#2
	jsr	Delay_yms
	bclr	PTT,#%00100000
	ldy	#2
	jsr	Delay_yms
	dbne	x,tone2
	bra	forever

 include 'subrotines.inc'