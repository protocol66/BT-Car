// Program to display 0 to 9 on 7-segment display continuously
#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void)
{
int i;
PLL_init();
led_disable();
seg7_enable();
_asm(cli);
while(1)
{
for(i=0; i<=9;i++)
{
seg7dec(i, 0);
ms_delay(500);
}
}
}