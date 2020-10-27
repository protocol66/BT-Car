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

DispTab dc.b $3F,$06,$5B,$4F,$66,$6D,$7D,$07,$7F,$6F
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

	movb	#$FF,DDRB  ; Configure port B as output port
	movb	#$0F,DDRP  ; configure PP0 to PP3 as output pins
	movb	#$FE,PTP  ; enable the first display
	bset	DDRJ,$02	    ;configure PJ1 pin for output
	bset PTJ,$02	      ;disable the LEDs

forever: ldx #DispTab   ;set X to point to the display table

loopi:   movb 0,x,PORTB  ; output segment pattern
	inx
	
	ldy	#1000
	jsr	Delay_yms	; wait for 1 second

	cpx	#DispTab+10	; reach the end of the table?
	bne	loopi
	bra	forever

 include 'subrotines.inc'

