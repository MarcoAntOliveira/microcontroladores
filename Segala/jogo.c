#include "jogo.h"
#include "graficos.h"

void DrawTittle()
{
    Nokia5110_PrintBMP2(0,0,titulo_Bitmap,84,48);
    Nokia5110_DisplayBuffer();
}

void DrawWin()
{
    Nokia5110_PrintBMP2(0,0,You_in_Bitmap,84,48);
    Nokia5110_DisplayBuffer();
}

void DeawLose()
{
    Nokia5110_PrintBMP2(0,0,You_lose_Bitmap,84,48);
    Nokia5110_DisplayBuffer();
}

void DesenhaJogo(struct zombie *vecZombie, int qtdZombies, struct plant *vecPlant, int qtdPlants)
{
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    int i, j;
    for(i = 0; i < qtdZombies; i++)
    {
        Nokia5110_PrintBMP2(vecZombie[i].pos_x, vecZombie[i].pos_y, zombie_Bitmap, 9, 16);
    }
    for(i = 0; i < qtdPlants; i++)
    {
        Nokia5110_PrintBMP2(vecPlant[i].pos_x, vecPlant[i].pos_y, plant_Bitmap, 16, 16);
        for(j = 0; j < vecPlant[i].qtd_attacks; j++)
        {
            Nokia5110_PrintBMP2(vecPlant[i].ataques[j].pos_x, vecPlant[i].ataques[j].pos_y, hit_Bitmap, 2, 2);
        }
    }

    Nokia5110_DisplayBuffer();
}

void DesenhaBloco(int posx, int posy, struct zombie *vecZombie, int qtdZombies, struct plant *vecPlant, int qtdPlants, unsigned int points)
{
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    int i, j;
    for(i = 0; i < qtdZombies; i++)
    {
        Nokia5110_PrintBMP2(vecZombie[i].pos_x, vecZombie[i].pos_y, zombie_Bitmap, 9, 16);
    }
    for(i = 0; i < qtdPlants; i++)
    {
        Nokia5110_PrintBMP2(vecPlant[i].pos_x, vecPlant[i].pos_y, plant_Bitmap, 16, 16);
        for(j = 0; j < vecPlant[i].qtd_attacks; j++)
        {
            Nokia5110_PrintBMP2(vecPlant[i].ataques[j].pos_x + 16, vecPlant[i].ataques[j].pos_y + 4, hit_Bitmap, 2, 2);
        }
    }
    Nokia5110_PrintBMP2(posx, posy, bloco_Bitmap, 16, 16);
    Nokia5110_DisplayBuffer();
    Nokia5110_SetCursor(5,0);
    Nokia5110_OutString("Pts: ");
    Nokia5110_SetCursor(7,0);
    Nokia5110_OutUDec(points);
}


void DetectaColisao(struct zombie *vecZombie, int *qtdZombies, struct plant *vecPlant, int *qtdPlants)
{
    int i,j;
    for(i = 0; i < *qtdZombies; i++)
    {
        for(j = 0; j < *qtdPlants; j++)
        {
            if( (vecPlant[j].pos_y == vecZombie[i].pos_y) && (vecPlant[j].pos_x+16 >= vecZombie[i].pos_x))
            {
                vecZombie[i].pos_x = vecZombie[i].pos_x;
                (*qtdPlants)--;
                DiminuiPlantas(vecPlant, qtdPlants, j);
            }
        }
    }
}

void DetectaColisaoZumbi(struct zombie *vecZombie, int *qtdZombies, struct plant *vecPlant, int *qtdPlants, struct Player *jogador)
{
    int i,j;
    for(i = 0; i < *qtdPlants; i++)
    {
        for(j = 0; j < *qtdZombies; j++)
        {
            if( vecPlant[i].pos_y == vecZombie[j].pos_y )//confere se o zumbi e a planta estão na mesma linha
            {
                if(vecPlant[i].qtd_attacks > 0)//confere se a planta pode atacar
                {
                    if(vecPlant[i].ataques[0].pos_x >= vecZombie[j].pos_x)//confere se o tiro acertou
                    {
                        DesenhaJogo(vecZombie, *qtdZombies, vecPlant, *qtdPlants);
                        vecPlant[i].ataques[0] = vecPlant[i].ataques[1];
                        vecPlant[i].ataques[1] = vecPlant[i].ataques[2];
                        vecPlant[i].qtd_attacks--;
                        vecZombie[j].vida--;
                        if(vecZombie[j].vida == 0)//confere se o zumbi morreu e o remove
                        {
                            jogador->Points += 50;
                            (*qtdZombies)--;
                            DiminuiZumbis(vecZombie, qtdZombies, j);
                        }
                    }
                }
            }
        }
    }
}

void DiminuiPlantas(struct plant *vecPlant, int *qtdPlants, int PosiPlanta)
{
    int i;
    for(i = PosiPlanta; i < (*qtdPlants); i++)
    {
        vecPlant[i] = vecPlant[i+1];
    }
}

void DiminuiZumbis(struct zombie *vecZombie, int *qtdZombies, int PosiZombie)
{
    if(*qtdZombies == 0)
    {
        return;
    }
    int i;
    for(i = PosiZombie; i < (*qtdZombies); i++)
    {
        vecZombie[i] = vecZombie[i+1];
    }
}

void MostraRegras()
{
    SysCtlDelay(5000000);
    int menu = 0;
    while(menu < 6)
    {
        if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0))
        {
            menu++;
        }
        if(menu == 0)
        {
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(0,0);
            Nokia5110_OutString("Defenda sua casa dos zumbis.");
            SysCtlDelay(5000000);
        }
        if(menu == 1)
        {
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(0,0);
            Nokia5110_OutString("SW1-Mover");
            Nokia5110_SetCursor(0,1);
            Nokia5110_OutString("SW2-Selecionar");
            SysCtlDelay(5000000);
        }
        if(menu == 2)
        {
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(0,0);
            Nokia5110_OutString("Voce comeca com 150 pontos.");
            SysCtlDelay(5000000);
        }
        if(menu == 3)
        {
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(0,0);
            Nokia5110_OutString("Cada planta custa 50 pontos.");
            SysCtlDelay(5000000);
        }
        if(menu == 4)
        {
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(0,0);
            Nokia5110_OutString("Cada zumbi lhe garante 50 pontos.");
            SysCtlDelay(5000000);
        }
        if(menu == 5)
        {
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_SetCursor(0,0);
            Nokia5110_OutString("Voce vence ao derrotar a horda de zumbis.");
            SysCtlDelay(5000000);
        }
    }
    return;

}
