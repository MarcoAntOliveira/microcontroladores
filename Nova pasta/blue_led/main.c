#include <stdint.h>
#include "inc/tm4c123gh6pm.h"


void delay(int time) {
    int i;
    for(i = 0; i < time; i++){}
}


int main(void) {
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; // Habilita o clock para o Port F
    GPIO_PORTF_DIR_R |= 0x04; // Configura o PF2 como saída
    GPIO_PORTF_DIR_R |= 0
    GPIO_PORTF_DEN_R |= 0x04; // Habilita a função digital do PF2


    while(1) {
        GPIO_PORTF_DATA_R |= 0x04; // Liga o LED azul
        delay(1000000); // Espera por 1 segundo
        GPIO_PORTF_DATA_R &= ~0x04; // Desliga o LED azul
        delay(1000000); // Espera por 1 segundo
    }
}
