
#include "bot.h"
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#define WRITE_REG(x)                      (*((volatile uint32_t *)(x)))

void ConfigureButtons(){

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    int i;

    for(i = 0; i < 10; i++);

    WRITE_REG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    WRITE_REG(GPIO_PORTF_BASE+GPIO_O_CR) = 0x01;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5);


}

int GetButton(){

    int i, aux;

    for(i = 0; i < 4; i++){

        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5 , 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);

        switch(i){

            case 0:

                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4 , 0xff);

                aux = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

                if(aux & GPIO_PIN_0) return 0;
                else if(aux & GPIO_PIN_1) return 1;
                else if(aux & GPIO_PIN_2) return 2;
                else if(aux & GPIO_PIN_3) return 3;

                break;

            case 1:

                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 , 0xff);

                aux = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

                if(aux & GPIO_PIN_0) return 4;
                else if(aux & GPIO_PIN_1) return 5;
                else if(aux & GPIO_PIN_2) return 6;
                else if(aux & GPIO_PIN_3) return 7;

                break;

            case 2:

                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1 , 0xff);

                aux = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

                if(aux & GPIO_PIN_0) return 8;
                else if(aux & GPIO_PIN_1) return 9;
                else if(aux & GPIO_PIN_2) return 10;
                else if(aux & GPIO_PIN_3) return 11;

                break;
            case 3:

                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5 , 0xff);

                aux = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

                if(aux & GPIO_PIN_0) return 12;
                else if(aux & GPIO_PIN_1) return 13;
                else if(aux & GPIO_PIN_2) return 14;
                else if(aux & GPIO_PIN_3) return 15;

                break;
        }
    }

    return BUTTON_NOT_PRESSED;
}





