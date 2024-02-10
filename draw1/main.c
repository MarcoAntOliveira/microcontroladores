
#include <stdint.h>
#include<stdbool.h>
#include <stdio.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "Nokia5110.h"
#include "inc/tm4c123gh6pm.h"


void  delay(uint32_t delayms){
    SysCtlDelay(delayms);

}

void delayMicroseconds(uint32_t us) {
    SysCtlDelay((SysCtlClockGet() / 3 / 1000000) * us);
}

// Função de atraso em milissegundos
void delayMilliseconds(uint32_t ms) {
    SysCtlDelay((SysCtlClockGet() / 3 / 1000) * ms);
}

void circ(){

}
    int main (void)
    {
        SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

        /*uint16_t segundos = 0, dminutos = 5, uminutos = 8, dhoras = 0, uhoras = 0;
        Nokia5110_Init();
            while (1) {
                     segundos++;
                     delayMilliseconds(500);
                if (segundos > 59) {
                    delayMilliseconds(5000);
                    uminutos++;
                    if(uminutos>9){
                        dminutos++;
                        uminutos = 0;
                    }
                    segundos = 0;
                }
                if (dminutos > 5 && uminutos >9 && segundos>5 ) {
                    delayMilliseconds(500);
                    //delay(500);
                    uhoras++;
                    if(uhoras > 9){
                        dhoras++;
                        uhoras = 0;
                    }
                    uminutos = 0;
                    dminutos = 0;

                }
                if (dhoras > 2 && uhoras>3){
                    delayMilliseconds(5000);
                    //delay(5000);
                    dhoras = 0;
                    uhoras = 0;
                }
                Nokia5110_Clear();
                Nokia5110_SetCursor(2, 2);
                Nokia5110_OutDec(dhoras);

                Nokia5110_SetCursor(3, 2);
                Nokia5110_OutDec(uhoras);

                Nokia5110_SetCursor(4, 2);
                Nokia5110_OutChar(':');

                Nokia5110_SetCursor(5, 2);
                Nokia5110_OutDec(dminutos);

                Nokia5110_SetCursor(6, 2);
                Nokia5110_OutDec(uminutos);

                Nokia5110_SetCursor(7, 2);
                Nokia5110_OutChar(':');

                Nokia5110_SetCursor(8, 2);
                Nokia5110_OutDec(segundos);
            }
            */

        Nokia5110_Init();
        Nokia5110_Clear();
        Nokia5110_SetCursor(2, 2);
        Nokia5110_OutDec(dhoras);

        Nokia5110_SetCursor(3, 2);
        Nokia5110_OutDec(uhoras);

        Nokia5110_SetCursor(4, 2);
        Nokia5110_OutChar(':');

        Nokia5110_SetCursor(5, 2);
        Nokia5110_OutDec(dminutos);

        Nokia5110_SetCursor(6, 2);
        Nokia5110_OutDec(uminutos);

        Nokia5110_SetCursor(7, 2);
        Nokia5110_OutChar(':');

        Nokia5110_SetCursor(8, 2);
        Nokia5110_OutDec(segundos);

    }
