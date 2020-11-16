/** ###################################################################
**     Filename  : MyPWMChannel0.C
**     Project   : MyPWMChannel0
**     Processor : MC9S12DP256BCPV
**     Version   : Driver 01.04
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 08.08.2003, 12:23
**     Abstract  :
**         Main module. 
**         Here is to be placed user's code.
**     Settings  :
**     Contents  :
**         No public methods
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2002
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE MyPWMChannel0 */

/* Including used modules for compilling procedure */
#include "Cpu.h"
#include "PWM8.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

volatile static byte pwmChannel[1];
volatile static unsigned int pwmRatio= 6939;
void main(void) {
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /*Write your code here*/
  for(;;) {
	pwmChannel[0]= PTP_PTP0;
	(void)PWM8_SetRatio16(pwmRatio);
  }

  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
    for(;;);
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END MyPWMChannel0 */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 03.29 for 
**     the Motorola HCS12 series of microcontrollers.
**
** ###################################################################
*/
