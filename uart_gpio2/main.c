

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
//"Defines" retirados da biblioteca "inc/tm4c123gh6pm.h"
//utilizados para declarar as variaveis de desbloqueio
//do pino PF4.
#define GPIO_PORTF_LOCK_R (*((volatile uint32_t *)0x40025520))
#define GPIO_PORTF_CR_R (*((volatile uint32_t *)0x40025524))
uint8_t LED=4;

/***Interrupção por borda de descida no PortF Pin4 (SW1)***/
void PortFIntHandler(void) {
GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
LED=2;
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
UARTprintf("Red\n");
SysCtlDelay(20000000);
}
/***Configuração da UART0, Utils.c***/
void ConfigureUART(void) // Função retirada do exemplo hello.c
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
GPIOPinConfigure(GPIO_PA0_U0RX);
GPIOPinConfigure(GPIO_PA1_U0TX);
GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
UARTStdioConfig(0, 115200, 16000000);
}
int main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    // Habilita clock geral do sistema
    ////Configuração da GPIO F ////
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;
    // Desbloqueio do GPIO_PORTF_CR_R = 0x1F; //pino PF0.
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    ////Configurando uma interrupção no PortD: Pin4 (SW1)////
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
    IntEnable(INT_GPIOF);
    ConfigureUART();
    while(1)
    {
        // Se SW2 for pressionado//
            if(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) & GPIO_PIN_0)) {
            LED=8;
            //UARTprintf("Verde\n");
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
            SysCtlDelay(20000000);
            }
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
        SysCtlDelay(200);
        LED=4;
    }
}
