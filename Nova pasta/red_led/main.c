#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

void delay(int time) {
    int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 3180; j++);
}

int main(void) {
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; // habilita o clock para o Port F
    GPIO_PORTF_DIR_R |= 0x02; // configura o PF1 como saída
    GPIO_PORTF_DEN_R |= 0x02; // habilita a função digital do PF1

    while(1) {
        GPIO_PORTF_DATA_R |= 0x02; // liga o LED vermelho
        delay(1000000); // espera por 1 segundo
        GPIO_PORTF_DATA_R &= ~0x02; // desliga o LED vermelho
        delay(1000000); // espera por 1 segundo
    }
}
