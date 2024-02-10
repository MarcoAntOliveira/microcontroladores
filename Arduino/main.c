
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
#include "driverlib/Adafruit-GFX/Adafruit_GFX.h"
#include "driverlib/Adafruit-PCD8544/Adafruit_PCD8544.h"

#define PIN_RST GPIO_PIN_2
#define PIN_DC  GPIO_PIN_3
#define PIN_CS  GPIO_PIN_4

void delayMs(uint32_t ms) {
    SysCtlDelay((SysCtlClockGet() / 3) * ms / 1000);
}

void setup() {
    // Configuração do sistema
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Configuração dos pinos do display
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, PIN_RST | PIN_DC | PIN_CS);
    GPIOPinWrite(GPIO_PORTA_BASE, PIN_RST | PIN_DC | PIN_CS, 0);

    // Inicialização do display
    Adafruit_PCD8544 display = Adafruit_PCD8544(SSI0_BASE, GPIO_PORTA_BASE, PIN_RST, PIN_DC, PIN_CS);
    display.begin();
    display.setContrast(40);

    // Limpa o display
    display.clearDisplay();
}

void loop() {
    // Escreve um texto no display
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0, 0);
    display.println("Teste Nokia 5110");

    // Atualiza o display
    display.display();

    // Aguarda 1 segundo
    delayMs(1000);

    // Limpa o display
    display.clearDisplay();

    // Atualiza o display
    display.display();

    // Aguarda 1 segundo
    delayMs(1000);
}

int main(void) {
    setup();

    while (1) {
        loop();
    }
}
