#ifndef CONTROL_H
#define CONTROL_H

#include "servo.h"

void control(unsigned char input)  {
	if(input == 0x04)			// forward slow
	{					         	
		set_servo(1,50);
		set_servo(3,-43);
		set_servo(5,50);
		set_servo(7,-43);
	}
	
	else if(input == 0x02)			// forward fast
	{					         	
		set_servo(1,-100);
		set_servo(3,90);
		set_servo(5,-100);
		set_servo(7,90);
	}

	else if(input == 0x0C)		// turn left slow
	{					          	
		set_servo(1,0);
		set_servo(3,-43);
		set_servo(5,0);
		set_servo(7,-43);
	}
	
	else if(input == 0x0A)		// turn left fast
	{					          	
		set_servo(1,0);
		set_servo(3,90);
		set_servo(5,0);
		set_servo(7,90);
	}

	else if(input == 0x14)		// turn right slow
	{					          	
		set_servo(1,50);
		set_servo(3,0);
		set_servo(5,50);
		set_servo(7,0);
	}
	
	else if(input == 0x12)		// turn right fast
	{					          	
		set_servo(1,-100);
		set_servo(3,0);
		set_servo(5,-100);
		set_servo(7,0);
	}

	else if(input == 0x08)		// backwards slow
	{					          	
		set_servo(1,-50);
		set_servo(3,43);
		set_servo(5,-50);
		set_servo(7,43);
	} 

	else if(input == 0x06)		// backwards fast
	{					          	
		set_servo(1,100);
		set_servo(3,-90);
		set_servo(5,100);
		set_servo(7,-90);
	}

	else if(input == 0x18)		// backwards left slow
	{					          	
		set_servo(1,0);
		set_servo(3,43);
		set_servo(5,0);
		set_servo(7,43);
	} 

	else if(input == 0x16)	// backwards left fast
	{					          	
		set_servo(1,0);
		set_servo(3,-90);
		set_servo(5,0);
		set_servo(7,-90);
	}
	
	else if(input == 0x1C)	// backwards right slow
	{					          	
		set_servo(1,-50);
		set_servo(3,0);
		set_servo(5,-50);
		set_servo(7,0);
	} 

	else if(input == 0x1A)	// backwards right fast
	{					          	
		set_servo(1,100);
		set_servo(3,0);
		set_servo(5,100);
		set_servo(7,0);
	}
	
	else if(input == 0x22)	// donut left
	{					          	
		set_servo(1,-100);
		set_servo(3,90);
		set_servo(5,0);
		set_servo(7,90);
	} 

	else if(input == 0x24)	// donut right
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


#endif