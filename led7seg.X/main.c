#include "mcc_generated_files/mcc.h"
#include <xc.h>
volatile uint8_t timer0ReloadVal;
unsigned int a=0xFF;
int c_250=0,c_125=0,c_4=0,e=0;
volatile uint8_t timer0ReloadVal;
int c_scan=0;
int s=0,j=0;
unsigned char Seg[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
int digit[4];
int cc=0;

void delay(int a)
{
    int g = 0, h = 0;
    for(g = 0; g < a; g++) {
        for(h = 0; h <125; h++){
            __nop();
        }
    }
}
void flash(void)
{       
    if(e==1)
    {
        a=a<<1;
        LATA=0x00|0xFF<<e;
    }
    else
    {
        a=(a<<1)|0x01;
        LATA=(0x00|0xFF<<e)|a;
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
        //if(c_4==2)//scan
        //{
            //if(cc==5)
            //{
               // cc=1;
           // }
          //  LATC=0x01<<cc;
           // cc++;
            //c_4=0;
       // }
        /*
         if(c_4==2)//7seg
        {
            if(s>10000)
            {
                s=0;
            }
            
                digit[0] = s % 10;              
                digit[1] = (s/10) % 10;            
                digit[2] = (s/100) % 10; 
                digit[3] = (s/1000); 
                
                if(s<10)
                {
                    if(c_scan==1)
                    {
                        c_scan=0;
                    }
                        LATC=0x01<<c_scan;
                        LATB=Seg[digit[c_scan]];
                        c_scan++;                          
                }
                if(10<s && s<100)
                {                    
                        if(c_scan==2)
                        {
                            c_scan=0;
                        }
                        LATC=0x01<<c_scan;
                        LATB=Seg[digit[c_scan]];
                        c_scan++;                        
                }
                if(100<s && s<1000)
                {                    
                        if(c_scan==3)
                        {
                            c_scan=0;
                        }
                        LATC=0x01<<c_scan;
                        LATB=Seg[digit[c_scan]];
                        c_scan++;                                               
                }
                if(1000<s && s<10000)
                {                    
                        if(c_scan==4)
                        {
                            c_scan=0;
                        }
                        LATC=0x01<<c_scan;
                        LATB=Seg[digit[c_scan]];
                        c_scan++;                                               
                }
                s++;
                c_4=0;
        }
         */
        
        if(c_250==250)//led 
        {
            if(e==9)
            {
                e=1;
            }
            flash();
            e=e+1;            
            c_250=0;
        }
        
        
    }
}
/*
                         Main application
 */
