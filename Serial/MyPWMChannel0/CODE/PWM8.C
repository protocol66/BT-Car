/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PWM8.C
**     Project   : MyPWMChannel0
**     Processor : MC9S12DP256BCPV
**     Beantype  : PWM
**     Version   : Bean 02.065, Driver 01.04, CPU db: 2.87.282
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 08.08.2003, 12:23
**     Abstract  :
**         This bean implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
**     Settings  :
**         Used output pin             : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       4             |  PP0_MISO1_PWM0_KWP0
**             ----------------------------------------------------
**
**         Timer name                  : PWM0 [8-bit] 
**         Counter                     : PWMCNT0   [172]
**         Mode register               : PWMCTL    [165]
**         Run register                : PWME      [160]
**         Prescaler                   : PWMPRCLK  [163]
**         Compare 1 register          : PWMPER0   [180]
**         Compare 2 register          : PWMDTY0   [188]
**         Flip-flop 1 register        : PWMPOL    [161]
**
**         User handling procedure     : not specified
**
**         Output pin
**
**         Port name                   : P
**         Bit number (in port)        : 0
**         Bit mask of the port        : 1
**         Port data register          : PTP       [600]
**         Port control register       : DDRP      [602]
**
**         Runtime setting period      : none
**         Runtime setting ratio       : calculated
**         Initialization:
**              Aligned                : Left
**              Output level           : low
**              Timer                  : Enabled
**              Event                  : Enabled
**         High-speed CPU mode
**             Prescaler               : divide-by-1
**             Clock                   : 2674 Hz
**           Initial value of            period        pulse width (ratio 10.58%)
**             Xtal ticks              : 1525920       161568
**             microseconds            : 95370         10098
**             milliseconds            : 95            10
**             seconds (real)          : 0.0953700     0.0100980
**
**     Contents  :
**         SetRatio16 - byte PWM8_SetRatio16(word Ratio);
**         SetDutyUS  - byte PWM8_SetDutyUS(word Time);
**         SetDutyMS  - byte PWM8_SetDutyMS(word Time);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2002
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


/* MODULE PWM8. */

#include "PWM8.h"

/* Definition of DATA and CODE segments for this bean. User can specify where
   these segments will be located on "Build options" tab of the selected CPU bean. */
#pragma DATA_SEG PWM8_DATA             /* Data section for this module. */
#pragma CODE_SEG PWM8_CODE             /* Code section for this module. */

static word RatioStore;                /* Ratio of L-level to H-level */


/*
** ===================================================================
**     Method      :  SetRatio (bean PWM)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
static void SetRatio(void)
{
  PWMDTY0 = (byte)((PWMPER0 * (dword)RatioStore) >> 16); /* Calculate new value according to the given ratio */
}

/*
** ===================================================================
**     Method      :  PWM8_SetRatio16 (bean PWM)
**
**     Description :
**         This method sets a new duty-cycle ratio.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Ratio      - Ratio is expressed as an 16-bit unsigned integer
**                      number. 0 - 65535 value is proportional
**                      to ratio 0 - 100%
**         Note: Calculated duty-cycle ratio depends on the timer
**               possibilities and on the selected period.
**     Returns     :
**         ---        - Error code
** ===================================================================
*/
byte PWM8_SetRatio16(word Ratio)
{
  RatioStore = Ratio;                  /* Store new value of the ratio */
  SetRatio();                          /* Calculate and set up new appropriate values of the duty and period registers */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  PWM8_SetDutyUS (bean PWM)
**
**     Description :
**         This method sets the new duty value of the output signal. The
**         duty is expressed in microseconds as a 16-bit unsigned integer
**         number.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Time       - Duty to set [in microseconds]
**                      (0 to 65535 us in high speed CPU mode)
**     Returns     :
**         ---        - Error code
** ===================================================================
*/
byte PWM8_SetDutyUS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */

  PE_Timer_LngMul((dword)Time,2951399567,&rtval); /* Multiply given value and high speed CPU mode coefficient */
  if (PE_Timer_LngHi4(rtval[0],rtval[1],&RatioStore)) /* Is the result greater or equal than 65536 ? */
    RatioStore = 65535;                /* If yes then use maximal possible value */
  SetRatio();                          /* Calculate and set up new appropriate values of the duty and period registers */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  PWM8_SetDutyMS (bean PWM)
**
**     Description :
**         This method sets the new duty value of the output signal. The
**         duty is expressed in milliseconds as a 16-bit unsigned integer
**         number.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Time       - Duty to set [in milliseconds]
**                      (0 to 95 ms in high speed CPU mode)
**     Returns     :
**         ---        - Error code
** ===================================================================
*/
byte PWM8_SetDutyMS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */

  if (Time >= 95)                      /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  PE_Timer_LngMul((dword)Time,45034783,&rtval); /* Multiply given value and high speed CPU mode coefficient */
  if (PE_Timer_LngHi2(rtval[0],rtval[1],&RatioStore)) /* Is the result greater or equal than 65536 ? */
    RatioStore = 65535;                /* If yes then use maximal possible value */
  SetRatio();                          /* Calculate and set up new appropriate values of the duty and period registers */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  PWM8_Init (bean PWM)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void PWM8_Init(void)
{
  PWMCNT0 = 0;
  RatioStore = 6939;                   /* Store initial value of the ratio */
  PWMDTY0 = 27;                        /* Store initial value to the duty-compare register */
  PWMPER0 = 255;                       /* and to the period register */
  /* PWMPRCLK: ??=0,PCKB2=0,PCKB1=0,PCKB0=0,??=0,PCKA2=0,PCKA1=1,PCKA0=1 */
  PWMPRCLK = 3;                        /* Set prescaler register */
  /* PWMSCLA: BIT7=1,BIT6=0,BIT5=1,BIT4=1,BIT3=1,BIT2=0,BIT1=1,BIT0=1 */
  PWMSCLA = 187;                       /* Set scale register */
  PWMCLK_PCLK0 = 1;                    /* Select clock source */
  PWME_PWME0 = 1;                      /* Run counter */
}

/* END PWM8. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 03.29 for 
**     the Motorola HCS12 series of microcontrollers.
**
** ###################################################################
*/
