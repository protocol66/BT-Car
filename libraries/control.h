#ifndef CONTROL_H
#define CONTROL_H

#include "servo.h"

void control(unsigned char input)  {
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

#endif