#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

uint8_t ui8PinData=2;

int main(void)
{   // configuração clock
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    //habilitação periferico
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //habilitação f3 led
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    // habiltação f4 como input
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    //configurando resistor de pull up
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


    while(1)
        {

        ui8PinData = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
            if (ui8PinData == 0b00010000)
                {
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
                }
            else
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0xFF);
        }
}
