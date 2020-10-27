//program to monitor switches and turn on LED respectively.
#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void)
{
PLL_init(); // set system clock frequency to 24 MHz
led_enable(); // enable LEDs
seg7_disable(); // disable 7 segment
DDRH = 0x00; //port H as inputs
_asm(cli); //enable interrupts

while(1)
{
leds_on(~PTH); // PORTB = ~PTH
}
}
