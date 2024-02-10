/*
 * functions_matriz_and_display.h
 *
 *  Created on: 4 de mai de 2019
 *      Author: Danilo
 */

#ifndef FUNCTIONS_MATRIZ_H_
#define FUNCTIONS_MATRIZ_H_

uint32_t get_matriz_botao( uint32_t value )
{
    uint32_t portal_linhas[4] = {GPIO_PORTF_BASE, GPIO_PORTB_BASE, GPIO_PORTB_BASE, GPIO_PORTB_BASE};
    uint32_t portal_colunas[4] = {GPIO_PORTF_BASE, GPIO_PORTF_BASE, GPIO_PORTF_BASE, GPIO_PORTF_BASE};
    uint32_t pinos_linhas[4] = {GPIO_PIN_4, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_5};
    uint32_t pinos_colunas[4] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3};
    uint32_t numero[4][4] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    uint32_t retorno = value;

    uint32_t i,j;
    for (i=0; i<4; i++)
    {
        GPIOPinWrite(portal_colunas[i], pinos_colunas[0]|pinos_colunas[1]|pinos_colunas[2]|pinos_colunas[3], ~(pinos_colunas[i]));
        for(j=0; j<4; j++)
        {
           if(GPIOPinRead(portal_linhas[j], pinos_linhas[j]) == 0x00 )
           {
               retorno = numero[j][i];
           }
        }
    }
    return retorno;
}

#endif /* FUNCTIONS_MATRIZ_H_ */
