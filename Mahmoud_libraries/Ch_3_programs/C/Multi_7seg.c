//Program to display 3456 on 7seg display
#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void)
{
const char digits[] = {3, 4, 5, 6};
int i;
PLL_init();
led_disable();
seg7_enable();
_asm(cli); //enable interrupts

while(1)
{
for(i=0; i<4; i++)
{
seg7dec(digits[i], i); // segment number 0 is the one

ms_delay(5);
}
}
} 