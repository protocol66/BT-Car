#include <hidef.h>      /* common defines and macros */
#include <mc9s12dg256.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
 
int val16;  //16 bit integer
long val32;  //32 integer

void main(void) {
PLL_init();
Lcd_init();
_asm(cli);

val16 = 55301;
set_lcd_addr(0x0);       
write_int_lcd(val16); //convert val16 to ASCII digits and display on LCD

val32 = 654325530;
set_lcd_addr(0x40);       
write_long_lcd(val32); //convert val132 to ASCII digits and display on LCD

 while(1){} /* wait forever */ }
