#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
//#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"
//"Defines" retirados da biblioteca "inc/tm4c123gh6pm.h"
//utilizados para declarar as variáveis de desbloqueio
//do pino PF0.
#define GPIO_PORTF_LOCK_R (*((volatile uint32_t *)0x40025520))
#define GPIO_PORTF_CR_R  (*((volatile uint32_t *)0x40025524))
int LED=4;
/***Configuração da UART0, Utils.c***/
void ConfigureUART(void) // Função retirada do exemplo hello.c
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
GPIOPinConfigure(GPIO_PA0_U0RX);
GPIOPinConfigure(GPIO_PA1_U0TX);
GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
//UARTStdioConfig(0, 115200, 16000000);
}
int main(void) {
// Habilita clock geral do sistema
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
////Configuração da GPIO F ////
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        GPIO_PORTF_LOCK_R = 0x4C4F434B;
        GPIO_PORTF_CR_R = 0x1F;
        // Desbloqueio do
        // pino PF0.
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
        GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
        ConfigureUART();
        while(1) {
        // Se SW2 for pressionado//
            if(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) & GPIO_PIN_0)) {
            LED=8;
            //UARTprintf("Verde\n");
        }
        // Se SW1 for pressionado//
        if(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) & GPIO_PIN_4)) {
        LED=2;
        //UARTprintf("Vermelho\n");
        }
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
        SysCtlDelay(2000000); LED=4; }
        }
