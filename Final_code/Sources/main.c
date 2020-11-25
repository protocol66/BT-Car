#include <hidef.h> /* common defines and macros */
#include "mc9s12dg256.h" /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
//#include "main_asm.h" /* interface to the assembly module */
#include "serial.h"
#include "control.h"


void interrupt 7 RTI_ISR()  {
    clear_RTI_flag();
    control(serial_recieve());
}

void main(void) {
    /* put your own code here */
    PLL_init();
    seg7_disable();
    led_disable();
    RTI_init();
    RTICTL = 0x7F;

    init_servo(1);          // initialize servos
    init_servo(3);
    init_servo(5);
    init_servo(7);

    serial_init();

    EnableInterrupts;

    while(1)  {
        _FEED_COP();
    }
}

