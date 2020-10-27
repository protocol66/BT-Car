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

number_ASCII ds.b 4
number ds.b 1
counter ds.b 1



; code section
            ORG   ROMStart



Entry:
_Startup:
            LDS   #RAMEnd+1       ; initialize the stack pointer

            CLI                     ; enable interrupts
main:   
      jsr CONFIGLCD

start:  
     ldy #number_ASCII
     jsr get_number
      
     LDAA #$1
     JSR CMD2LCD
     
     LDAA #$06 ;move cursor to right (entry mode set instruction) 	
	   JSR CMD2LCD    
     

     ldx #number_ASCII
     jsr PUTSLCD

     ldy #number_ASCII
     jsr D2B_8bits_signed
     stab number 
     
     LDAA	#'+' 	
     JSR	PUTCLCD 
     
     ldy #number_ASCII
     jsr get_number
     
     ldx #number_ASCII
     jsr PUTSLCD
     
     LDAA	#'=' 	
     JSR	PUTCLCD
	   
     ldy #number_ASCII
     jsr D2B_8bits_signed
     addb number
    
     
     ldy #number_ASCII
     jsr B2D_8bits_signed
    
      ldx #number_ASCII
      jsr PUTSLCD
    
      lbra start 



 include 'subrotines.inc'
