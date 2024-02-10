#include <stdint.h>

#define ESC_REG(x)                  (*((volatile uint32_t *)(x)))

#define SYSCTL_RCGC2_R              0x400FE108
#define SYSCTL_RCGC2_GPIOF          0x00000020
#define GPIO_PORTF_DIR_R            0x40025400
#define GPIO_PORTF_DEN_R            0x4002551C
#define GPIO_PORTF_DATA_R           0x400253FC
#define GPIO_OS_DR2R                0x500
#define GPIO_OS_DR4R                0x504
#define GPIO_OS_DR8R                0x508
#define Pino_3                      0x08


HAB_PORT_S(uint32_t PORT_F,uint8_t PIN_S){
    ESC_REG(SYSCTL_RCGC2_R) = PORT_F;
    ESC_REG(GPIO_PORTF_DIR_R) = PIN_S;
    ESC_REG(GPIO_PORTF_DEN_R) = PIN_S;
    ESC_REG(PORT_F + GPIO_OS_DR2R) |= PIN_S;

    }

HAB_PORT(uint8_t PORT_F){
    ESC_REG(SYSCTL_RCGC2_R) = PORT_F;
}


int main(void)
{
    volatile uint32_t ui32Loop;
    PIN_S = 0x08;
    PORT_F = SYSCTL_RCGC2_GPIOF;
    // Habilita o portal de GPIO F
    //ESC_REG(SYSCTL_RCGC2_R) = SYSCTL_RCGC2_GPIOF;

    // Faz leitura dummy para efeito de atraso
    ui32Loop = ESC_REG(SYSCTL_RCGC2_R);

    // Habilita o pino 3 do portal F, configura como sa�da digital
    /*
    ESC_REG(GPIO_PORTF_DIR_R) = PORT_S;
    ESC_REG(GPIO_PORTF_DEN_R) = PORT_S;
    */
     HAB_PORT_S(PORT_F, PIN_S)
    // Loop principal
    while(1)
    {
        // Acende o LED
        ESC_REG(GPIO_PORTF_DATA_R)|= 0x08;

        // Atraso
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }

        // Apaga o LED
        ESC_REG(GPIO_PORTF_DATA_R) &= ~(0x08);

        // Atraso
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }
    }
}
