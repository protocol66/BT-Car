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


;Toggling PE2 to turn on and off the relay for Dragon12 Plus Trainer Board 
;PE2 of PORTE is connected to Relay on Dragon12+ board
;This program toggles PE2 to click on and off the relay (you hear the click sound opening and clsoing the relay)
;For relay discussion see Chapter 15 of Mazidi & Causey HCS12 book

;If you use this relay to control an external device such as horn and lamp use external power as shown in chapter 15.  

    
;code section
         
  Bset DDRE,%00000100     ;PE2 as Output pin for Relay
  Bclr DDRH,$00           ; initially the relay is off


Loop:    
        Brset PTH,$01,Off    ; if the switch is not connected, go to on 
        Bset PORTE,%00000100     ;PE2=1 to turn on relay
        Bra Loop
Off:    Bclr PORTE,%00000100     ;PE2=0 to turn off relay     
	  Bra Loop              ;Keep toggling Relay    

	  
