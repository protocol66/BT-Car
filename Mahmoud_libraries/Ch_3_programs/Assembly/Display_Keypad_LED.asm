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

;Keypad program for Dragon12 Plus Trainer Board. 
;Press any key and the ASCII code for the key is shown on PORTB LEDs 
;with HCS12 Serial Monitor Program installed. This code is for CodeWarrior IDE
;In Dragon12+ RAM address is from $1000-3FFF 
;We use RAM addresses starting at $1000 for scratch pad (variables) and $3FFF for Stack 
;Make sure you are in HCS12 Serial Monitor Mode before downloading 
;and also make sure SW7=LOAD (SW7 is 2-bit red DIP Switch on bottom right side of the board and must be 00, or LOAD) 
;Press F7 (to Make), then F5(Debug) to downLOAD,and F5 once more to start the program execution
   

; ======== For LEDs =============
   MOVB #$FF,DDRB         ;MAKE PORTB OUTPUT
   MOVB #$02,DDRJ         ;ENABLE LED ARRAY ON PORTB OUTPUT
   MOVB #$00,PTJ          ;ENABLE LED ARRAY ON PORTB OUTPUT
   MOVB #$00,PORTB        ;INITIALIZE PORT B

; ======== For Seven segments =============   
   MOVB #$0F,DDRP         ;
   MOVB #$0F,PTP          ;TURN OFF 7SEG LED   	

yy: jsr keypad 

 STAA PORTB          ;PUT ASCII TO PORTB
   
   
 BRA yy           ;BACK TO START		
   
 include 'subrotines.inc'