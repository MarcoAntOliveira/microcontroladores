#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/gpio.h"
#include"inc/hw_gpio.h"
#include "driverlib/sysctl.h"


// Definindo as constantes que representam cada pino do display de sete segmentos
#define SEGMENT_A 0x01
#define SEGMENT_B 0x02
#define SEGMENT_C 0x04
#define SEGMENT_D 0x08
#define SEGMENT_E 0x10
#define SEGMENT_F 0x20
#define SEGMENT_G 0x40

// Definindo as constantes que representam cada pino do microcontrolador
#define PIN_A GPIO_PIN_0
#define PIN_B GPIO_PIN_1
#define PIN_C GPIO_PIN_2
#define PIN_D GPIO_PIN_3
#define PIN_E GPIO_PIN_4
#define PIN_F GPIO_PIN_5
#define PIN_G GPIO_PIN_6

// Definindo os pinos GPIO utilizados para cada segmento do display
#define GPIO_A GPIO_PORTF_BASE, PIN_A
#define GPIO_B GPIO_PORTF_BASE, PIN_B
#define GPIO_C GPIO_PORTF_BASE, PIN_C
#define GPIO_D GPIO_PORTF_BASE, PIN_D
#define GPIO_E GPIO_PORTF_BASE, PIN_E
#define GPIO_F GPIO_PORTF_BASE, PIN_F
#define GPIO_G GPIO_PORTF_BASE, PIN_G

// Tabela para mapear cada número para os segmentos que devem ser ativados
const char digitMap[] = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,  // 0
    SEGMENT_B | SEGMENT_C,  // 1
    SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_E | SEGMENT_D,  // 2
    SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_C | SEGMENT_D,  // 3
    SEGMENT_F | SEGMENT_G | SEGMENT_B | SEGMENT_C,  // 4
    SEGMENT_A | SEGMENT_F | SEGMENT_G | SEGMENT_C | SEGMENT_D,  // 5
    SEGMENT_A | SEGMENT_F | SEGMENT_E | SEGMENT_D | SEGMENT_C | SEGMENT_G,  // 6
    SEGMENT_A | SEGMENT_B | SEGMENT_C,  // 7
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,  // 8
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G   // 9
};

// Função para exibir um número no display de sete segmentos
void displayDigit(uint32_t digit) {
    // Seleciona os pinos corretos para cada segmento do display
    GPIOPinWrite(GPIO_A | GPIO_B | GPIO_C | GPIO_D | GPIO_E | GPIO_F | GPIO_G, digitMap[digit]);

    // Espera 200ms antes de exibir o próximo número
    SysCtlDelay(SysCtlClockGet() / 3 / 5 * 200);
}

int main(void)
{
    // Configura os pinos escolhidos para o display como saída
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_A | GPIO_B | GPIO_C | GPIO_D | GPIO_E | GPIO_F | GPIO_G);

    uint32_t count = 0;
    while (count < 8) {
        displayDigit(count);
        count++;
    }
}

    // Loop infinito para manter o programa
