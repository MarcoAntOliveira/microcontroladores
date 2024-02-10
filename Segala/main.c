#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/hibernate.h"
#include "driverlib/interrupt.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"


#include "Nokia5110.h"

#include "jogo.h"

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);//habilitita a frequencia do tiva para 40Mhz

    //Inicializa a tela
    Nokia5110_Init();
    Nokia5110_Clear();

    //Inicializa os botões
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//Habilita o portal F
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);//Habilita tanto o pino 4(sw1) quanto o pino 0 (sw2) como entradas
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);


    //Escreve o título
    DrawTittle();
    SysCtlDelay( 50000000 );//delay


    //Menu
    while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
    {
        Nokia5110_Clear();
        Nokia5110_ClearBuffer();
        Nokia5110_SetCursor(0,0);
        Nokia5110_OutString("Start (SW1)");
        Nokia5110_SetCursor(0,4);
        Nokia5110_OutString("Regras (SW2)");

        if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0))
        {
            SysCtlDelay( 100000 );
            MostraRegras();
            SysCtlDelay( 10000000 );
        }
        SysCtlDelay( 100000 );//delay
    }

    srand(time(NULL));

    int i, j, k;

    struct Player jogador;//cria um jogador
    jogador.player_turn = 1;
    jogador.Points = 150;
    jogador.isDead = 0;

    int rand_zombie = 0;


    struct zombie vec_zombies[10];
    struct plant vec_plants[10];

    int qtd_zombies = 0;
    int qtd_plants = 0;
    int contador = 0;

    int maxZombies = 5;
    int level = 1;
    int first = 1;

    while(!jogador.isDead)
    {
        if(first == 1 && level == 1)
        {
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(2,2);
            Nokia5110_OutString("Level 1");
            SysCtlDelay( 25000000 );
            first = 0;
        }
        if(first == 1 && level == 2)//aumenta a quantidade de zumbis
        {
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(2,2);
            Nokia5110_OutString("Level 2");
            SysCtlDelay( 25000000 );
            qtd_zombies = 0;
            qtd_plants = 0;
            maxZombies = 8;
            contador = 0;
            first = 0;
        }
        if(!jogador.player_turn)//Turno de ataque
        {
            jogador.player_turn++;
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(2,2);
            Nokia5110_OutString("Turno");
            Nokia5110_SetCursor(4,3);
            Nokia5110_OutString("de");
            Nokia5110_SetCursor(2,4);
            Nokia5110_OutString("Ataque");
            SysCtlDelay( 25000000 );
            DesenhaJogo(vec_zombies, qtd_zombies, vec_plants, qtd_plants);
            if(contador < maxZombies)
            {
                rand_zombie = rand() % 3;
                vec_zombies[qtd_zombies].vida = 2;
                vec_zombies[qtd_zombies].pos_x = 72;
                vec_zombies[qtd_zombies].pos_y = 16*(rand_zombie);


                qtd_zombies++;
                contador++;
            }
            if(qtd_plants == 0)
            {
                jogador.isDead = 1;break;
            }
            for(i = 0; i < qtd_plants; i++)
            {
                if(vec_plants[i].qtd_attacks < 3)
                {
                    struct attack atk;
                    atk.pos_x = vec_plants[i].pos_x + 16;
                    atk.pos_y = vec_plants[i].pos_y + 4;
                    vec_plants[i].ataques[vec_plants[i].qtd_attacks] = atk;
                    vec_plants[i].qtd_attacks++;
                }
            }
            for(j = 0; j < 9; j++)//laço dos passos
            {
                for(i = 0; i < qtd_plants; i++)//move os tiros de cada planta
                {
                    for(k = 0; k < vec_plants[i].qtd_attacks; k++)
                    {
                        vec_plants[i].ataques[k].pos_x = vec_plants[i].ataques[k].pos_x + 2;
                        if(vec_plants[i].ataques[k].pos_x > 65)
                        {
                            vec_plants[i].ataques[0] = vec_plants[i].ataques[1];
                            vec_plants[i].ataques[1] = vec_plants[i].ataques[2];
                            vec_plants[i].qtd_attacks--;
                        }
                    }
                }
                for(i = 0; i < qtd_zombies; i++)//move os zumbis
                {
                    vec_zombies[i].pos_x = vec_zombies[i].pos_x - 1;
                    DetectaColisao(vec_zombies, &qtd_zombies, vec_plants, &qtd_plants);
                    if(vec_zombies[i].pos_x == 0){jogador.isDead = 1;break;}
                }
                DetectaColisaoZumbi(vec_zombies, &qtd_zombies, vec_plants, &qtd_plants, &jogador);//confere se a bala acertou o zumbi
                DesenhaJogo(vec_zombies, qtd_zombies, vec_plants, qtd_plants);
                if(qtd_zombies == 0)
                {
                    DesenhaJogo(vec_zombies, 0, vec_plants, qtd_plants);
                    SysCtlDelay( 10000000 );
                    if(level == 1){level = 2; first = 1; break;}
                    if(level == 2){jogador.isDead = -1; break;}
                }
                //DesenhaJogo(vec_zombies, qtd_zombies, vec_plants, qtd_plants);
                SysCtlDelay( 5000000 );
            }
            if(jogador.Points < 50){jogador.player_turn--;}
            SysCtlDelay( 10000 );//delay
        }

        else//Turno de defesa
        {
            jogador.player_turn--;
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(2,2);
            Nokia5110_OutString("Turno");
            Nokia5110_SetCursor(4,3);
            Nokia5110_OutString("de");
            Nokia5110_SetCursor(2,4);
            Nokia5110_OutString("Defesa");
            SysCtlDelay( 25000000 );//delay
            //if(jogador.Points < 50 || qtd_plants >= 5){break;}
            if(jogador.Points >= 50)
            {
                vec_plants[qtd_plants].vida = 3;
                vec_plants[qtd_plants].qtd_attacks = 0;
                int contador;
                contador = 0;
                while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0))
                {
                    if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)){ SysCtlDelay( 1000000 ); contador++;}
                    if(contador > 4){contador = 0;}
                    vec_plants[qtd_plants].pos_x = 16*contador;
                    DesenhaBloco(vec_plants[qtd_plants].pos_x , 0, vec_zombies, qtd_zombies, vec_plants, qtd_plants, jogador.Points);
                    SysCtlDelay( 1000000 );//delay
                }
                SysCtlDelay( 10000000 );//delay
                contador = 0;
                while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0))
                {
                    if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)){ SysCtlDelay( 1000000 );contador++;}
                    if(contador > 2){contador = 0;}
                    vec_plants[qtd_plants].pos_y = 16*contador;
                    DesenhaBloco(vec_plants[qtd_plants].pos_x , vec_plants[qtd_plants].pos_y, vec_zombies, qtd_zombies, vec_plants, qtd_plants, jogador.Points);
                    SysCtlDelay( 1000000 );//delay
                }
                SysCtlDelay( 100000 );

                jogador.Points -= 50;
                qtd_plants++;
            }
            DesenhaJogo(vec_zombies, qtd_zombies, vec_plants, qtd_plants);
            SysCtlDelay( 10000000 );//delay
        }
    }
    if(jogador.isDead == 1)//Tela de derrota
    {
        while(1)
        {
            DeawLose();
            SysCtlDelay( 1000000000 );//delay
        }
    }

    if(jogador.isDead == -1)//Tela de vitória
    {
        while(1)
        {
            DrawWin();
            SysCtlDelay( 1000000000 );//delay
        }
    }

}
