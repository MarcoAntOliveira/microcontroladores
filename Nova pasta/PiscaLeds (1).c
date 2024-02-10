//Includes das bibliotecas que contém as funções e os #defines de variáveis que usamos no código 

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"

uint8_t ui8PinData = 2; 

// O código a seguir existe para ligar e desligar o led RGB imbutido na plaquinha 
int main(void)
{
    //clock é responsável pela temporização que ocorre no microcontrolador
    //precisamos de precisão dependendo do caso/código/projeto
    //o clock determina a velocidade de funcionamento em Hz
    //o Tiva tem mais de uma fonte de clock disponível para utilização, a fonte escolhida depende do projeto e precisão necessárias

    SysCtlClockSet( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);
    // A função acima configura o clock que iremos usar. Ela recebe apenas uma variável segundo o datasheet
    // mas o operador | indica que estamos fazendo alterações em bit ( | é a operação OR, como se estive somando os bits das variaveis )
    // exemplo: 10010101 | 00010110 = 10010111, esse valor final é o que ele vai passar para a função (o tal do masking)
    // Dentro da função temos: divisor de clock do sistema (temos várias opções para usar)
    // Escolho se uso o pll com  SYSCTL_USE_PLL ou o oscilador com SYSCTL_USE_OSC.
    // A frequencia do cristal externo (Tbm temos várias opções). Valores abaixo de YSCTL_XTAL_5MHZ não tem como usar se usarmos o PLL
    // A fonte do oscilador pode ser escolhida entre SYSCTL_OSC_MAIN, SYSCTL_OSC_INT, SYSCTL_OSC_INT4, SYSCTL_OSC_INT30, ou SYSCTL_OSC_EXT32
    // Sendo o ultimo disponível para dispositivos como modulo de hibernação
    // Posso também desativar o oscilador interno e usar um externo. Há variáveis específicas para usar na função e fazer isso se quiser
    // Essa função só é valida para dispostivos TM4C123. Há outra função p/ os demais. 

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    /*
    A função acima ativa o periférico que ela recebe como argumento
        preciso ativar os periféricos para que eles possam ser usado para leitura/escrita
       ----> por padrão todos estão desligados <----
        aqui ela está ativando a porta F, para que possamos usar os pinos dessa porta (os LEDS e os botões/switches são acessados por ela)
        Posso habilidar um dos dois tipos de caminhos para essas portas, o APB( Advanced Peripheral Bus) e o AHB Advanced High-
        Performance Bus) qual usar depende do que quero fazer e de com quais sinais estou lidando
        para fazer essa alteração só preciso mudar os #defines das variaveis, atualmente usamos o APB 

        Os pinos das portas podem ser utilizados como periféricos ou GPIO, mas nem todos podem ser configurados, alguns são apenas GPIO
        Os leds podem ser acessados através dos pinos PF1, PF2 E PF3
    */

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    /* 
    Depois de ativar a porta F para utilização de seus pinos, aqui configuramos que os pinos 1,2 e 3 serão pinos de saída (ligarão
        os leds. Como argumento passamos a porta a qual os pinos pertencem, e então passamos os pinos que iremos utilizar.
        Depois de ativar as portas e configurar como saída, vamos utilizá-las dentro do While e ver como funciona.
     */
    while(){

        /*Essa função Write vai passar para os pinos se eles devem ser ativados ou desativados, ativando para ligar o led
        e desativando para desligar
        No início do código, a variávei ui8PinData foi inicializada com 2, pq 2 em binário é o código para ativar o pino 1
        logo depois ela é aumentada para 4 ali no Else, ativando o pino 2, etc
        Quando chega em 8, ela é setada pra 2 novamente para reiniciar o loop*/
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2| GPIO_PIN_3, ui8PinData);

        //delay manual
        for (int i = 0;i <20000000; i++){}

        // aqui ela recebe 0x00 para desligar os leds e reiniciar o loop, já que por padrão eles estão desligados
        // e só irão ligar se passar para a porta o código que representa o pino, no caso de ui8PinData
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);

        //delay
        for (int i = 0;i <20000000; i++){}

        //checa se a variável está setada para ligar o pino 3, se estiver, volta para 2, se não estiver, passa para o próximo
        // valor para ligar o próximo LED
        if(ui8PinData==8){
            ui8PinData=2;
        }else {
            ui8PinData=ui8PinData*2;
        }
        
        
    }

}
