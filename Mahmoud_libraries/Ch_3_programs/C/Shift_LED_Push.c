#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void) {
PLL_init(); // set system clock frequency to 24 MHz
led_enable();
seg7_disable();
PORTB = 0x01;
_asm(cli); //enable interrupts

while(1)
{
if(SW2_down())
{
PORTB = PORTB << 1;
if (PORTB == 0) {PORTB = 0x01;}
ms_delay(25);
while(SW2_down()) {} //wait until switch is

ms_delay(25);
}}}