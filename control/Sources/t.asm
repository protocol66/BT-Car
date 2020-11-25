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

 dc.b $4A ;inital value of [$1000]





; code section

            ORG   ROMStart





Entry:

_Startup:

            LDS   #RAMEnd+1       ; initialize the stack pointer



            CLI                     ; enable interrupts

mainLoop:

      ; Register A is a counter for the loop

        ldaa #6

      ; Loop until counter is 0, then go to end 

      loop: dbeq a,end

      ; Logical shift left byte at [$1000]

            lsl $1000

            bra loop

      end: 