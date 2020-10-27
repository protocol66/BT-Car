#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void)
{
PLL_init(); // set system clock frequency to 24 MHz
DDRB = 0xff; // Port B is output
DDRJ = 0xff; // Port J is output
DDRP = 0xff; // Port P is output
PTJ = 0x00; // enable LED
PTP = 0xFF; // disable all 7-segment displays
_asm(cli); //enable interrupts

while(1) //loop forever
{ led_on(0x00); // Bit 0 in Port B is on
ms_delay(1000); // ms_delay(delay in ms)
led_off(0x0); // Bit 0 in Port B is off
ms_delay(1000); } }