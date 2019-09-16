#include "mcc_generated_files/mcc.h"
#include <xc.h>

unsigned char Seg[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
int c_4;
int digit[4];

uint16_t convertedValue=0;

unsigned char a[4]={0x08,0x04,0x02,0x01};
unsigned char c[4]={0,1,2,3};
int i,j,d,x,y,z;
volatile uint8_t timer0ReloadVal;

int c_scan;



void TMR0_ISR(void)
{

    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    // reload TMR0
    TMR0L = timer0ReloadVal;

    if(TMR0_InterruptHandler)
    {
        TMR0_InterruptHandler();
    }

    c_4++;
}
/*
void scan(void)
{
    if(c_scan>3)
    {
        c_scan=0;
    }
    LATC=0x01<<c_scan;
    c_scan++;         
}
*/

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
        
        if(c_4>2)
        {
            c_4=0;
            //scan();
            ADC_StartConversion(channel_AN0);
            while(!ADC_IsConversionDone());
            {
                convertedValue=ADC_GetConversionResult();
            }
            
            digit[3] = convertedValue % 10;              
            digit[2] = (convertedValue/10) % 10;            
            digit[1] = (convertedValue/100) % 10; 
            digit[0] = (convertedValue/1000); 
            
            
            if(c_scan==4)
            {
                c_scan=0;
            }
            if(c_scan==0)
            {
                LATB=Seg[digit[c_scan]];
                LATC=0x01<<c_scan;;
                     }
                     
            
            if(c_scan==1)
            {
                LATB=Seg[digit[c_scan]];
                LATC=0x01<<c_scan;;
            }
            if(c_scan==2)
            {
                LATB=Seg[digit[c_scan]];
                LATC=0x01<<c_scan;;
            }
            if(c_scan==3)
            {
                LATB=Seg[digit[c_scan]];
                LATC=0x01<<c_scan;;
            }
            
            
            c_scan++;
            
        }
    }
}
