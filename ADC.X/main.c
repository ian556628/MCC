#include "mcc_generated_files/mcc.h"
#include <math.h>


/*
                         Main application
 */

int i,j,d,x,y,z;
uint16_t convertedValue = 0;
unsigned char a[4]={0x08,0x04,0x02,0x01};
unsigned char b[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char c[4]={0,1,2,3};
volatile uint8_t cnt=0;
void transTWOtoTEN(int n);


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
   
    while(1)
    {   
        if(cnt>2)
        {
        cnt=0;    
        ADC_StartConversion(channel_AN0);
        while(!ADC_IsConversionDone());
        {
            convertedValue = ADC_GetConversionResult();
        }
        d=convertedValue;
        c[0]=d/1000;//千
        c[1]=(d-c[0]*1000)/100;//百位數
        c[2]=(d-c[0]*1000-c[1]*100)/10;//十位數
        c[3]=d %10;//個位數
        //輸出 c 陣列
        for (i=0;i<=60;i++)
        {
            for (j=0;j<=3;j++)
            {
                LATB=a[j];//位址
                while(cnt<2)
                {
                    LATC=b[c[j]];               
                }
                cnt=1;
             
            }
        }
    }   
}
}
void transTWOtoTEN(int n)
{
    int x = 0 , y = 1;
    n = convertedValue; 
    while (n>0)
    {
    x += (n%10)*y;    
    y = y*2;
    n /= 10;    
    }
    d = x;
}