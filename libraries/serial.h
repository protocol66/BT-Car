#ifndef SERIAL_H
#define SERIAL_H

//#include <hidef.h>      /* common defines and macros */
//#include "mc9s12dg256.h"
//#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"

/* ERROR code and STATUS definitions */
#define START_BIT 0xFF;
#define STOP_BIT 0xFE;
#define NO_DATA_BIT 0xFD;
#define ERROR_OK 1
#define ERROR_ERROR 0
#define TX_READY 0
#define TX_WAIT 1
#define INT_VECT_NUM 21         //this number is used to link SCI1Isr to the interupt vector

unsigned char *SCI1Stringp;
unsigned char _rx_buff[2] = {0};     //do not use
unsigned char rx_buff;
unsigned char tx_status;

unsigned char serial_init();
void serial_send(unsigned char *SCI1Byte);
char serial_recieve()

//interubt that does the processing for serial RX and TX
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
    //controls recieving
    if(SCI1SR1 & 0x20)  {       //checks that there is a start and stop bit
        SCI1SR1;        //clears flags
        SCI1DRL;
        if(SCI1DRL == START_BIT) {
            _rx_buff[0] = START_BIT;
            _rx_buff[1] = NO_DATA_BIT;
        } else if(SCI1DRL == STOP_BIT)  {
            if(_rx_buff[1] != NO_DATA_BIT)  {
                rx_buff = _rx_buff[1];
            }
            _rx_buff[0] = 0;
            _rx_buff[1] = NO_DATA_BIT;
        } else if(_rx_buff[0] == START_BIT)  {
            _rx_buff[1] = SCI1DRL;
        }
    }
}

//inits SCI1 aka serial port 
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

//get what is in the reciever buffer
char serial_recieve()   {
    return rx_buff;
}


#endif
