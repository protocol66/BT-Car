#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void)
{

int i;
PLL_init(); // set system clock frequency to 24 MHz
//led_disable();

DDRT = DDRT | 0b00100000; // PTT5 as output

_asm(cli);

while(1)
{
for (i=1;i<=250;i++){
  
PTT = PTT | 0x20; //make PT5=1
ms_delay(1); //change the delay size to see what

PTT = PTT & 0xDF; //Make PT5=0
ms_delay(1); //change delay size....
}
for (i=1;i<=125;i++){
  
PTT = PTT | 0x20; //make PT5=1
ms_delay(2); //change the delay size to see what

PTT = PTT & 0xDF; //Make PT5=0
ms_delay(2); //change delay size....
}

}
}