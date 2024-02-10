
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
#include "Nokia5110.h"
#include "inc/tm4c123gh6pm.h"


void UartConfig(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

int main(){
      SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
      Nokia5110_Init();
      UartConfig();
      while(1)
      {
          // variaveis para as horas, segundos, minutos
          char horas , minutos , segundos;
          //lê as horas , minutos e segundos do terminal
          horas = UARTCharGet(UART0_BASE);
          minutos = UARTCharGet(UART0_BASE);
          segundos = UARTCharGet(UART0_BASE);

          Nokia5110_Clear();

          Nokia5110_SetCursor(3,3);
          Nokia5110_OutChar(horas);
          Nokia5110_SetCursor(3, 4);
          Nokia5110_OutChar(':');
          Nokia5110_SetCursor(3, 5);
          Nokia5110_OutChar(minutos);
          Nokia5110_SetCursor(3,6);
          Nokia5110_OutChar(':');
          Nokia5110_SetCursor(3,7);
          Nokia5110_OutChar(segundos);
      }



}
