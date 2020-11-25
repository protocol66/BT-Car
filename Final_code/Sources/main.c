#include <hidef.h> /* common defines and macros */
#include "mc9s12dg256.h" /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
//#include "main_asm.h" /* interface to the assembly module */
#include "serial.h"
#include "control.h"


//void interrupt 7 RTI_ISR()  {
//    control(serial_recieve());
//    clear_RTI_flag();
//}

void main(void) {
    long i = 0;
    /* put your own code here */
    set_clock_24mhz();
    // seg7_disable();
    // led_disable();
    // RTI_init();
    RTICTL = 0x7F;

    reset_all_servos();
    init_servo(1);          // initialize servos
    init_servo(3);
    init_servo(5);
    init_servo(7);

    serial_init();

    EnableInterrupts;

    while(1)  {
        control(serial_recieve());
        for (i = 0; i < 60000; i++);
            _FEED_COP();
    }
}

