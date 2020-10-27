#include <hidef.h>      /* common defines and macros */
#include <mc9s12dg256.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */

void main (void)
{ unsigned char led_tab[16]= {0x80,0x40,0x20,0x10,0x08,0x04,0x02,
                      0x01, 0x01,0x02,0x04,0x08,0x10,0x20,0x40};
	char i; 
	DDRB	= 0xFF;	// configure Port B for output
	DDRJ	|= 0x02;	// configure PJ1 pin for output
	PTJ  	&= 0xFD;    // enable LEDs to light
	seg7_disable();
	 _asm(cli); 
		while (1) {
		for (i = 0;i < 16; i++) {
		PORTB = led_tab[i]; // output a new LED pattern
			ms_delay(500); // wait for approx. 500 ms}
   	}
} 
}