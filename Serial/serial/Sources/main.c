#include <hidef.h>      /* common defines and macros */
#include "mc9s12dg256.h"
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"

/* ERROR code and STATUS definitions */
#define ERROR_OK 1
#define ERROR_ERROR 0

#define TX_READY 0
#define TX_WAIT 1


#define INT_VECT_NUM 21         //this number is used to link SCI1Isr to the interupt vector

//unsigned char SCI1String[6]={'H','E','L','L','O','\0'};
//unsigned char *SCI1Stringp = SCI1String;
unsigned char *SCI1Stringp;
unsigned char tx_buff = 0;
unsigned char _rx_buff[2] = {0};     //do not use
unsigned char rx_buff;
unsigned char tx_status;
unsigned char _rx_status;
unsigned char rx_status;
const char START = 0xFF;
const char STOP = 0xFE;

void set_clock_24mhz();
unsigned char serial_init();
void serial_send(unsigned char SCI1Byte);

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt INT_VECT_NUM SCI1Isr() {
    //controls sending
    if (SCI1SR1 & 0x80){     /*If transmission flag is set*/
        SCI1SR1;
        if(*(SCI1Stringp++) != '\0'){
             SCI1DRL=*SCI1Stringp;
         } else {
             tx_status=TX_READY;   /*Start new transmission cycle*/
             SCI1CR2 &= 0x7F;         /*Disable TDRE interrupt*/
        }
    }  
    //controls sending
    if(SCI1SR1 & 0x20)  {       //checks that there is a start and stop bit
        SCI1SR1;        //clears flags
        SCI1DRL;
        if(SCI1DRL == 0xFF) {
            _rx_buff[0] = 0xFF;
            _rx_buff[1] = 0xFD;
        } else if(SCI1DRL == 0xFE)  {
            if(_rx_buff[1] != 0xFD)  {
                rx_buff = _rx_buff[1];
            }
            _rx_buff[0] = 0;
            _rx_buff[1] = 0xFD;
        } else if(_rx_buff[0] == 0xFF)  {
            _rx_buff[1] = SCI1DRL;
        }
        //PORTB ^= 0xff;
        //serial_send(rx_buff);
    }
}


unsigned char serial_init(){
    SCI1BDL = 156;      /*Configure baud rate at 9600 bps with*/
    SCI1BDH = 0x00;      /*an SCI1 clock modulo of 24MHz*/
    SCI1CR1 = 0x00;      /*8 data bits, no parity*/
    SCI1CR2 = 0x2C;      /*Enable Tx, Rx, and RDRF interrupts*/
    if (SCI1SR1 & 0x80){     /*Poll TDRE flag*/
        return ERROR_OK;    /*TDRE set, return OK*/
    } else {
        return ERROR_ERROR; /*TDRE clear, return ERROR*/
    }
}

//perameters = string or char array pointer to string with \0 at then end
void serial_send(unsigned char *SCI1Byte){
    SCI1DRL = *SCI1Byte;        /*Write data byte to SCI1DRL register*/
    SCI1CR2 |= 0x80;         /*Enable TDRE interrupt*/
}

char serial_recieve()   {
    return rx_buff - 100;
}

void set_clock_24mhz(){
   CLKSEL &= 0x7F;
   PLLCTL |= 0x40;
   SYNR  = 0x05;
   REFDV = 0x01;
   /* REFDV=0x00;   for 4 MHz */
   /* REFDV=0x01;   for 8 MHz  */
   /* REFDV=0x03;   for 16 MHz */
   while(!(0x08 & CRGFLG));    
   CLKSEL |= 0x80;
}

unsigned char main()    { 
    DDRS = 0x00;
    DDRJ = 0x0f;
    PTJ = 0x00;
    DDRB = 0xff;
    PORTB = 0xff;
    DDRP = 0xff;
    PTP = 0x0f;
    set_clock_24mhz();

    if (serial_init())    {   /*Configure SCI1 port*/
    } else {
        return ERROR_ERROR;
    }

    EnableInterrupts;

    tx_status = TX_READY;     /*Initialize transmission cycle flag*/
    //serial_send(h);
    for (;;){
        // if(tx_status == TX_READY){
        //     tx_status = TX_WAIT;
        //     SCI1Stringp=SCI1String;       /*Set pointer to character string*/
        //     serial_send(*SCI1Stringp);/*Send first byte of string*/
        // }
        _FEED_COP();
    }
}
