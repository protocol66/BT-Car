#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */

void main(void)
{
 byte mask = 0x80;
 byte pattern = 0b01001111;
 
 DDRT =DDRT|0x01;
 _asm(cli); //enable interrupts
 
 while(1) {
  
 if((pattern&mask) ==0)
  PTT=PTT&0xFE;
 else
 PTT=PTT|0x01;
 ms_delay(10);
 mask =mask >>1;
 if(mask ==0)
 mask = 0x80;
 
 }



}