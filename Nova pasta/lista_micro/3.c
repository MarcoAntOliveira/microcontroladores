/*
Para realizar a multiplexação dos dígitos, é necessário modificar a função display_number() para que ela receba um vetor com os números que serão exibidos em cada um dos quatro dígitos do display. Em seguida, a função deve ser modificada para exibir cada um dos dígitos em sequência, com um pequeno atraso entre cada exibição.
*/
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

// Define o número de dígitos no display
#define DIGIT_COUNT 4

// Define os pinos para cada dígito do display
#define DIGIT_0_PIN GPIO_PIN_0
#define DIGIT_1_PIN GPIO_PIN_1
#define DIGIT_2_PIN GPIO_PIN_2
#define DIGIT_3_PIN GPIO_PIN_3

// Define os pinos para cada segmento do display
#define SEGMENT_A_PIN GPIO_PIN_4
#define SEGMENT_B_PIN GPIO_PIN_5
#define SEGMENT_C_PIN GPIO_PIN_6
#define SEGMENT_D_PIN GPIO_PIN_7
#define SEGMENT_E_PIN GPIO_PIN_0
#define SEGMENT_F_PIN GPIO_PIN_1
#define SEGMENT_G_PIN GPIO_PIN_2

// Define o mapa de conversão para cada número
uint8_t digits[10] = {
    // ABCDEFG
    0b11111100,  // 0
    0b01100000,  // 1
    0b11011010,  // 2
    0b11110010,  // 3
    0b01100110,  // 4
    0b10110110,  // 5
    0b10111110,  // 6
    0b11100000,  // 7
    0b11111110,  // 8
    0b11110110   // 9
};

// Variável para armazenar o número atual\nuint32_t current_number = 0;

// Função para exibir os números do vetor no display
void display_number(uint8_t *digits) {
    uint8_t i, j;
    uint32_t value;

    // Loop através de cada dígito do display
    for (i = 0; i < DIGIT_COUNT; i++) {
        // Determine qual pino ativar baseado no dígito atual
        switch (i) 
        {
            case 0:
                value = DIGIT_0_PIN;
                break;
            case 1:
                value = DIGIT_1_PIN;
                break;
            case 2:
                value = DIGIT_2_PIN;
                break;
            case 3:
                value = DIGIT_3_PIN;
                break;
            default:
                value = 0;
                break;
        }

        // Configure o pino do dígito atual
        GPIOPinWrite(GPIO_PORTF_BASE, DIGIT_0_PIN | DIGIT_1_PIN | DIGIT_2_PIN | DIGIT_3_PIN, value);

        // Configure os pinos dos segmentos baseado no número atual
        GPIOPinWrite(GPIO_PORTC_BASE, SEGMENT_A_PIN | SEGMENT_B_PIN | SEGMENT_C_PIN | SEGMENT_D_PIN | SEGMENT_E_PIN | SEGMENT_F_PIN | SEGMENT_G_PIN, digits[i]);

        // Atraso para permitir a exibição do número
        SysCtlDelay(SysCtlClockGet() / 3000);
    }
}

int main() {
    // Configura a frequência do sistema para 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // Configura os pinos dos dígitos como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, DIGIT_0_PIN | DIGIT_1_PIN | DIGIT_2_PIN | DIGIT_3_PIN);

    // Configura os pinos dos segmentos como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, SEGMENT_A_PIN | SEGMENT_B_PIN | SEGMENT_C_PIN | SEGMENT_D_PIN | SEGMENT_E_PIN | SEGMENT_F_PIN | SEGMENT_G_PIN);

    // Configura o temporizador para gerar interrupções de 1 segundo
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);

    // Habilita interrupções
    IntMasterEnable();

    // Loop infinito
    while(1);
}

// Manipulador de interrupção do temporizador
void Timer0IntHandler() {
    // Limpa a interrupção
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Incrementa o número atual
    current_number++;

    // Se o número atual é maior que 9, comece de 0 novamente
    if (current_number > 9) {
        current_number = 0;
    }

    // Obtem os dígitos para o número atual
    uint8_t digit_buffer[DIGIT_COUNT];
    uint32_t i, j;
    for (i = 0; i < DIGIT_COUNT; i++) {
        // O i-ésimo dígito deve exibir o número atual módulo 10 elevado à i
        digit_buffer[i] = digits[(current_number / (uint32_t)pow(10, i)) % 10];
    }

    // Exibe os números no display com um pequeno atraso entre cada dígito
    for (i = 0; i < 100; i++) {
        for (j = 0; j < DIGIT_COUNT; j++) {
            uint8_t current_digit[DIGIT_COUNT] = {0};
            current_digit[j] = digit_buffer[j];
            display_number(current_digit);
        }
    }
}
