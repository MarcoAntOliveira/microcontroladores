#include <stdint.h>
#include <stdio.h>

#define ESC_REG(x)                  (*((volatile uint32_t *)(x)))

#define SYSCTL_RCGC2_R              0x400FE108
#define GPIO_BASE         0x400FE000
#define GPIO_OFFSET       0x608

#define PORTAL_A          0x00000001 // 0000 0001 em binario
#define PORTAL_B          0x00000002 // 0000 0010 em binario
#define PORTAL_C          0x00000004 // 0000 0100 em binario
#define PORTAL_D          0x00000008 // 0000 1000 em binario
#define PORTAL_E          0x00000010 // 0001 0000 em binario
#define PORTAL_F          0x00000020 // 0010 0000 em binario

#define PORTAL_A_BASE 0x40004000
#define PORTAL_B_BASE 0x40005000
#define PORTAL_C_BASE 0x40006000
#define PORTAL_D_BASE 0x40007000
#define PORTAL_E_BASE 0x40024000
#define PORTAL_F_BASE 0x40025000

#define PINO_0            0x01
#define PINO_1            0x02
#define PINO_2            0x04
#define PINO_3            0x08
#define PINO_4            0x10
#define PINO_5            0x20
#define PINO_6            0x40
#define PINO_7            0x80
#define GPIO_O_GPIODIR    0x400
#define GPIO_O_GPIODEN    0x51C // digital ou outra funcao
#define GPIO_O_GPIODR2R   0x500
#define GPIO_O_GPIODR4R   0x504
#define GPIO_O_GPIODR8R   0x508
#define GPIO_O_GPIOSLR    0x500
#define GPIO_O_GPIOPUR    0x510
#define GPIO_O_DATA_R     0x000
#define GPIO_O_GPIOLOCK   0x520
#define GPIO_O_GPIOCR     0x524


#define DELAY_BASE 1000000  // 1000000 = 2.5 segundos, aproximadamente
#define DELAY DELAY_BASE/(60*2.5) // piscar 60 vezes por segundo
#define DELAY2 100000

void habilita_portal2(uint32_t portal) {
    ESC_REG(GPIO_BASE + GPIO_OFFSET)  |= portal;
}

void habilita_portal(uint32_t portal){
    ESC_REG(SYSCTL_RCGC2_R) |= portal;
}

void desabilita_portal(uint32_t portal){
    ESC_REG(SYSCTL_RCGC2_R) &= ~(portal);
}

void configura_pino_saida(uint32_t portal_base, uint8_t pino){
    ESC_REG(portal_base + GPIO_O_GPIODIR)  |= pino;
    ESC_REG(portal_base + GPIO_O_GPIODEN)  |= pino;
    ESC_REG(portal_base + GPIO_O_GPIODR2R) |= pino;
    ESC_REG(portal_base + GPIO_O_GPIODR4R) &= ~(pino);
    ESC_REG(portal_base + GPIO_O_GPIODR8R) &= ~(pino);
    ESC_REG(portal_base + GPIO_O_GPIOSLR) &= ~(pino);
}

void escrita_pinos(uint32_t portal_base, uint8_t pino, uint8_t valor) {
    ESC_REG (portal_base + (GPIO_O_DATA_R + (pino << 2))) = valor;
}

// Limpa o display inteiro, desligando todos os digitos
void limpa_display(){
    escrita_pinos(PORTAL_C_BASE, PINO_6 | PINO_5 | PINO_4, 0x00);
    escrita_pinos(PORTAL_E_BASE, PINO_3 | PINO_2 | PINO_1 | PINO_0, 0x00);

    escrita_pinos(PORTAL_B_BASE, PINO_6 , 0x00);
    escrita_pinos(PORTAL_B_BASE, PINO_7,  0x00);
    escrita_pinos(PORTAL_D_BASE, PINO_2 , 0x00);
    escrita_pinos(PORTAL_D_BASE, PINO_3,  0x00);
}

// Da um delay no sistema, sem uma unidade definida(segundo, millisegundo, etc),
// onde o valor foi definido na pratica
void delay(uint32_t i){
    uint32_t cont;
    for(cont = 0; cont < i; cont++) {}
}

// Escolhe o digito que vai ser feita a escrita do numero
void escolhe_digito(uint32_t num) {
    switch(num){
    case 1:
        escrita_pinos(PORTAL_B_BASE, PINO_6 , 0x00);
        escrita_pinos(PORTAL_B_BASE, PINO_7,  PINO_7);
        escrita_pinos(PORTAL_D_BASE, PINO_2 , PINO_2);
        escrita_pinos(PORTAL_D_BASE, PINO_3,  PINO_3);
        break;
    case 2:
        escrita_pinos(PORTAL_B_BASE, PINO_6 , PINO_6);
        escrita_pinos(PORTAL_B_BASE, PINO_7,  0x00);
        escrita_pinos(PORTAL_D_BASE, PINO_2 , PINO_2);
        escrita_pinos(PORTAL_D_BASE, PINO_3,  PINO_3);
        break;
    case 3:
        escrita_pinos(PORTAL_B_BASE, PINO_6 , PINO_6);
        escrita_pinos(PORTAL_B_BASE, PINO_7,  PINO_7);
        escrita_pinos(PORTAL_D_BASE, PINO_2 , 0x00);
        escrita_pinos(PORTAL_D_BASE, PINO_3,  PINO_3);
        break;
    case 4:
        escrita_pinos(PORTAL_B_BASE, PINO_6 , PINO_6);
        escrita_pinos(PORTAL_B_BASE, PINO_7,  PINO_7);
        escrita_pinos(PORTAL_D_BASE, PINO_2 , PINO_2);
        escrita_pinos(PORTAL_D_BASE, PINO_3,  0x00);
        break;
    }
}

// Escreve 1 numero no digito especificado anteriormente. Condicao: 0 <= num <= 9
void escreve_1digito(uint8_t num){
    switch(num) {
        case 0:
               escrita_pinos(PORTAL_C_BASE, PINO_5 | PINO_4,PINO_5 + PINO_4);
               escrita_pinos(PORTAL_E_BASE, PINO_3 | PINO_2 | PINO_1 | PINO_0, PINO_3 + PINO_2 + PINO_1 + PINO_0);
               break;
        case 1:
               escrita_pinos(PORTAL_E_BASE, PINO_2 | PINO_1 ,PINO_2 + PINO_1);
               break;
        case 2:
               escrita_pinos(PORTAL_C_BASE, PINO_6  | PINO_4, PINO_6 + PINO_4);
               escrita_pinos(PORTAL_E_BASE, PINO_3 | PINO_1 | PINO_0, PINO_3 + PINO_1 + PINO_0);
               break;
        case 3:
               escrita_pinos(PORTAL_C_BASE, PINO_6 , PINO_6);
               escrita_pinos(PORTAL_E_BASE, PINO_3 |PINO_2 | PINO_1 | PINO_0,PINO_3 + PINO_2 + PINO_1 + PINO_0);
               break;
        case 4:
               escrita_pinos(PORTAL_C_BASE, PINO_6 | PINO_5 , PINO_6 + PINO_5);
               escrita_pinos(PORTAL_E_BASE, PINO_2 | PINO_1 , PINO_2 + PINO_1);
               break;
        case 5:
               escrita_pinos(PORTAL_C_BASE, PINO_6 | PINO_5, PINO_6 + PINO_5);
               escrita_pinos(PORTAL_E_BASE, PINO_3 | PINO_2 | PINO_0, PINO_3 + PINO_2 + PINO_0);
               break;
        case 6:
               escrita_pinos(PORTAL_C_BASE, PINO_6 | PINO_5 | PINO_4, PINO_6 + PINO_5 + PINO_4);
               escrita_pinos(PORTAL_E_BASE, PINO_3 | PINO_2  | PINO_0, PINO_3 + PINO_2 + PINO_0);
               break;
        case 7:
               escrita_pinos(PORTAL_E_BASE, PINO_2 | PINO_1 | PINO_0,PINO_2 + PINO_1 + PINO_0);
               break;
        case 8:
               escrita_pinos(PORTAL_C_BASE, PINO_6 | PINO_5 | PINO_4, PINO_6 + PINO_5 + PINO_4);
               escrita_pinos(PORTAL_E_BASE, PINO_3 | PINO_2 | PINO_1 | PINO_0, PINO_3 + PINO_2 + PINO_1 + PINO_0);
               break;
        case 9:
               escrita_pinos(PORTAL_C_BASE, PINO_6 | PINO_5 , PINO_6 + PINO_5);
               escrita_pinos(PORTAL_E_BASE, PINO_3 | PINO_2 | PINO_1 | PINO_0, PINO_3 + PINO_2 + PINO_1 + PINO_0);
        }
}

// Escreve um numero no display. Ele escreve nos 4 digitos, logo o numero deve seguir a condicao: 0 <= num <= 9999
void escreve_numero(uint32_t num) {
    uint32_t num1 = num / 1000;
    uint32_t num2 = num % 1000 / 100;
    uint32_t num3 = num % 100 / 10;
    uint32_t num4 = num % 100;

    limpa_display();
    escolhe_digito(1);
    escreve_1digito(num1);
    delay(DELAY);
    ////////////////////////////////////////////////////
    limpa_display();
    escolhe_digito(2);
    escreve_1digito(num2);
    delay(DELAY);
    ////////////////////////////////////////////////////
    limpa_display();
    escolhe_digito(3);
    escreve_1digito(num3);
    delay(DELAY);
    ////////////////////////////////////////////////////
    limpa_display();
    escolhe_digito(4);
    escreve_1digito(num4);
    delay(DELAY);
}

int main(void)
{
    volatile uint32_t ui32Loop;

    // Habilita os portais relativos aos pinos do display
    habilita_portal(PORTAL_B);
    habilita_portal(PORTAL_D);
    habilita_portal(PORTAL_C);
    habilita_portal(PORTAL_E);
    // Faz leitura dummy para efeito de atraso
    ui32Loop = ESC_REG(SYSCTL_RCGC2_R);

    configura_pino_saida(PORTAL_C_BASE, PINO_6 | PINO_5 | PINO_4);
    configura_pino_saida(PORTAL_E_BASE, PINO_3 | PINO_2 | PINO_1 | PINO_0);
    configura_pino_saida(PORTAL_D_BASE, PINO_3 | PINO_2);
    configura_pino_saida(PORTAL_B_BASE, PINO_6 | PINO_7);

    uint32_t aux, aux2;
    // Loop principal
    while(1)
    {
        for(aux = 0; aux < 9999; aux++) {
            for(aux2 = 0; aux2 < 60; aux2++){
                escreve_numero(aux);
            }
        }
    }
}
