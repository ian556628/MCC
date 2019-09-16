#include "mcc_generated_files/mcc.h"
uint8_t c_scan=0;
int i=0,k=0;
unsigned char Seg7[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

char digit[4]={0,0,0,0};
char seg_display[4]={0,0,0,0};

char show[4]={0x08,0x04,0x02,0x01};

volatile uint8_t scan_cnt=0;


void display_7seg1(uint8_t c_scan)
{ 
    if (c_scan==0)  
    {
        LATB=0xff;
        LATC=0x00;
        LATC=show[0]; 
        LATB=Seg7[digit[0]];
        __delay_ms(2);
        c_scan++;
    }   
    if (c_scan==1)  
    {
        LATB=0xff;
        LATC=0x00;
        LATC=show[1];
        LATB=Seg7[digit[1]];
        __delay_ms(2);
        c_scan++;
    }   
    if (c_scan==2)  
    {
        LATB=0xff;
        LATC=0x00;
        LATC=show[2];
        LATB=Seg7[digit[2]];
        __delay_ms(2);
        c_scan++;
    }   
    if (c_scan==3)  
    {
        LATB=0xff;
        LATC=0x00;
        LATC=show[3];
        LATB=Seg7[digit[3]];
        __delay_ms(2);
        c_scan=0;
    }   
}
void calculate_output(void)
{ 
    digit[3] =  k % 10;              
    digit[2] = (k/10) % 10;            
    digit[1] = (k/100) % 10; 
    digit[0] = (k/1000);
       
    for (i=0;i<=50;i++)
    {
        display_7seg1(c_scan);
    }
        
    k++;
    if(k>9999)
    {
        k=0; 
    }
}
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    while(1)
    {
         calculate_output();
    }        
}





