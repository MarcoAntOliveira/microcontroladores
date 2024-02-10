#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "Adafruit_PCD8544.h"




uint8_t ui8PinData = 2;

void SysTickHandler (void)
{

    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0))
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);

    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 8);
    }
}

void PortFHandler (void)
{
    uint32_t flag = GPIOIntStatus(GPIO_PORTF_BASE,true);
    if ( (flag & GPIO_INT_PIN_4) == GPIO_INT_PIN_4)
    {
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
                {
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
                }
                else
                {
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0xFF);
                }
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
    }
}

int main(void)
{
    SysCtlClockSet( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
                    | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
                          GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    //config da interrupt
    GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTF_BASE,GPIO_INT_PIN_4);
    IntEnable(INT_GPIOF);
    IntMasterEnable();

    SysTickPeriodSet(0x00FFFF);
    SysTickIntEnable();
    SysTickEnable();

    while (1)
    {
        SysCtlDelay(10000000);
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
        }
    }
}
