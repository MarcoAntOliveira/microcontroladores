#include <stdint.h>
#include <stdio.h>

#define ESC_REG(x)                  (*((volatile uint32_t *)(x)))

//[[[[[[[[[[[[[[[[ REGISTRADORES ]]]]]]]]]]]]]]]]
//registradores pg 232

#define SYSCTL_RCGC2_R              0x400FE108          //Run Mode Clock Gating Control Register 2
#define GPIO_HB_CTL                 0x400FE06C        //GPIO [[[AHB]]] High-Performance Bus Control [[[AHB]]]
#define GPIO_RCGCGPIO_R             0x400FE608        //GPIO [[[APB]]] General-Purpose Input/Output Run Mode Clock Gating

//[[[[[[[[[[[[[[[[ PORTAIS ]]]]]]]]]]]]]]]]
#define PORTAL_A                    0x00000001 //0000 0001  portal (2^0 = ) 1, 1 em Hexadecimal, primeiro portal
#define PORTAL_B                    0x00000002 //0000 0010  portal (2^1 = ) 2, 2 em Hexadecimal, segundo portal
#define PORTAL_C                    0x00000004 //0000 0100  portal (2^2 = ) 4, 4 em Hexadecimal, terceiro portal
#define PORTAL_D                    0x00000008 //0000 1000  portal (2^3 = ) 8, 8 em Hexadecimal, quarto portal
#define PORTAL_E                    0x00000010 //0001 0000  portal (2^4 = ) 16, 10 em Hexadecimal, quinto portal
#define PORTAL_F                    0x00000020 //0010 0000  portal (2^5 = ) 32, 20 em Hexadecimal, sexto portal pg 340

//10.4 Register Map PG 658 (PORTAL BASES)
//portais APB
#define PORTAL_A_BASE 0x40004000
#define PORTAL_B_BASE 0x40005000
#define PORTAL_C_BASE 0x40006000
#define PORTAL_D_BASE 0x40007000
#define PORTAL_E_BASE 0x40024000
#define PORTAL_F_BASE 0x40025000
//portais AHB
#define PORTAL_A_BASE_AHB           0x40058000
#define PORTAL_B_BASE_AHB           0x40059000
#define PORTAL_C_BASE_AHB           0x4005A000
#define PORTAL_D_BASE_AHB           0x4005B000
#define PORTAL_E_BASE_AHB           0x4005C000
#define PORTAL_F_BASE_AHB           0x4005D000

#define SW1             0x10 //SW1 -      PF4  SW1
#define SW2             0x01 //SW2 -      PF0  SW2
#define LED_RED         0x02 //LED_RED    PF1  LED_RED
#define LED_BLUE        0x04 //LED_BLUE   PF2  LED_BLUE
#define LED_GREEN       0x08 //LED_GREEN  PF3  LED_GREEN

#define PINO_0                      0x01    //0000 0001  1 pino 0, 2^0 = 1 , posicao 0
#define PINO_1                      0x02    //0000 0010  2 pino 1, 2^1 = 2, posicao 1
#define PINO_2                      0x04    //0000 0100  4 pino 2, 2^2 = 4, posicao 2
#define PINO_3                      0x08    //0000 1000  8 pino 3, 2^3 = 8, posicao 3
#define PINO_4                      0x10    //0001 0000  16 pino 4, 2^4 = 16(10 em Hexa), posicao 4
#define PINO_5                      0x20    //0010 0000  32 pino 5, 2^5 = 32(20 em Hexa), posicao 5
#define PINO_6                      0x40    //0100 0000  64 pino 6, 2^6 = 32(40 em Hexa), posicao 6
#define PINO_7                      0x80    //1000 0000  128 pino 7, 2^5 = 128(80 em Hexa), posicao 7

//-------------------------------
//10 General-Purpose Input/Outputs (GPIOs) pg 649
#define GPIO_O_GPIODIR              0X400
#define GPIO_O_GPIODEN              0x51C //GPIO Digital Enable, habilita a funcao digital.
#define GPIO_O_GPIODR2R             0x500 //diz que a corrente eh de 2 mA
#define GPIO_O_GPIODR4R             0x504 //diz que a corrente eh de 4mA
#define GPIO_O_GPIODR8R             0x508 //diz que a corrente eh de 8 mA
#define GPIO_O_GPIOSLR              0x518//Habilita o controle do slew rate
#define GPIO_O_GPIOPUR              0x510 //diz que eh pull up (impede a um pino de ter sinal flutuante/ tensao no ar). Habilita um resistor pull-up
#define GPIO_O_DATA_R               0x000//GPIODATA, valores escritos aqui vao para os pinos, se eles foram configurados como saida.
#define GPIO_O_GPIOLOCK             0x520
#define GPIO_O_GPIOCR               0x524
//-------------------------------

#define DELAY_BASE 1000000  // 1.000.000 = 2.5 minutos, aproximadamente
#define DELAY_1S DELAY_BASE/(60*5.5) // 60*2.5)tempo de 1s

#define NVIC_EN0 0xE000E100
#define NVIC_EN1 0xE000E104
#define NVIC_EN2 0xE000E108
#define NVIC_EN3 0xE000E10C
#define NVIC_EN4 0xE000E110

#define INT_GPIO_A 0x0
#define INT_GPIO_B 0x1
#define INT_GPIO_C 0x2
#define INT_GPIO_D 0x3
#define INT_GPIO_E 0x4
#define INT_GPIO_F 0x1E

#define GPIO_O_IM  0x410
#define GPIO_O_IS  0x404
#define GPIO_O_IBE 0x408
#define GPIO_O_EV  0x40C
#define GPIO_O_RIS 0x414
#define GPIO_O_ICR 0x41C

//tipo de borda
#define GPIO_FALLING_EDGE   0x0  //tava em alta e vai pra baixa
#define GPIO_RISING_EDGE    0x4  //tava em baixa vai pra alta
#define GPIO_BOTH_EDGE      0x1  //em qualquer mudança de estado
#define GPIO_LOW_LEVEL      0x2  //sempre que tiver em baixa
#define GPIO_HIGH_LEVEL     0x6  //sempre que tiver em alta


#define NVIC_ST_CTRL    0xE000E010
#define NVIC_ST_RELOAD  0xE000E014
#define NVIC_ST_CURRENT 0xE000E018

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ INTERRUPÇÃO ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
void device_arm(void){
    __asm( " mrs r0, PRIMASK\n"
    " cpsie i\n"
     " bx lr\n");
}

void HabilitaInterrupcao (uint32_t ui32interrupcao){
    if(ui32interrupcao <=31){
        ESC_REG(NVIC_EN0)|= 1<<ui32interrupcao; //seta bit1 na interrupcao
    }
}

void configura_interrupcao_gpio (uint32_t portal_base, uint8_t pino, uint32_t tipo_interrupcao){

    ESC_REG(portal_base+GPIO_O_IBE) = ((tipo_interrupcao & 1)? //operador ternario
            (ESC_REG(portal_base + GPIO_O_IBE)| pino) :
            (ESC_REG(portal_base + GPIO_O_IBE)& ~ (pino)));

    ESC_REG(portal_base+GPIO_O_IS) = ((tipo_interrupcao & 2)?
                (ESC_REG(portal_base + GPIO_O_IS)| pino) :
                (ESC_REG(portal_base + GPIO_O_IS)& ~ (pino)));

    ESC_REG(portal_base+GPIO_O_EV) = ((tipo_interrupcao & 4)?
                (ESC_REG(portal_base + GPIO_O_EV)| pino) :
                (ESC_REG(portal_base + GPIO_O_EV)& ~ (pino)));


}

void habilita_interrupcao_gpio(uint32_t portal_base, uint8_t pino){
    ESC_REG(portal_base+GPIO_O_IM)|=pino;
}

void desabilita_interrupcao_gpio(uint32_t portal_base, uint8_t pino){
    ESC_REG(portal_base + GPIO_O_IM) &= ~(pino);
}

void limpa_interrupcao_gpio(uint32_t portal_base, uint8_t pino){
    ESC_REG(portal_base+GPIO_O_ICR) = pino;
}

void habilita_systick(void){
    ESC_REG(NVIC_ST_CTRL) |= 0b101; //coloca 1 no bit 0 e 2, pg 138
}

void habilita_interrupcao_systick(void){
    ESC_REG(NVIC_ST_CTRL) |= 0b10;
}

void desabilita_interrupcao_systick(void){
    ESC_REG(NVIC_ST_CTRL) &= ~(0b10);
}

void configura_systick(uint32_t valor){
    ESC_REG(NVIC_ST_RELOAD) = valor-1; //-1 pq comeca a contar do 0
}
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ INTERRUPÇÃO ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



//[[[[[[[[[[[[[[[[ HABILITAR PORTAIS ]]]]]]]]]]]]]]]]
void Habilita_portal_todos(uint32_t registrador, uint32_t portal) {
    ESC_REG(registrador)  |= portal;
}

void desabilita_portal(uint32_t registrador, uint32_t portal) {
    ESC_REG(registrador) &= ~(portal);
}

void configura_pino_saida(uint32_t portal_base, uint8_t pino){
    ESC_REG(portal_base + GPIO_O_GPIODIR)  |= pino;
    ESC_REG(portal_base + GPIO_O_GPIODEN)  |= pino;
    ESC_REG(portal_base + GPIO_O_GPIODR2R) |= pino;
    ESC_REG(portal_base + GPIO_O_GPIODR4R) &= ~(pino);
    ESC_REG(portal_base + GPIO_O_GPIODR8R) &= ~(pino);
    ESC_REG(portal_base + GPIO_O_GPIOSLR) &= ~(pino);
}
void configura_pino_entrada(uint32_t portal_base, uint8_t pino) // Habilita o pino do portal , configura como entrada digital
{
    ESC_REG(portal_base + GPIO_O_GPIODIR)  &= ~(pino);//acessa o GPIO de direcao do portal apenas no pino passado como parametro para desabilita-la no pino
    ESC_REG(portal_base + GPIO_O_GPIODEN)  |= pino;//acessa o GPIO da funcao digital do portal apenas no pino passado como parametro para habilita-la no pino
    ESC_REG(portal_base + GPIO_O_GPIODR2R) |= pino;//acessa o GPIO da corrente de 2mA apenas no pino passado como parametro para habilita-la no pino
   // ESC_REG(portal_base + 0x06C) |= pino;
    ESC_REG(portal_base + GPIO_O_GPIODR4R) &= ~(pino);//acessa o GPIO da corrente de 4mA apenas no pino passado como parametro para desabilita-la
    ESC_REG(portal_base + GPIO_O_GPIODR8R) &= ~(pino);//acessa o GPIO da corrente de 8mA apenas no pino passado como parametro para desabilita-la
    ESC_REG(portal_base + GPIO_O_GPIOSLR ) &= ~(pino);//desabilita o slew rate se o mesmo tiver sido habilitado(que so eh habilitado em 8mA)
}

void configura_pino_pull_up(uint32_t portal_base, uint8_t pino)
{
    ESC_REG(portal_base + GPIO_O_GPIOPUR)  |= pino;//acessa o GPIO de Pull Up e ativa o resistor pull up para o pino passado como parametros
}

void escrita_pinos(uint32_t portal_base, uint8_t pino, uint8_t valor) {
    ESC_REG (portal_base + (GPIO_O_DATA_R + (pino << 2))) = valor;
}

uint32_t leitura_pinos(uint32_t portal_base, uint8_t pino)
{
    return (ESC_REG (portal_base + (GPIO_O_DATA_R + (pino << 2))));
}
void destrava_pino(uint32_t portal_base, uint8_t pino)
{//Register 19: GPIO Lock (GPIOLOCK), offset 0x520 pg 684
    ESC_REG(portal_base + GPIO_O_GPIOLOCK) |= 0x4C4F434B;
    ESC_REG(portal_base + GPIO_O_GPIOCR ) |= pino;
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
        case 1://F
            escrita_pinos(PORTAL_C_BASE, PINO_5 , PINO_5);
               break;
        case 2://A
               escrita_pinos(PORTAL_E_BASE, PINO_0 , PINO_0);
               break;
        case 3://B
                escrita_pinos(PORTAL_E_BASE, PINO_1 , PINO_1);
               break;
        case 4://C
                escrita_pinos(PORTAL_E_BASE, PINO_2 , PINO_2);
               break;
        case 5://D
            escrita_pinos(PORTAL_E_BASE, PINO_3 , PINO_3);
               break;
        case 6://E
            escrita_pinos(PORTAL_C_BASE, PINO_4 , PINO_4);
               break;
        }
}

// Escreve um numero no display. Ele escreve nos 4 digitos, logo o numero deve seguir a condicao: 0 <= num <= 9999
void horario(int velocidade) {
    int i;
            limpa_display();
            escolhe_digito(1);
            escreve_1digito(1);
            delay(velocidade);

            for(i=1;i<5;i++){
            limpa_display();
            escolhe_digito(i);
            escreve_1digito(2);
            delay(velocidade);
            }
            limpa_display();
            escolhe_digito(4);
            escreve_1digito(3);
            delay(velocidade);

            limpa_display();
            escolhe_digito(4);
            escreve_1digito(4);
            delay(velocidade);

            for(i=4;i>0;i--){
            limpa_display();
            escolhe_digito(i);
            escreve_1digito(5);
            delay(velocidade);
            }

            limpa_display();
            escolhe_digito(1);
            escreve_1digito(6);
            delay(velocidade);
}


void anti_horario(int velocidade) {
    int i;
                limpa_display();
                escolhe_digito(1);
                escreve_1digito(1);
                delay(velocidade);

                limpa_display();
                escolhe_digito(1);
                escreve_1digito(6);
                delay(velocidade);

                for(i=1;i<5;i++){
                limpa_display();
                escolhe_digito(i);
                escreve_1digito(5);
                delay(velocidade);
                }

                limpa_display();
                escolhe_digito(4);
                escreve_1digito(4);
                delay(velocidade);

                limpa_display();
                escolhe_digito(4);
                escreve_1digito(3);
                delay(velocidade);

                for(i=4;i>0;i--){
                limpa_display();
                escolhe_digito(i);
                escreve_1digito(2);
                delay(velocidade);
    }

}



void giro(int sentido,int velocidade){
    if(sentido==1){
        horario(velocidade);
    }
    if(sentido==2){
        anti_horario(velocidade);
    }
}

int sentido=1;
int velocidade=0;
int tipo_de_velocidade=0;

void interrupcao(void){
    delay(20000);
    if(leitura_pinos(PORTAL_F_BASE,SW1)==0x00){
        tipo_de_velocidade++;
        switch(tipo_de_velocidade){
        case 1:
            velocidade=200000;
            break;
        case 2:
            velocidade=100000;
            break;
        case 3:
            velocidade=50000;
            break;
        case 4:
            velocidade=25000;
            break;
        case 5:
            velocidade=10000;
            break;
        case 6:
            velocidade=200000;
            tipo_de_velocidade=0;
            break;
        }
    }
    if(leitura_pinos(PORTAL_F_BASE,SW2)==0x00){
        sentido++;
        switch(sentido){
        case 1:
            sentido=1;
            break;
        case 2:
            sentido=2;
            break;
        case 3:
            sentido=1;
            break;
        }
    }
    limpa_display();
    limpa_interrupcao_gpio(PORTAL_F_BASE, SW1|SW2); // desativa só dessa vez

}



int main(void)
{
    volatile uint32_t ui32Loop;

    // Habilita os portais relativos aos pinos do display
    Habilita_portal_todos(SYSCTL_RCGC2_R,PORTAL_B);
    Habilita_portal_todos(SYSCTL_RCGC2_R,PORTAL_D);
    Habilita_portal_todos(SYSCTL_RCGC2_R,PORTAL_C);
    Habilita_portal_todos(SYSCTL_RCGC2_R,PORTAL_E);
    Habilita_portal_todos(GPIO_RCGCGPIO_R,PORTAL_F);

    // Faz leitura dummy para efeito de atraso
    ui32Loop = ESC_REG(SYSCTL_RCGC2_R);

    configura_pino_saida(PORTAL_C_BASE, PINO_6 | PINO_5 | PINO_4);
    configura_pino_saida(PORTAL_E_BASE, PINO_3 | PINO_2 | PINO_1 | PINO_0);
    configura_pino_saida(PORTAL_D_BASE, PINO_3 | PINO_2);
    configura_pino_saida(PORTAL_B_BASE, PINO_6 | PINO_7);

    destrava_pino(PORTAL_F_BASE,PINO_0); // destrava botão
    configura_pino_entrada(PORTAL_F_BASE,PINO_0 | PINO_4);// habilita os botoes como entrada de dado
    configura_pino_pull_up(PORTAL_F_BASE,PINO_0 | PINO_4);// ativa a função pull up

    HabilitaInterrupcao (INT_GPIO_F);
    habilita_interrupcao_gpio(PORTAL_F_BASE, SW1 | SW2); //SW1
    configura_interrupcao_gpio (PORTAL_F_BASE, SW1, GPIO_FALLING_EDGE);
    configura_interrupcao_gpio (PORTAL_F_BASE, SW2, GPIO_FALLING_EDGE);

    while(1){
        if(tipo_de_velocidade!=0){
            giro(sentido,velocidade);
        }
    }
}












