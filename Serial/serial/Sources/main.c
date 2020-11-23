#include <hidef.h>      /* common defines and macros */
#include "mc9s12dg256.h"
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"

/* ERROR code and STATUS definitions */
#define ERROR_OK 1
#define ERROR_ERROR 0

#define TX_BUF_SIZE 100
#define RX_BUF_SIZE 100
#define TX_READY 0
#define TX_WAIT 1
#define TX_BUF_OVER 2
#define RX_READY 0
#define RX_WAIT 1
#define RX_BUF_OVER 2


#define INT_VECT_NUM 21         //this number is used to link SCI1Isr to the interupt vector

//unsigned char SCI1String[6]={'H','E','L','L','O','\0'};
//unsigned char *SCI1Stringp;

unsigned char tx_status;
unsigned char rx_status;
unsigned char tx_buffer[TX_BUF_SIZE] = {0};
unsigned char rx_buffer[RX_BUF_SIZE] = {0};
unsigned long tx_counter;
unsigned long rx_counter;

void clear_tx() {
    long i;
    for (i = 0; i < TX_BUF_SIZE; i++)   {
        tx_buffer[i] = 0;
    }
    tx_counter = 0;
    tx_status = TX_READY;
}

void clear_rx() {
    long i;
    for (i = 0; i < RX_BUF_SIZE; i++)   {
        rx_buffer[i] = 0;
    }
    rx_counter = 0;
    rx_status = RX_READY;
}

void push_tx(const char data)  {
    if(tx_status == TX_WAIT || tx_status == TX_BUF_OVER)
        return;
    tx_counter++
    if(tx_counter < TX_BUF_SIZE)    {
        tx_buffer[tx_counter] = data;
    } else {
        tx_status = TX_BUF_OVER;
    }
}

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
    if(SCI1SR1 & 0x20)  {
        SCI1Stringg = {}
    }
    return;
}


unsigned char SCI1Config(void){
    SCI1BDL = 0x9C;      /*Configure baud rate at 9600 bps with*/
    SCI1BDH = 0x00;      /*an SCI1 clock modulo of 4MHz*/
    SCI1CR1 = 0x00;      /*8 data bits, no parity*/
    SCI1CR2 = 0x2C;      /*Enable Tx, Rx, and RDRF interrupts*/
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

unsigned char main(void)    {
    set_clock_24mhz();

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
