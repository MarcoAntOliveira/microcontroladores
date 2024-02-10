#include <stdint.h>
#include<stdbool.h>
#include <stdio.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "Nokia5110.h"
#include "inc/tm4c123gh6pm.h"
#include <math.h>

void  delay(uint32_t delayms){
    SysCtlDelay(delayms);

}

void delayMicroseconds(uint32_t us) {
    SysCtlDelay((SysCtlClockGet() / 3 / 1000000) * us);
}


/*
void drawCircle(int16_t x0, int16_t y0, int16_t radius) {
  int16_t x = radius;
  int16_t y = 0;
  int16_t err = 0;

  while (x >= y) {
    Nokia5110_SetPxl(x0 + x, y0 + y); // Desenha ponto no quadrante superior direito
    Nokia5110_SetPxl(x0 + y, y0 + x); // Desenha ponto no quadrante superior esquerdo
    Nokia5110_SetPxl(x0 - y, y0 + x); // Desenha ponto no quadrante inferior esquerdo
    Nokia5110_SetPxl(x0 - x, y0 + y); // Desenha ponto no quadrante inferior direito
    Nokia5110_SetPxl(x0 - x, y0 - y); // Desenha ponto no quadrante inferior direito espelhado
    Nokia5110_SetPxl(x0 - y, y0 - x); // Desenha ponto no quadrante inferior esquerdo espelhado
    Nokia5110_SetPxl(x0 + y, y0 - x); // Desenha ponto no quadrante superior esquerdo espelhado
    Nokia5110_SetPxl(x0 + x, y0 - y); // Desenha ponto no quadrante superior direito espelhado

    if (err <= 0) {
      y += 1;
      err += 2 * y + 1;
    }
    if (err > 0) {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
}
*/
/*
const uint8_t ptr[] = {

   0x80, 0xC0, 0xE0, 0xE0, 0xF0, 0xF8, 0xF8, 0xFC, 0x7C, 0x7C, 0x7E, 0x3E, 0x3E, 0x3E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3E, 0x3E, 0x3E, 0x7E,
   0x7C, 0x7C, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0xC0, 0xF8, 0xFC, 0xFF, 0xFF, 0x7F, 0x1F, 0x07, 0x03, 0x01, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
   0x01, 0x01, 0x03, 0x07, 0x1F, 0x7F, 0xFF, 0xFF, 0xFC, 0xF8, 0x07, 0x0F, 0x3F, 0x7F, 0xFF, 0xFE, 0xF8, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF,
   0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE0, 0xE0, 0xF0, 0xF8, 0xFE, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x01, 0x01, 0x01, 0x03,
   0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3F, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x0F, 0x07, 0x07, 0x03,

  };
  */
const uint8_t circle[] =
{
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
   0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF,
   0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0x81, 0xFF,
   0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x81, 0xFF, 0xFF,
   0xA5, 0xA5, 0xA5, 0xA5, 0x81, 0xFF, 0xFF, 0xFF,
   0xBD, 0xBD, 0xBD, 0x81, 0xFF, 0xFF, 0xFF, 0xFF,
   0x81, 0x81, 0x81, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF

};

const uint8_t ptr[]= {
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07

};





// Exemplo de uso
int main(void) {
    float angle = 30.0;  // �ngulo em graus
    float sinValue;
    float cosValue;
    float pi = 3.14159 / 180.0;
  SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
  // Inicializa��o do display
  sinValue = sinf(angle * (pi));
  cosValue =cosf(angle*(pi));

  Nokia5110_Init();
  Nokia5110_Clear();
    Nokia5110_SetCursor(0, 0);
    Nokia5110_MyDrawing(ptr,2,2,7,8);
    Nokia5110_SetCursor(0,3);
    Nokia5110_OutDec(3);
    Nokia5110_SetCursor(5, 0);
    Nokia5110_OutDec(12);
    Nokia5110_SetCursor(5,5);
    Nokia5110_OutDec(6);
    Nokia5110_SetCursor(11,3);
    Nokia5110_OutDec(9);
    Nokia5110_SetCursor(cosValue, sinValue);
    Nokia5110_OutChar('|');
    Nokia5110_SetCursor(cosValue, sinValue);
    Nokia5110_OutChar('|');
    Nokia5110_SetCursor(5, 4);
    Nokia5110_OutChar('|');

  // Atualiza o display
 //Nokia5110_DisplayBuffer();
}
//Lembre-se de ajustar as coordenadas e o raio da circunfer�ncia de acordo com suas necessidades. Certifique-se tamb�m de ter a biblioteca "Nokia5110.h" inclu�da e corretamente configurada em seu ambiente de desenvolvimento.









