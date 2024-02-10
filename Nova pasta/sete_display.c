#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define PIN_A GPIO_PIN_0
#define PIN_B GPIO_PIN_1
#define PIN_C GPIO_PIN_2
#define PIN_D GPIO_PIN_3
#define PIN_E GPIO_PIN_4
#define PIN_F GPIO_PIN_5
#define PIN_G GPIO_PIN_6

void displayDigit(int digit);

const uint8_t digitMap[10] = {
    (PIN_A | PIN_B | PIN_C | PIN_D | PIN_E | PIN_F), /* 0 */
    (PIN_B | PIN_C), /* 1 */
    (PIN_A | PIN_B | PIN_D | PIN_E | PIN_G), /* 2 */
    (PIN_A | PIN_B | PIN_C | PIN_D | PIN_G), /* 3 */
    (PIN_B | PIN_C | PIN_F | PIN_G), /* 4 */
    (PIN_A | PIN_C | PIN_D | PIN_F | PIN_G), /* 5 */
    (PIN_A | PIN_C | PIN_D | PIN_E | PIN_F | PIN_G), /* 6 */
    (PIN_A | PIN_B | PIN_C), /* 7 */
    (PIN_A | PIN_B | PIN_C | PIN_D | PIN_E | PIN_F | PIN_G), /* 8 */
    (PIN_A | PIN_B | PIN_C | PIN_D | PIN_F | PIN_G) /* 9 */
};

int main(void) {
    // Define a frequência de operação do sistema em 80 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    
    // Habilita o periférico GPIOF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    
    // Configura o pino PF0 como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    // Configura o pino PF1 como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    // Configura o pino PF2 como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    // Configura o pino PF3 como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    // Configura o pino PF4 como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    // Configura o pino PF5 como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_5);
    // Configura o pino PF6 como saída
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_6);
    
    while(1) {
        for(int i=0; i<=9; i++) {
            displayDigit(i);
            SysCtlDelay(2000000); // espera 200ms antes de mostrar o próximo número
        }
    }
}

void displayDigit(int digit) {
    uint8_t segmentMask = digitMap[digit];
    
    GPIOPinWrite(GPIO_PORTF_BASE, PIN_A | PIN_B | PIN_C | PIN_D | PIN_E | PIN_F | PIN_G, segmentMask);
}
