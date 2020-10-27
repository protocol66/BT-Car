#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void)
{
int i;
const char digits[] = {0x3F, 0x06, 0x5B, 0x4F,0x66, 0x6D, 0x7D,0x07,0x7F, 0x6F};
PLL_init();
led_disable();
seg7_enable();
_asm(cli);
while(1)
{
for(i=0; i<=9; i++)
{
seg7_on(digits[i], 0); // display the segments s on

ms_delay(1000);
}
} }