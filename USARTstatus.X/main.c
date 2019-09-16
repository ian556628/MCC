#include "mcc_generated_files/mcc.h"
#include <xc.h>
int status=0;
volatile uint8_t led_value=0x00;
volatile uint8_t rxData=0;
volatile uint8_t seg_value1=0x00;
volatile uint8_t seg_value2=0x00;
volatile uint8_t seg[2];
unsigned char segg11=0x00;
unsigned char segg122=0x00;
unsigned char segg12=0x00;
unsigned char segg21=0x00;
unsigned char segg222=0x00;
unsigned char segg22=0x00;
int c=0,cc=0;
volatile uint8_t c_scan;
unsigned char Seg[16]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};

void state(void)
{    
    switch(status)
    {
        case 1://led
            __delay_ms(20);
            if(EUSART1_is_rx_ready())
            {                
                rxData = EUSART1_Read();
                if(rxData!=0x3f)
                {
                    led_value=rxData;            
                    LATA=led_value; 
                    LATA=~LATA;
                    __delay_ms(1);
                    status=0;
                    break;
                }
            }
            else
                status=1;
                break;
        case 2://seg
            __delay_ms(15);
            if(EUSART1_is_rx_ready())
            {                
                rxData = EUSART1_Read();
                if(rxData!=0x3a)
                {
                    if(c==1)
                    {
                        seg_value2=rxData;
                        __delay_ms(1);
                        c=0;
                        status=0;
                        break;
                    }
                    if(c==0)
                    {
                        seg_value1=rxData;
                        __delay_ms(1);
                        c++;
                        status=0;
                        break;
                    }
                }
            } 
            
        /*case 3:
            if(EUSART1_is_rx_ready())
            {
                rxData = EUSART1_Read();
                if(rxData!=0x3a)
                {
                    seg_value2=rxData;                   
                    status=4;
                    __delay_ms(1);
                    //break;
                }
            }*/            
    }
}

void seg_calculate(void)
{
    segg12=seg_value1<<4;
    segg122=segg12>>4;
    segg11=(seg_value1|0x0F)>>4;
    segg22=seg_value2<<4;
    segg222=segg22>>4;
    segg21=(seg_value2|0x0F)>>4;
}

void show_seg(void)
{ 
    if (c_scan==0)  
    {
        LATD=0xff;
        LATC=0x00;
        LATC=0x08; 
        LATD=Seg[segg11];
        __delay_ms(2);
        c_scan++;
    }   
    if (c_scan==1)  
    {
        LATD=0xff;
        LATC=0x00;
        LATC=0x04;
        LATD=Seg[segg122];
        __delay_ms(2);
        c_scan++;
    }   
    if (c_scan==2)  
    {
        LATD=0xff;
        LATC=0x00;
        LATC=0x02;
        LATD=Seg[segg21];
        __delay_ms(2);
        c_scan++;
    }   
    if (c_scan==3)  
    {
        LATD=0xff;
        LATC=0x00;
        LATC=0x01;
        LATD=Seg[segg222];
        __delay_ms(2);
        c_scan=0;
    }   
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    
    while (1)
    {  
        state();
        seg_calculate();
        show_seg();
        if(EUSART1_is_rx_ready())
        {
            rxData = EUSART1_Read();
            if(rxData==0x3F)//?
            {
                EUSART1_Write(0x4C);
                status=1;
            }
            if(rxData==0x3A)//:
            {
                EUSART1_Write(0x53);               
                status=2;                                              
            }    
        }      
    }
}
