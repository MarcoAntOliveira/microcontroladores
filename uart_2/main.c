#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

void UART_Init(void)
{
    // Habilita o clock para o módulo UART1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configura os pinos PB0 e PB1 como pinos de função UART
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configura a taxa de transmissão (115200 bps) e os parâmetros de comunicação
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

    // Habilita o módulo UART1
    UARTEnable(UART1_BASE);
}
void UART_SendString(const char *str)
{
    while (*str)
    {
        UARTCharPut(UART1_BASE, *str);
        str++;
    }
}
void UART_ReceiveString(char *buffer, uint32_t bufferSize)
{
    uint32_t i;

    for (i = 0; i < bufferSize - 1; i++)
    {
        buffer[i] = UARTCharGet(UART1_BASE);
        if (buffer[i] == '\r' || buffer[i] == '\n')
            break;
    }

    buffer[i] = '\0';
}

