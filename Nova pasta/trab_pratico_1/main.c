
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

#include <inc/tm4c123gh6pm.h> //header para a placa TM4C123GH6PM
#include <driverlib/sysctl.h> //header da TivaWare Peripheral Driver Library

// Define os pinos dos segmentos do display de 7 segmentos
#define SEG_A GPIO_PIN_0
#define SEG_B GPIO_PIN_1
#define SEG_C GPIO_PIN_2
#define SEG_D GPIO_PIN_3
#define SEG_E GPIO_PIN_4
#define SEG_F GPIO_PIN_5
#define SEG_G GPIO_PIN_6

// Array para armazenar os segmentos utilizados no padrão quadrado
const uint8_t PADRAO_QUADRADO1[] = {SEG_A, SEG_B, SEG_F, SEG_G};
const uint8_t PADRAO_QUADRADO2[] = {SEG_C, SEG_D, SEG_E, SEG_G};

int main(void) {
    volatile uint32_t ui32Loop;

    // Habilita a porta E
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)) {}

    // Configura os pinos como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G);

    // Loop infinito
    while(1) {
        // Exibe o padrão quadrado com os segmentos definidos em PADRAO_QUADRADO1
        GPIOPinWrite(GPIO_PORTE_BASE, SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G, 0x00);
        uint32_t i , j = 0;
        for (i = 0; i < sizeof(PADRAO_QUADRADO1)/sizeof(PADRAO_QUADRADO1[0]); i++) {
            GPIOPinWrite(GPIO_PORTE_BASE, PADRAO_QUADRADO1[i], PADRAO_QUADRADO1[i]);
        }
        // Delay para exibir o padrão
        SysCtlDelay(2000000);

        // Desliga os segmentos utilizados no padrão anterior
        GPIOPinWrite(GPIO_PORTE_BASE, SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G, 0x00);

        // Exibe o padrão quadrado com os segmentos definidos em PADRAO_QUADRADO2
        for ( j = 0; j < sizeof(PADRAO_QUADRADO2)/sizeof(PADRAO_QUADRADO2[0]); j++) {
            GPIOPinWrite(GPIO_PORTE_BASE, PADRAO_QUADRADO2[j], PADRAO_QUADRADO2[j]);
        }
        // Delay para exibir o padrão
        SysCtlDelay(2000000);

        // Desliga os segmentos utilizados no padrão anterior
        GPIOPinWrite(GPIO_PORTE_BASE, SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G, 0x00);
    }
}
