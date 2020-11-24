#include <hidef.h> /* common defines and macros */
#include <mc9s12dg256.h> /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
#include "Servo.h"

// forward = 8% left 6% right 
// PP1 = FL; PP3 = FR; PP5 = BL; PP7 = BR 
// L = 0x22; R = 0x88; ALL = 0xAA

unsigned short input;

//unsigned short right_adjust = ;
//unsigned short left_adjust = 1;

void main(void)
{
	PLL_init();
	set_clock_24mhz();
	SW_enable();
	
	_asm(cli); 	      	//enable interrupts
	
  init_servo(1);          // initialize servos
  init_servo(3);
  init_servo(5);
  init_servo(7);

	while(1)
	{
		input = SW1_dip();
	    
		if(input == 1)			// forward slow
    	{					         	
    		set_servo(1,50);
    		set_servo(3,-43);
    		set_servo(5,50);
    		set_servo(7,-43);
    	}
		
    	else if(input == 2)			// forward fast
    	{					         	
			set_servo(1,-100);
			set_servo(3,90);
			set_servo(5,-100);
			set_servo(7,90);
    	}

    	else if(input == 3)		// turn left slow
    	{					          	
			set_servo(1,0);
    		set_servo(3,-43);
    		set_servo(5,0);
    		set_servo(7,-43);
    	}
		
		else if(input == 4)		// turn left fast
    	{					          	
			set_servo(1,0);
    		set_servo(3,90);
    		set_servo(5,0);
    		set_servo(7,90);
    	}

    	else if(input == 5)		// turn right slow
    	{					          	
			set_servo(1,50);
    		set_servo(3,0);
    		set_servo(5,50);
    		set_servo(7,0);
    	}
		
		else if(input == 6)		// turn right fast
    	{					          	
			set_servo(1,-100);
    		set_servo(3,0);
    		set_servo(5,-100);
    		set_servo(7,0);
    	}

    	else if(input == 7)		// backwards slow
    	{					          	
			set_servo(1,-50);
    		set_servo(3,43);
    		set_servo(5,-50);
    		set_servo(7,43);
    	} 

    	else if(input == 8)		// backwards fast
    	{					          	
			set_servo(1,100);
    		set_servo(3,-90);
    		set_servo(5,100);
    		set_servo(7,-90);
    	}

		else if(input == 9)		// backwards left slow
    	{					          	
			set_servo(1,0);
    		set_servo(3,43);
    		set_servo(5,0);
    		set_servo(7,43);
    	} 

    	else if(input == 10)	// backwards left fast
    	{					          	
			set_servo(1,0);
    		set_servo(3,-90);
    		set_servo(5,0);
    		set_servo(7,-90);
    	}
		
		else if(input == 11)	// backwards right slow
    	{					          	
			set_servo(1,-50);
    		set_servo(3,0);
    		set_servo(5,-50);
    		set_servo(7,0);
    	} 

    	else if(input == 12)	// backwards right fast
    	{					          	
			set_servo(1,100);
    		set_servo(3,0);
    		set_servo(5,100);
    		set_servo(7,0);
    	}
		
		else if(input == 13)	// donut left
    	{					          	
			set_servo(1,-100);
			set_servo(3,90);
			set_servo(5,0);
			set_servo(7,90);
    	} 

    	else if(input == 14)	// donut right
    	{					          	
			set_servo(1,-100);
			set_servo(3,90);
			set_servo(5,-100);
			set_servo(7,0);
    	}
		
		else				        	// stay still
    	{	
			set_servo(1,0);
    		set_servo(3,0);
    		set_servo(5,0);
    		set_servo(7,0);
    	} 
	}
}

