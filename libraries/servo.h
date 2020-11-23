#ifndef SERVO_H
#define SERVO_H

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
//#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
//#include "main_asm.h"

#define SERVO_SCALE_FACTOR 28   //scaling factor is divided by 100
#define SERVO_INIT_VAL 0

int init_servo(const unsigned short);
int set_servo(const unsigned short, const short);
void reset_all_servos();
void stop_all_servos();

//initializes 2 pwms into 1 16bit pwm
//valid servo numbers 1,3,5,7
//return 0 = success, 1 = invalid servo number, 2 = SPI is running
int init_servo(const unsigned short servo_num)  {

    PWMPOL = 0xFF;        //set duty cycle = on time
    PWMCLK = 0x00;        //set pwm 1 to use clock A, because reasons...
    PWMPRCLK = 0x33;      //set prescaler for both clock A and B to 24/8 = 3MHz
    PWMCAE = 0x0;         //set left allign
    PWMCTL |= 0xF0;       //concatinate pwm 0 and 1, 2 and 3, 4 and 5, 6 and 7; to 16 bit pwm

    switch (servo_num)
    {
        case 1:
            if(SPI1CR1_SPE)              //SPI1 and PWM 1-3 cannot run at the same time 
              return 2;
            PWMPER01 = 60000;        //3MHz / 60,000 = 20ms
            set_servo(1, SERVO_INIT_VAL);        //set servo to 50 percent
            PWME |= 0x03;            //enable pwm on port
            break;

        case 3:
            if(SPI1CR1_SPE)
              return 2;
            PWMPER23 = 60000;
            set_servo(3, SERVO_INIT_VAL);
            PWME |= 0x0C;
            break;

        case 5:
            if(SPI2CR1_SPE)             //SPI2 and PWM 4-7 cannot run at the same time
              return 2;
            PWMPER45 = 60000;
            set_servo(5, SERVO_INIT_VAL);
            PWME |= 0x30;
            break;

        case 7:
            if(SPI2CR1_SPE)
              return 2;
            PWMPER67 = 60000;
            set_servo(7, SERVO_INIT_VAL);
            PWME |= 0xC0;
            break;

        default:
            return 1;
            break;
    }

    return 0;
}

//servo_num number of servo, valid servo numbers 1,3,5,7 aka PP pins
// servo min=-100 max =100
//return 0 = success, 1 = invalid servo number 
int set_servo(const unsigned short servo_num, const short pos_input)  {

    int tmp = pos_input * 15 * SERVO_SCALE_FACTOR; //new_pwm = 4500 + input*15*scaling_factor,
    short new_pwm = (4500 + tmp/100);                // where 3000 = 1ms and scaling_factor accounts for the max wheel speed
    switch (servo_num)                                                  
    {
        case 1:
            PWMDTY01 = new_pwm;
            break;

        case 3:
            PWMDTY23 = new_pwm;
            break;

        case 5:
            PWMDTY45 = new_pwm;
            break;

        case 7:
            PWMDTY67 = new_pwm;
            break;

        default:
            return 1;
            break;
    }

    return 0;

}

//disables all pwm
void stop_all_servos()  {
    PWMPER0 = 0x00;
    PWMPER1 = 0x00;
    PWMPER2 = 0x00;
    PWMPER3 = 0x00;
    PWMPER4 = 0x00;
    PWMPER5 = 0x00;
    PWMPER6 = 0x00;
    PWMPER7 = 0x00;

    PWMDTY0 = 0x00;
    PWMDTY1 = 0x00;
    PWMDTY2 = 0x00;
    PWMDTY3 = 0x00;
    PWMDTY4 = 0x00;
    PWMDTY5 = 0x00;
    PWMDTY6 = 0x00;
    PWMDTY7 = 0x00;
}

//disables all pwm and resets the values
void reset_all_servos() {
    PWME = 0x00;
    PWMPOL = 0x00;
    PWMCLK = 0x00;
    PWMPRCLK = 0x00;
    PWMCAE = 0x00;
    PWMCTL = 0x00;
    stop_all_servos();
}

void set_clock_24mhz(void){
   CLKSEL &= 0x7F;
   PLLCTL |= 0x40;
   SYNR  = 0x05;
   REFDV = 0x01;
   /* REFDV=0x00;   for 4 MHz */
   /* REFDV=0x01;   for 8 MHz  */
   /* REFDV=0x03;   for 16 MHz */
   while(!(0x08 & CRGFLG));    CLKSEL |= 0x80;
}

#endif
