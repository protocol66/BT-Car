#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void) {
int i;
PLL_init(); // set system clock frequency to 24 MHz
seg7_disable();
led_enable();
_asm(cli);
while(1)
{
for(i=0; i<=255;i++)
{
leds_on(i); //PORTB = i
ms_delay(1);
} } }