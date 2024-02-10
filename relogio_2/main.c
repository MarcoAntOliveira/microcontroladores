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


#include <string.h>

#include <driverlib/pin_map.h>


#define UART_MODULE     UART0_BASE
#define BAUD_RATE       115200

void UARTSetup(void) {
  // Habilita a UART0 e o GPIOA no clock do sistema
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  // Configura os pinos PA0 (U0RX) e PA1 (U0TX) como função UART
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  // Configura a UART com uma determinada taxa de baud rate
  UARTConfigSetExpClk(UART_MODULE, SysCtlClockGet(), BAUD_RATE,
                      (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                       UART_CONFIG_PAR_NONE));
}



// Função de atraso em milissegundos
void delayMilliseconds(uint32_t ms) {
    SysCtlDelay((SysCtlClockGet() / 3 / 1000) * ms);
}

int main(void) {
  Nokia5110_Init();
  char commandBuffer[10];  // Buffer para armazenar o comando recebido
  char receivedChar;
  uint8_t horas, minutos, segundos;

  // Configuração do sistema
  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                 SYSCTL_XTAL_16MHZ);
  UARTStdioConfig(0, BAUD_RATE, SysCtlClockGet());
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  // Configura a UART
  UARTSetup();

  while (1) {
    // Verifica se há caracteres recebidos na UART
    while (UARTCharsAvail(UART_MODULE)) {
      // Lê o caractere recebido
      receivedChar = UARTCharGetNonBlocking(UART_MODULE);

      // Verifica se o caractere recebido é um final de linha
      if (receivedChar == '\n') {
        // Processa o comando recebido
        sscanf(commandBuffer, "%2hhu:%2hhu:%2hhu", &horas, &minutos, &segundos);

        // Aqui você pode atualizar os valores de hora, minuto e segundo com as variáveis
        // 'hour', 'minute' e 'second' que foram extraídas do comando.

        // Limpa o buffer do comando
        memset(commandBuffer, 0, sizeof(commandBuffer));
      } else {
        // Armazena o caractere recebido no buffer do comando
        strncat(commandBuffer, &receivedChar, 1);
      }

      // Após atualizar os valores de hora, minuto e segundo
      UARTprintf("%02d:%02d:%02d\n", horas, minutos, segundos);

     Nokia5110_Clear();
     Nokia5110_SetCursor(2, 2);
     Nokia5110_OutDec(horas);
/*
     Nokia5110_SetCursor(3, 2);
     Nokia5110_OutDec(uhoras);
*/
     Nokia5110_SetCursor(3, 2);
     Nokia5110_OutChar(':');

     Nokia5110_SetCursor(4, 2);
     Nokia5110_OutDec(minutos);
/*
     Nokia5110_SetCursor(6, 2);
     Nokia5110_OutDec(uminutos);
*/
     Nokia5110_SetCursor(5, 2);
     Nokia5110_OutChar(':');

     Nokia5110_SetCursor(6, 2);
     Nokia5110_OutDec(segundos);



    }
  }
}




/*
// Função de atraso em milissegundos
void delayMilliseconds(uint32_t ms) {
    SysCtlDelay((SysCtlClockGet() / 3 / 1000) * ms);
}
    int main (void)
    {
        SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
        uint16_t segundos = 0, dminutos = 5, uminutos = 8, dhoras = 0, uhoras = 0;
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


    }
*/
