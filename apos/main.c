
///////////////////////////////////////////////////////////////////////////////////// // project0.c disponibilizado pela TI adaptado.
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#define RED_LED GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3
 #ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line) // Rotina de erro
{ }
#endif
void  delay(uint32_t delayms){
    SysCtlDelay(delayms);

}
int main(void) {
// // Configurando o clock do sistema
SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
// // Habilitando a GPIO F e configurando os pinos 1, 2 e 3 como saída. (Ver os defines!)
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);
// // Loop //
while(1) {
// // Liga o LED vermelho que está no pino 1 da GPIO F //
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, RED_LED);
// // Delay //
    delay(1000000);
// // Liga o LED azul que está no pino 2 da GPIO F //
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, GREEN_LED);

   delay(5000000);

    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, RED_LED);
  delay(1000000);
}
}
