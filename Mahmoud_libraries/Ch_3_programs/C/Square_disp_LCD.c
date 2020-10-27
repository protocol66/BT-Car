#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
void main(void)
{
long num1, num2;
char* ptr;
//char buff[];
 char  buff[12]; 


int i;
char c, a;
PLL_init();
lcd_init();
keypad_enable();

set_lcd_addr(0x00);
ptr = buff;
i = 0;
_asm(cli);

while(1){
c = getkey();
a= hex2asc(c);
buff[i]=a;
if (c < 10){
data8(a);
wait_keyup();
i++;}
else{
switch(c){
case 0xE:
num1=number(ptr);
num2=num1*2;
set_lcd_addr(0x40);
write_long_lcd(num2);
wait_keyup();
i=0;
set_lcd_addr(0x00);
break;
case 0xF:
clear_lcd();
wait_keyup();
i=0;
set_lcd_addr(0x00);
break;
Default:
break;}}}}