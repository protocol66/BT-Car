#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void)
{
int i;
PLL_init(); // set system clock frequency to 24 MHz
seg7_disable();
led_enable();
_asm(cli); //enable interrupts

while(1)
{
for(i=7; i>=0;i--)
{
led_on(i); // LED i is on
ms_delay(500); // wait 500 ms
led_off(i);
ms_delay(500);
}

for(i=1; i<=6;i++)
{
led_on(i);
ms_delay(500);
led_off(i);
ms_delay(500);
}
}
}