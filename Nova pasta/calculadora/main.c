#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "  driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "inc/hw_gpio.h"

#define SEGMENT_A GPIO_PIN_0
#define SEGMENT_B GPIO_PIN_1
#define SEGMENT_C GPIO_PIN_2
#define SEGMENT_D GPIO_PIN_3
#define SEGMENT_E GPIO_PIN_4
#define SEGMENT_F GPIO_PIN_5
#define SEGMENT_G GPIO_PIN_6
#define SEGMENT_DP GPIO_PIN_7

void setDisplayValue(uint8_t ui8Value)
{
    switch (ui8Value)
    {
    case 0:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F, 0x3F);
        break;
    case 1:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_B|SEGMENT_C, 0x06);
        break;
    case 2:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_A|SEGMENT_B|SEGMENT_D|SEGMENT_E|SEGMENT_G, 0x5B);
        break;
    case 3:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_G, 0x4F);
        break;
    case 4:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_B|SEGMENT_C|SEGMENT_F|SEGMENT_G, 0x66);
        break;
    case 5:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_A|SEGMENT_C|SEGMENT_D|SEGMENT_F|SEGMENT_G, 0x6D);
        break;
    case 6:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_A|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F|SEGMENT_G, 0x7D);
        break;
    case 7:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_A|SEGMENT_B|SEGMENT_C, 0x07);
        break;
    case 8:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F|SEGMENT_G, 0x7F);
        break;
    case 9:
        GPIOPinWrite(GPIO_PORTB_BASE, SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_F|SEGMENT_G, 0x6F);
        break;
    default:
        break;
    }
}

void initDisplay()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, SEGMENT_A|SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F|SEGMENT_G|SEGMENT_DP);
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); //set oscillator to 16MHz
    initDisplay(); //initialize display
    setDisplayValue(5); //show number 5 on the display
    while(1)
    {
    }
}
