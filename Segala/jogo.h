#ifndef JOGO_H
#define JOGO_H

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


struct Player
{
    int player_turn;
    int isDead;
    int Points;
};

struct zombie
{
    int vida;
    int pos_x;
    int pos_y;
};

struct attack
{
    int pos_x;
    int pos_y;
};

struct plant
{
    int vida;
    int pos_x;
    int pos_y;

    int qtd_attacks;
    struct attack ataques[3];
};



void DrawTittle();

void DrawWin();

void DeawLose();

//Esta função limpa a tela e depois redesenha todos os objetos de volta em suas posições
void DesenhaJogo(struct zombie *vecZombie, int qtdZombies, struct plant *vecPlant, int qtdPlants);

void DesenhaBloco(int posx, int posy, struct zombie *vecZombie, int qtdZombies, struct plant *vecPlant, int qtdPlants, unsigned int points);

void DetectaColisao(struct zombie *vecZombie, int *qtdZombies, struct plant *vecPlant, int *qtdPlants);

void DetectaColisaoZumbi(struct zombie *vecZombie, int *qtdZombies, struct plant *vecPlant, int *qtdPlants, struct Player *jogador);


void DiminuiPlantas(struct plant *vecPlant, int *qtdPlants, int PosiPlanta);

void DiminuiZumbis(struct zombie *vecZombie, int *qtdZombies, int PosiZombie);

void MostraRegras();

#endif
