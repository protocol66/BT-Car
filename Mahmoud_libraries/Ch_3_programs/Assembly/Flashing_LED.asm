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
		INCLUDE 'derivative.inc' 

ROMStart    EQU  $4000  ; absolute address to place my code/constant data

; variable/data section

 ifdef _HCS12_SERIALMON
            ORG $3FFF - (RAMEnd - RAMStart)
 else
            ORG RAMStart
 endif
 ; Insert here your data definition.

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
mainLoop:

    bset	DDRJ,$02	   ;configure PJ1 pin for output
	bclr	PTJ,$02	         ;enable LEDs to light
	movb #$FF,DDRP   ; disable 7 segments that are connected
	movb #$0F,PTP    ; ''    ''             ''
	bset	DDRB,#%00000001  ;configure PB0 pin for output

forever: bset PORTB,#%00000001 ; pull PB0 pin to high
	
      ldy	#1000	; wait for 1000 ms = 1 sec
	jsr	Delay_yms	;	"
	
      bclr PORTB,#%00000001  ; pull PB0 pin to low
	ldy	#1000	; wait for 1000 ms = 1 sec
	jsr	Delay_yms	;	"	
	
	bra	forever

 include 'subrotines.inc'
  