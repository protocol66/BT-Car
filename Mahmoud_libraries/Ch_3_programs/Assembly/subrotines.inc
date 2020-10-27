 
 ;---------------------------------------------------------------------------------------------------------------------------------------
 ; the subroutine D2B_16bits_signed converts decimal to binary and it is used for negative numbers. 
 ; The decimal number is stored as ASCII code in an array that ends with 0. Y points at the beginning of the array. If the number is negative the string should start with "-"
 ; the decimal value is stored in register D
 ;---------------------------------------------------------------------------------------------------------------------------------------
 
D2B_16bits_signed
 pshx
 pshy
 ldx #0   ; X will have the converted number - initialize it to 0
 ldab 0,Y  ; b= the first element
 pshb      ; save it because later we need to know if the number is -ve to compute the negate
 cmpb #45  ; 45 means -
 bne pos_sig_number16
 iny
     
pos_sig_number16
  ldab 0,Y   
  cmpb #0   ; check if this is the last number
  beq _end_sig_16
  iny   ; point at next element 
  subb #$30     ; convert ASCII to a decimal 
  
  pshy  ; push y because I want to use
  pshd  ; push d because I want to use
  xgdx
  ldy #10
  emul ; Y,D= D X 10 =X X 10=D
  xgdx  ; X=D or X = X times 10
  puld
  puly
  abx
  
  bra pos_sig_number16



_end_sig_16  
  ; I AM USING D
  pulb   ; chcek if the string started with -
  cmpb #45
   beq negative_16number
   xgdx
   puly
 pulx
  rts


negative_16number: 
 xgdx
 coma ; negate the number
 comb
 addd #1 
 puly
 pulx 
   rts
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------



;---------------------------------------------------------------------------------------------------------------------------------------
 ; the subroutine D2B_16bits_unsigned converts decimal to binary and it is used for unsigned numbers. 
 ; The decimal number is stored as ASCII code in an array that ends with 0. Y points at the beginning of the array. Do not use + at the beginning 
 ; the decimal value is stored in register D
 ;---------------------------------------------------------------------------------------------------------------------------------------
 
D2B_16bits_unsigned
 pshx
 pshy

    ldx #0 ; decimal number is stored in X, initialize it
pos_number16
  ldab 0,Y   
  cmpb #0   
  beq _end16
  iny           ; point at next element
  subb #$30     ; convert number to decimal 
  pshy
  pshd
  xgdx
  ldy #10
  emul ; Y,D= D X 10 =X X 10=D
  xgdx  ; X=D  or X = 10X 
  puld
  puly
  abx
  
  bra pos_number16

_end16  
   xgdx  ; store the result in D

 puly
 pulx
 rts

;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------

;---------------------------------------------------------------------------------------------------------------------------------------
 ; the subroutine D2B_8bits_signed converts decimal to binary and it is used for signed numbers. 
 ; The decimal number is stored as ASCII code in an array that ends with 0. Y points at the beginning of the array. If the number is negative the string should start with "-"
 ; the decimal value is stored in register B
 ;---------------------------------------------------------------------------------------------------------------------------------------
 
D2B_8bits_signed
 pshx
 pshy
 psha
 
 ldab #0 

 ldaa 0,Y
 psha
 cmpa #45
 bne pos_num
 iny
  
pos_num:
  ldaa 0,Y  
  cmpa #0
  beq _end
  iny
  suba #$30
     
  psha  ; save A because we will need it later
  
  ldaa #10
  mul ; B= B X 10
  pula
  
  aba ; A = B +A
  tab  
  bra pos_num

_end
 pula
 cmpa #45
 beq negative_number
 pula
 puly
 pulx
 rts

negative_number: 
 negb 
 
 pula
 puly
 pulx
   rts

;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------


;---------------------------------------------------------------------------------------------------------------------------------------
 ; the subroutine D2B_8bits_unsigned converts decimal to binary and it is used for 8 bit unsigned numbers. 
 ; The decimal number is stored as ASCII code in an array that ends with 0. Y points at the beginning of the array. Do not use + at the beginning 
 ; the decimal value is stored in register B
 ;---------------------------------------------------------------------------------------------------------------------------------------
D2B_8bits_unsigned
 pshx
 pshy
 psha
   ldab #0

pos_number
  ldaa 0,Y  
  cmpa #0
  beq _end1
  
  iny
  suba #$30
     ; save the content of y
  psha
  
  ldaa #10
  mul ; B= B X 10
  pula
  
  aba ; A = B +A
  tab  
  bra pos_number

_end1
 pula
 puly
 pulx
   rts

;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------


; the subroutine B2D_16bits_signed converts binary number stored in register D to ASCII and store the result starting from the memory location pointed by Y, the end will be 0.
; If the number is -ve, the ASCII starts with -
;--------------------------------------------------------------------------------------------------------------------------------------
 
B2D_16bits_signed
 pshx
 pshy

 
  movb #$0,counter ; counter i used to count the number of digits
  cpd #0
  BGE positive16
  pshd
 ; the number is negative 
  ldab #45 ; store -
  stab 0,Y 
  puld
  iny
  coma ; negate d
  comb
  addd #1

positive16  
  ldx #10 ;X =10
  idiv ;D/X Quotient ? X, Remainder ?D
  pshb
  inc counter
  cpx #0 
  beq end_division16sign  ; end if quotient =0
 
 xgdx ; D = the quotient required for the next division
 ldx #10 ; X =10
 idiv ; D/10 Quotient ? X, Remainder ? D
 pshb  ; save the number
 inc counter
 
 cpx #0 
 beq end_division16sign
 
 xgdx ; D = the quotient required for the next division
 ldx #10 ; X =10
 idiv ; D/10 Quotient ? X, Remainder ? D
 pshb  ; save the number
 inc counter
 
 cpx #0 
 beq end_division16sign
 
 xgdx ; D = the quotient required for the next division
 ldx #10 ; X =10
 idiv ; D/10 Quotient ? X, Remainder ? D
 pshb  ; save the number
 inc counter
 
 cpx #0 
 beq end_division16sign

 
 xgdx ; D = the quotient required for the next division
 pshb  ; save the number
 inc counter
 
end_division16sign:

 ldaa #0
 cmpa counter
 beq end_pull16sig

 pulb
 addb #$30
 stab 0,y
 iny
 dec counter
 bra end_division16sign      

end_pull16sig
 ldaa #$0
 staa 0,y
  puly
 pulx

 rts      


;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------


 ; the subroutine B2D_16bits_unsigned converts binary number stored in register D to ASCII and store the result starting from the memory location pointed by Y, the end will be 0.
; The number is unsigned.
 ;--------------------------------------------------------------------------------------------------------------------------------------
 
B2D_16bits_unsigned
 pshx
 pshy
  
  movb #$0,counter
  ldx #10 ;X =10
  
  idiv ;D/X Quotient ? X, Remainder ?D
  pshb
  inc counter
  
  cpx #0
  beq end_division16
 
           
 xgdx ; D = the quotient required for the next division
 ldx #10 ; X =10
 idiv ; D/10 Quotient ? X, Remainder ? D
 pshb
 inc counter
 
 cpx #0
 beq end_division16
 
 xgdx ; D = the quotient required for the next division
 ldx #10 ; X =10
 idiv ; D/10 Quotient ? X, Remainder ? D
 pshb
 inc counter
 
 cpx #0
 beq end_division16
 
 
 xgdx ; D = the quotient required for the next division
 ldx #10 ; X =10
 idiv ; D/10 Quotient ? X, Remainder ? D
 pshb
 inc counter
 
 cpx #0
 beq end_division16

 xgdx ; D = the quotient required for the next division
 pshb
 inc counter
 
 
end_division16:

 ldaa #0
 cmpa counter
 
 beq end_pull16

 pulb
 addb #$30
 stab 0,y
 iny
 dec counter
 
 bra end_division16      

end_pull16
 ldaa #$0
 staa 0,y
 puly
 pulx
 rts                       
 


;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------


  ; the subroutine B2D_8bits_unsigned converts binary number stored in register B to ASCII and stores the result starting from the memory location pointed by Y, the end will be 0.
; The number is unsigned and 8 bits.
 ;--------------------------------------------------------------------------------------------------------------------------------------
  
B2D_8bits_unsigned
 pshx
 pshy
 psha


 
 movb #0,counter
 
 ldx #10 ;X =10
  clra
  idiv ;D/X Quotient ? X, Remainder ?D
  pshb
  inc counter
  
  cpx #0
  beq _end_div
 
           
 xgdx ; D = the quotient required for the next division
 ldx #10 ; X =10
 idiv ; D/10 Quotient ? X, Remainder ? D
 pshb
 inc counter
 
 cpx #0
 beq _end_div
  
 xgdx ; D = the quotient required for the next division
 pshb
 inc counter
 
 
 
 
_end_div:

 ldaa #0
 cmpa counter
 
 beq end_pulls

 pulb
 addb #$30
 stab 0,y
 iny
 dec counter
 
 bra _end_div        

end_pulls
 ldaa #$0
 staa 0,y
 pula
 puly 
 pulx
 rts                                                  
 

  
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
  ; the subroutine B2D_8bits_signed converts binary number stored in register B to ASCII and stores the result starting from the memory location pointed by Y, the end will be 0.
; The number is signed and 8 bits.
 ;--------------------------------------------------------------------------------------------------------------------------------------
 ;--------------------------------------------------------------------------------------------------------------------------------------
 
B2D_8bits_signed
 pshx
 pshy
 psha
 
 movb #0,counter ; A counts the number of digits 
 
 cmpb #0
 BGE positive

negative
 ldaa #45 
 staa 0,Y
 iny
 negb

positive
 ldx #10 ;X =10
 clra
  idiv ;D/X Quotient ? X, Remainder ?D
  pshb
  inc counter
  
  cpx #0
  beq _end_division
           
 xgdx ; D = the quotient required for the next division
 ldx #10 ; X =10
 idiv ; D/10 Quotient ? X, Remainder ? D
 pshb
 inc counter
 
 cpx #0
 beq _end_division
  
 xgdx ; D = the quotient required for the next division
 pshb
 inc counter
 

_end_division:
 ldaa #0
 cmpa counter
 
 beq _end_pulls

 pulb
 addb #$30
 stab 0,y
 iny
 dec counter
 
 bra _end_division        

_end_pulls
 ldaa #$0
 staa 0,y
 
 pula
 puly
 pulx

 rts 


;---------------------------------------------------------------------------------------------------------------------------------------
; get_number
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------

get_number
 pshx
 pshy
 psha
 pshb
                                                                                           
begin:     JSR keypad  ;  '*'  for negative '#' to Enter
           cmpa #$2A ; '*'
           beq negati
           cmpa #$23    ;'#'
           beq enter
           cmpa #$30
           blo begin
           cmpa #$39
           bhi begin
           staa 1,y+
           bra begin
           
negati: movb #$2D,1,y+  ; storing negative ascii value at menory location y
        bra begin
        
enter:  
        movb #0,0,y ; storing '0' at memory location y
 pulb
 pula
 puly
 pulx

        rts

;---------------------------------------------------------------------------------------------------------------------------------------
; Delay_yms
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
Delay_yms: 
 pshx
 pshy
 psha
 pshb
 

outerloop: ldx #1000
innerloop: psha ; 2 E cycles
 pula ; 3 E cycles
 psha ; 2 E cycles
 pula ; 3 E cycles
 psha ; 2 E cycles
 pula ; 3 E cycles
 psha ; 2 E cycles
 pula ; 3 E cycles
 nop ; 1 E cycle
 dbne x,innerloop
 dbne y,outerloop

 pulb
 pula
 puly
 pulx

 rts
 
;---------------------------------------------------------------------------------------------------------------------------------------
; CONFIGLCD
;---------------------------------------------------------------------------------------------------------------------------------------
;--------------------------------------------------------------------------------------------------------------------------------------- 
CONFIGLCD: 
 pshx
 pshy
 psha
 pshb
 
	MOVB #$FF,DDRK	; configure port K for output	
	LDY #$10
	JSR  Delay_yms		  	
		  
	LDAA	#$28	
	JSR	  CMD2LCD    	   		
		  
	LDAA	#$0E     	
    JSR	  CMD2LCD		
		  
	LDAA	#$01     	
	JSR	  CMD2LCD    	
	
	LDY #$10
	JSR  Delay_yms		  
	LDAA	#$06     	
	JSR	  CMD2LCD    		  
	
	LDY #$05
	JSR Delay_yms
	
	pulb
 pula
 puly
 pulx
	RTS
   	
;---------------------------------------------------------------------------------------------------------------------------------------
; CMD2LCD
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------     
CMD2LCD: 
 pshx
 pshy
 psha
 pshb
               		
		  PSHA            ; save the command in the stack		
		  ANDA  #$F0      ; Clear the lower 4 bits
		  LSRA            ; match the upper 4 bits with the LCD
		  LSRA            ; data pins
		  STAA  PORTK
		  BCLR  PORTK,#$01   ;Select the instruction register in RS 	
		  BSET  PORTK,#$02   ;EN = high
		  ; the command has been sent with RS and EN
		  		   	
		  NOP  ; 3 NOP to extend the duration of EN
		  NOP
		  NOP				
		  BCLR  PORTK,#$02 ;EN   ; EN = LOW
		  	
		  ; repeat previous step for the first half of the command byte.
		  PULA
		  ANDA  #$0F
    	LSLA
    	LSLA
  		STAA  PORTK
		  BCLR  PORTK,#$01   ;RS 	
		  BSET  PORTK,#$02 ;EN 	
		  NOP
		  NOP
		  NOP				
		  BCLR  PORTK,#$02 ;EN 	
		  
		  ; delay is needed until the LCD does all the interbnal operations
		  LDY #$07
		  JSR Delay_yms
		  
		  
 pulb
 pula
 puly
 pulx	  
		  RTS
;---------------------------------------------------------------------------------------------------------------------------------------
; PUTCLCD:
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------     
PUTCLCD:
 pshx
 pshy
 psha
 pshb
                    	
		  PSHA		    ; save a copy of the data in the stack		
		  ANDA   #$F0  ; Clear the lower 4 bits
		  LSRA
		  LSRA
		  STAA   PORTK
		  BSET   PORTK,#$01   ;RS  select LCD data register	
		  BSET   PORTK,#$02 ;EN = high	
		  NOP
		  NOP
		  NOP				
		  BCLR   PORTK,#$02 ;EN = low 	
		  
		  PULA
		  ANDA   #$0F
    	  LSLA
          LSLA
  		  STAA   PORTK
  		  BSET   PORTK,#$01  ;RS select LCD data register
		  BSET   PORTK,#$02 ;EN = high	
		  NOP
		  NOP
		  NOP				
		  BCLR   PORTK,#$02 ;EN  ; E = low to complete the write cycle
		   
		   ; delay is needed until the LCD does all the interbnal operations
		  LDY #$07
		  JSR Delay_yms
	pulb
 pula
 puly
 pulx
		  RTS

		  
;---------------------------------------------------------------------------------------------------------------------------------------
; PUTSLCD:
;---------------------------------------------------------------------------------------------------------------------------------------
;--------------------------------------------------------------------------------------------------------------------------------------- 		  
PUTSLCD: 
 pshx
 pshy
 psha
 pshb
                   	
		  
NEXT: LDAA 1,X+
		BEQ DONEPS 
		JSR PUTCLCD
		  	
		BRA NEXT
		  
DONEPS: 

 pulb
 pula
 puly
 pulx

 rts

;---------------------------------------------------------------------------------------------------------------------------------------
; keypad:
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
keypad:
 pshx
 pshy
 pshb
 
; Read one character and returns it in A    
   MOVB #$F0,DDRA         ; MAKE PORT A HIGH NIBLE OUTPUT -- LOW NIBLE INPUT
;; 2- CHECK IF A SWITCH IS PRESSED

K1:                   ;TEST TO MAKE SURE NO BUTTON PRESSED
   MOVB #%11110000,PORTA  ;SET ROWS HIGH
   
   LDAA PORTA         ;CAPTURE PORT A
   ANDA #%00001111        ;MASK OUT ROWS
   
   CMPA #$00         ;
   BNE K1           ;IF COLUMS IS ZERO NO BUTTON PRESSED
                      ;DO NOT MOVE ON UNTILL NO BUTTON IS PRESSED

;A SWITCH MAY BE PRESSED
;FOR DEBOUNCING, WAIT 15ms AND CHECK AGAIN

K2:                   ;
   LDY 20
   JSR Delay_yms
   LDAA  PORTA         ;
   ANDA  #%00001111        ;
   CMPA  #$00         ;IF COLS !=0 THEN A BUTTON IS PRESSED
  ; BNE   OVER         ;
   ;BRA   K2           ;IF NO BUTTON PRESSED KEEP CHECKING
  BEQ K2

OVER:                 ;
   LDY 20
   JSR Delay_yms
   
   LDAA  PORTA         ;READ PORT A
   ANDA  #%00001111        ;MASK OUT ROWS
   CMPA  #$00         ;CHECK FOR PRESS AFTER DEBOUNCE
   
   BEQ K2           ;IF NO PRESS AFTER DEBOUNCE GO BACK
   
  ;IF PRESSED GO FIND WHAT ROW

;---------------------------------------------------------------------------------
;; 3- A SWITCH IS PRESSED

;; WHICH SWITCH IS PRESSED

   ;IF PRESSED GO FIND WHAT ROW
   
OVER1:

;;;;;      test Row 0
                ;
   LDAA  #%00010000        ;MAKE HIGH ROW0 THE REST GROUNDED
   STAA  PORTA         ;
   LDAB #$08 ;SET COUNT TO PROVIDE SHORT DELAY FOR STABILITY
P1:                   ;AFTER CHANGING THE PORT A OUTPUT
   DECB        ;DECREMENT COUNT
   BNE   P1           ;IF COUNT NOT ZERO KEEP DECREMENTING

   LDAA  PORTA         ;READ PORTA
   ANDA  #%00001111        ;MASK OUT ROWS
   CMPA  #$00         ;IS INPUT ZERO?
   BNE   R0           ;IF COLUMS NOT ZERO THEN BUTTON IS IN ROW 0
   
   
;;;;;      test Row 1
   
   LDAA  #%00100000        ;IF ZERO THEN BUTTON NOT IN ROW0
   STAA  PORTA         ;TURN ON ROW 1 TURN OFF ALL OTHERS
   LDAB #$08 ;SHORT DELAY TO STABALIZE

P2:                   ;AFTER CHANGING THE PORT A OUTPUT
   DECB       ;DECREMENT COUNT
   BNE   P2           ;IF COUNT NOT ZERO KEEP DECREMENTING
   LDAA  PORTA         ;READ PORT A
   ANDA  #%00001111        ;MASK OUT ROWS
   CMPA  #$00         ;CHECK FOR KEY PRESS
   BNE   R1           ;IF PRESSED KEY IS IN ROW1
   
;;;;;      test Row 2
   
   
   LDAA  #%01000000        ;IF ZERO BUTTON NOT IN ROW1
   STAA  PORTA         ;TURN ON ROW2 ALL OTHERS OFF
   LDAB #$08  ;SHORT DELAY TO STABALIZE PORTA
P3:                   ;
   DECB       ;DECREMENT COUNT
   BNE   P3           ;DELAY LOOP 
   LDAA  PORTA         ;READ PORTA
   ANDA  #%00001111        ;MASK OUT ROWS
   CMPA  #$00         ;CHECK FOR PRESS
   BNE   R2           ;IF FOUND KEY IS IN ROW2
   
;;;;;      test Row 3
   LDAA  #%10000000        ;IF ZERO MOVE TO ROW3
   STAA  PORTA         ;TURN ON ROW3 ALL OTHERS OFF
   LDAB #$08  ;SHORT DELAY TO STABALIZE OUTPUT
P4:                   ;
   DECB        ;DECREMENT DELAY
   BNE   P4           ;DELAY LOOP
   LDAA  PORTA         ;READ PORT A
   ANDA  #%00001111        ;MASK OUT ROWS
   CMPA  #$00         ;CHECK FOR PRESS
   BNE   R3           ;IF FOUND KEY IN ROW3
   BRA   K2           ;IF ROW NOT FOUND GO BACK TO START     	
R0:                   ;
   LDX   #KCODE0      ;LOAD PONTER TO ROW0 ARRAY	
   BRA   FIND         ;GO FIND COLUMN	 	
R1:                   ;
   LDX   #KCODE1      ;LOAD POINTER TO ROW1 ARRAY	
   BRA   FIND         ;GO FIND COUMN		
R2:                   ;
   LDX   #KCODE2      ;LOAD PINTER TO ROW2
   BRA   FIND         ;GO FIND COLUMN
R3:                   ;
   LDX   #KCODE3      ;LOAD POINTER TO ROW3
   BRA   FIND         ;GO FIND COLUMN

FIND:                 ;
   ANDA  #%00001111        ;MASK OUT ROWS   A = 0000 0001 or A = 0000 0010 or A = 0000 0100 or A = 0000 1000
SHIFT:                ;
   LSRA               ;LOGICAL SHIFT RIGHT PORTA
   BCS MATCH        ;IF CARY SET COLUM IS FOUND
   INX                ;IF CARY NOT CLEAR INCREMENT POINTER TO ROW ARRAY
   BRA   SHIFT        ;SHIFT RIGHT UNTIL CARY IS CLEAR.

MATCH:                ;
   LDAA  0,X          ;LOAD ASCII FROM ROW ARARAY
  
  
 pulb
 puly
 pulx

 rts

KCODE0 DC.B '123A' 
KCODE1 DC.B '456B' 
KCODE2 DC.B '789C' 
KCODE3 DC.B '*0#D'


  ;---------------------------------------------------------------------------------------------------------------------------------------
; Delay_yus
;---------------------------------------------------------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------------------------------------------------------
Delay_yus: 
 
outer_loop: 
 psha ; 2 E cycles
 pula ; 3 E cycles
 psha ; 2 E cycles
 pula ; 3 E cycles
 psha ; 2 E cycles
 pula ; 3 E cycles
 psha ; 2 E cycles
 pula ; 3 E cycles
 nop ; 1 E cycle
 dbne y,outer_loop


 rts

 
 
 
 
 
 
 
 