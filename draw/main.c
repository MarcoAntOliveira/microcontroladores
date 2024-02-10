#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
#include  "Nokia5110.h"

// Definições de pinos do display Nokia 5110

uint16_t horas = 0,  minutos = 0, segundos = 0;

// Função para escrever dados no display
void writeData(uint8_t data) {
    GPIOPinWrite(GPIO_PORTB_BASE, PIN_DC, PIN_DC); // Define DC como 1 (dados)
    SSIDataPut(SSI0_BASE, data); // Envia o dado pela interface SSI
    while(SSIBusy(SSI0_BASE)); // Aguarda a transmissão ser concluída
}

// Função para escrever comandos no display
void writeCommand(uint8_t command) {
    GPIOPinWrite(GPIO_PORTB_BASE, PIN_DC, 0); // Define DC como 0 (comando)
    SSIDataPut(SSI0_BASE, command); // Envia o comando pela interface SSI
    while(SSIBusy(SSI0_BASE)); // Aguarda a transmissão ser concluída
}

// Função para inicializar o display
void initDisplay() {
    GPIOPinWrite(GPIO_PORTB_BASE, PIN_RESET, 0); // Define RESET como 0
    SysCtlDelay(10); // Aguarda um curto período de tempo
    GPIOPinWrite(GPIO_PORTB_BASE, PIN_RESET, PIN_RESET); // Define RESET como 1

    writeCommand(0x21); // Ativa modo estendido
    writeCommand(0xB8); // Define a tensão do LCD (valor padrão)
    writeCommand(0x04); // Define o coeficiente de temperatura
    writeCommand(0x14); // Define o modo de exibição
    writeCommand(0x20); // Ativa modo básico
    writeCommand(0x0C); // Ativa display (modo normal)
}

// Função para desenhar um pixel na posição (x, y)
void drawPixel(uint8_t x, uint8_t y, bool value) {
    if (x >= 84 || y >= 48) return; // Verifica limites do display

    writeCommand(0x80 | x); // Define coluna
    writeCommand(0x40 | (y / 8)); // Define linha

    uint8_t buffer = 0x01 << (y % 8); // Calcula o bit correspondente

    writeData(value ? buffer : 0x00); // Desenha o pixel
}

// Função para desenhar um retângulo na posição (x, y) com largura e altura definidas
void drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool fill) {
    int i , j;
    for ( i = 0; i < width; i++) {
        for ( j = 0; j < height; j++) {
            drawPixel(x + i, y + j, fill);
        }
    }
}
void drawLine(uint8_t x, uint8_t y,   uint8_t width,  bool fill) {
    uint8_t i ;
    for ( i = 0; i < width; i++) {
            drawPixel(x + i, y, fill);
        }
}

// Função para desenhar os ponteiros do relógio
void  drawClockHands(uint8_t hours, uint8_t minutes, uint8_t seconds){
    // Desenha o ponteiro das horas
    uint8_t hourAngle = (hours % 12) * 30 + (minutes / 2);
    uint8_t hourX = 41 + 15 * sin((hourAngle - 90) * 0.01745);
    uint8_t hourY = 23 - 15 * cos((hourAngle - 90) * 0.01745);
    drawLine(41, 23, hourX, hourY);

    // Desenha o ponteiro dos minutos
    uint8_t minuteAngle = minutes * 6 + (seconds / 10);
    uint8_t minuteX = 41 + 20 * sin((minuteAngle - 90) * 0.01745);
    uint8_t minuteY = 23 - 20 * cos((minuteAngle - 90) * 0.01745);
    drawLine(41, 23, minuteX, minuteY);

    // Desenha o ponteiro dos segundos
    uint8_t secondAngle = seconds * 6;
    uint8_t secondX = 41 + 25 * sin((secondAngle - 90) * 0.01745);
    uint8_t secondY = 23 - 25 * cos((secondAngle - 90) * 0.01745);
    drawLine(41, 23, secondX, secondY);
}
void delayMilliseconds(uint32_t ms) {
    SysCtlDelay((SysCtlClockGet() / 3 / 1000) * ms);
}

int main(void) {


    // Configuração do sistema
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Configuração do clock
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // Habilita o clock do GPIO Port B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0); // Habilita o clock do SSI0

    // Configuração dos pinos do display
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, PIN_RESET | PIN_SCE | PIN_DC | PIN_SDIN | PIN_SCLK);
    GPIOPinWrite(GPIO_PORTB_BASE, PIN_RESET | PIN_SCE | PIN_DC | PIN_SDIN | PIN_SCLK, 0);

    // Configuração da interface SSI
    GPIOPinConfigure(SSI0_TX_PIN);
    //GPIOPinConfigure(GPIO_PB7_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTB_BASE, PIN_SDIN | PIN_SCLK);
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);
    SSIEnable(SSI0_BASE);

    // Inicialização do display
    initDisplay();
    drawClockHands(minutos,horas, segundos);
  /*
    while (1) {
        // Lógica do relógio

                             segundos++;
                             delayMilliseconds(500);
                        if (segundos > 59) {
                            delayMilliseconds(5000);
                            minutos++;
                            segundos = 0;
                        }
                        if (minutos> 59) {
                            delayMilliseconds(500);
                            //delay(500);
                            horas++;
                            minutos = 0;
                        }
                        if (horas > 23){
                            delayMilliseconds(5000);
                            //delay(5000);
                            horas = 0;
                        }


        // Obtenha as informações de tempo atual (horas, minutos, segundos)

        // Limpa o display
        drawRectangle(0, 0, 84, 48, false);

        // Desenha os ponteiros do relógio
        drawClockHands(horas, minutos, segundos);

        // Atualiza o display

        delayMilliseconds(500);
        // Aguarda um curto período de tempo
    }
    */
}

