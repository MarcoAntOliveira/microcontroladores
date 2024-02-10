#include <stdint.h> // inclusão da biblioteca de tipos inteiros
#include "inc/tm4c123gh6pm.h"
#define sseg_A   0x01 // definição de sseg_A como 0x01
#define sseg_B   0x02 // definição de sseg_B como 0x02
#define sseg_C   0x04 // definição den sseg_C como 0x04
#define sseg_D   0x08 // definição de sseg_D como 0x08
#define sseg_E   0x10 // definição de sseg_E como 0x10
#define sseg_F   0x20 // definição de sseg_F como 0x20
#define sseg_G   0x40 // definição de sseg_G como 0x40

#define GPIOPortF_base 0x40025000 // definição da base do port F como 0x40025000

void sseg_init(void) // definição da função sseg_init
{
    SYSCTL_RCGCGPIO_R |= 0x20;        // inicialização do clock do port F
    GPIO_PORTF_DIR_R |= 0xFF;          // seta todas as saídas como saídas digitais
    GPIO_PORTF_DEN_R |= 0xFF;          // habilita todas as portas digitais

    GPIO_PORTF_DATA_R &= ~(sseg_A | sseg_B | sseg_C | sseg_D | sseg_E | sseg_F | sseg_G); // seta todas as portas sseg como LOW

}

void sseg_display(uint8_t digit) // definição da função sseg_display
{
    switch (digit)
    {
        case 0:
            GPIO_PORTF_DATA_R = sseg_A | sseg_B | sseg_C | sseg_D | sseg_E | sseg_F;
            break;
        case 1:
            GPIO_PORTF_DATA_R = sseg_B | sseg_C;
            break;
        case 2:
            GPIO_PORTF_DATA_R = sseg_A | sseg_B | sseg_D | sseg_E | sseg_G;
            break;
        case 3:
            GPIO_PORTF_DATA_R = sseg_A | sseg_B | sseg_C | sseg_D | sseg_G;
            break;
        case 4:
            GPIO_PORTF_DATA_R = sseg_B | sseg_C | sseg_F | sseg_G;
            break;
        case 5:
            GPIO_PORTF_DATA_R = sseg_A | sseg_C | sseg_D | sseg_F | sseg_G;
            break;
        case 6:
            GPIO_PORTF_DATA_R = sseg_A | sseg_C | sseg_D | sseg_E | sseg_F | sseg_G;
            break;
        case 7:
            GPIO_PORTF_DATA_R = sseg_A | sseg_B | sseg_C;
            break;
        case 8:
            GPIO_PORTF_DATA_R = sseg_A | sseg_B | sseg_C | sseg_D | sseg_E | sseg_F | sseg_G;
            break;
        case 9:
            GPIO_PORTF_DATA_R = sseg_A | sseg_B | sseg_C | sseg_D | sseg_F | sseg_G;
            break;
        default:
            GPIO_PORTF_DATA_R &= ~(sseg_A | sseg_B | sseg_C | sseg_D | sseg_E | sseg_F | sseg_G);
            break;
    }
}

int main(void) // definição da função main
{
    sseg_init(); // inicialização da função sseg_init
    uint8_t num = 0; // definição da variável num como 0

    while (1) // loop infinito
    {
        sseg_display(num); // chama a função sseg_display passando num como parâmetro
        num++; // incrementa num a cada iteração

        if (num == 10) // se num for igual a 10
        {
            num = 0; // num volta a ser igual a 0
        }
        volatile int i = 0;
        for ( i = 0; i < 500000; i++); // espera um tempo para exibir cada dígito
    }

}
