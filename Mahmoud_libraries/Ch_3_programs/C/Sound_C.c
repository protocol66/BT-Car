#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */



int count;



void interrupt 13 anyname(){
count=count+1;
if (count<100){
  
tone(2867);
}
if( count>100 && count<200 ) {
  
tone(717);
}
if( count>200){
  
 tone(1434);  
}
}


void main (void){
  PLL_init();
  count=0;
  _asm(cli);
  sound_init();
  sound_on();
    
  while(1){
   
  }
  
}
    