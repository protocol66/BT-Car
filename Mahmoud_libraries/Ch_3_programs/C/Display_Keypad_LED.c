#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void) {
int c =0;
 const char  Asc[] = { 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46};
PLL_init();
led_enable ();
seg7_disable();
keypad_enable(); //initialization to the keypad
_asm(cli); //enable interrupts
 
while(1)
{
c = getkey(); // c is the key number
leds_on(Asc[c]);  // Asc[c] gives the ASCII of the key
wait_keyup(); //wait until the key is released
}
}