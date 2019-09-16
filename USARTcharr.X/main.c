#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include <stdlib.h>
#include <string.h>
char led_value[2];
int status=0,i=0;
volatile uint8_t rxData=0;
int val;
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
        if(EUSART1_is_rx_ready())
            {                
                rxData = EUSART1_Read();
                if(rxData!=0x3f)
                {
                    for(i=0;i<2;i++)
                    {
                        led_value[i]=rxData;                          
                    }
                    char str[2];
                    strcpy(str, led_value);
                    val=atoi(str);
                    LATA=val;
                    LATA=~LATA;
                    __delay_ms(1);
                    status=0;
                    break;
                }
            }
    }
}
