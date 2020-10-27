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
MSG1 dc.b "ECE 3120 is easy",0
MSG2 dc.b "We like it!",0
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



;Displaying "YES" on LCD for Dragon12+ Trainer Board 
;with HCS12 Serial Monitor Program installed. This code is for CodeWarrior IDE
;Modified by Mazidi from Chapter 12 of HS12 book by Mazidi & Causey
;On Dragon12+ LCD data pins of D7-D4 are connected to Pk5-Pk2, En=Pk1,and RS=Pk0,


;code section
     
      JSR CONFIGLCD
    	LDX #MSG1	  
		 JSR PUTSLCD 
		   	
		  
		  LDAA #$c0
		  JSR CMD2LCD
		  
		 	LDX #MSG2	  
		  JSR PUTSLCD
		   		   	
AGAIN: 
  BRA	AGAIN      	
 
 include 'subrotines.inc'