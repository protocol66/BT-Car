#include <hidef.h>      /* common defines and macros */
#include "mc9s12dg256.h"
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"

/* ERROR code and STATUS definitions */
#define ERROR_OK 1
#define ERROR_ERROR 0
#define START_CYCLE 1
#define WAIT_CYCLE 0

#define INT_VECT_NUM 21         //this number is used to link SCI1Isr to the interupt vector

char global = 0;

unsigned char SCI1IniTx;
unsigned char SCI1String[6]={'H','E','L','L','O','\0'};


#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt INT_VECT_NUM SCI1Isr(void) {
    global = 1;
    if (SCI1SR1 & 0x80){     /*If transmission flag is set*/
        if(*(SCI1Stringp++) != '\0'){
            SCI1DRL=*SCI1Stringp;
        } else {
            SCI1IniTx=START_CYCLE;   /*Start new transmission cycle*/
            SCI1CR2 &= 0x7F;         /*Disable TDRE interrupt*/
        }
    }
    return;
}


unsigned char SCI1Config(void){
    SCI1BDL = 0x0D;      /*Configure baud rate at 19200 bps with*/
    SCI1BDH = 0x00;      /*an SCI1 clock modulo of 4MHz*/
    SCI1CR1 = 0x00;      /*8 data bits, no parity*/
    SCI1CR2 = 0x08;      /*Enable Tx, Rx, and RDRF interrupt*/
    if (SCI1SR1 & 0x80){     /*Poll TDRE flag*/
        return ERROR_OK;    /*TDRE set, return OK*/
    } else {
        return ERROR_ERROR; /*TDRE clear, return ERROR*/
    }
}

void SCI1Tx(unsigned char SCI1Byte){
    SCI1DRL = SCI1Byte;        /*Write data byte to SCI1DRL register*/
    SCI1CR2 |= 0x80;         /*Enable TDRE interrupt*/
}

unsigned char main(void)    {
    if (SCI1Config())    {   /*Configure SCI1 port*/
    } else {
        return ERROR_ERROR;
    }

    EnableInterrupts;

    SCI1IniTx = START_CYCLE;     /*Initialize transmission cycle flag*/
    for (;;){
        if(SCI1IniTx == START_CYCLE){
            SCI1IniTx = WAIT_CYCLE;
            SCI1Stringp=SCI1String;       /*Set pointer to character string*/
            SCI1Tx(*SCI1Stringp);/*Send first byte of string*/
        }
    }
}
