#include <hidef.h>      /* common defines and macros */
#include <mc9s12dg256.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
 
void main(void) 
{
    char* q1;
    char* q2;
    q1 = "Welcome to 3120";
    q2 = "Prof. Mahmoud";
    
    PLL_init(); 

    lcd_init();  //initialize the LCD for 4bit, two lines, …
    _asm(cli); //enable interrupts
	
    set_lcd_addr(0x1); //set the cursor at position 1 line 1
    type_lcd(q1); //wrire q1 starting from position 1 line 1
    set_lcd_addr(0x41); //set the cursor at position 1 line 2
    type_lcd(q2); //wrire q2 starting from position 1 line 2
    
 while(1) {} /* wait forever */
}
