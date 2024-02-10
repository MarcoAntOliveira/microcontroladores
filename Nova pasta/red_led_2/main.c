#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIO_PORTA_BASE

int main(void)
{
    // Setup do microcontrolador
    uint32_t ui32SysClock;
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(LED_PORT, LED_PIN);

    while(1)
    {
        // Ativando o LED
        GPIOPinWrite(LED_PORT, LED_PIN, LED_PIN);
        SysCtlDelay(ui32SysClock / 6); // Delay

        // Desativando o LED
        GPIOPinWrite(LED_PORT, LED_PIN, 0x0);
        SysCtlDelay(ui32SysClock / 6); // Delay
    }
}
