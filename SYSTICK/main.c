#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#define SYS_FREQ 16000000  // Frequência do sistema em Hz
#define TICKS_PER_SECOND 1000  // Número de ticks do SysTick por segundo
#define DISPLAY_REFRESH_RATE 100  // Taxa de atualização do display em Hz
#define DISPLAY_UPDATE_INTERVAL (TICKS_PER_SECOND / DISPLAY_REFRESH_RATE)

volatile uint32_t g_ticks = 0;
volatile bool g_sw1Pressed = false;

void SysTick_Handler(void)
{
    // Incrementa o contador de ticks
    g_ticks++;

    // Verifica se o botão SW1 está pressionado a cada intervalo de atualização
    if (g_ticks % DISPLAY_UPDATE_INTERVAL == 0)
    {
        if (GPIO_PIN_4 & GPIO_PORTF_AHB_DATA_R)
        {
            g_sw1Pressed = true;
        }
        else
        {
            g_sw1Pressed = false;
        }
    }
}

void configureSysTick(void)
{
    // Configura o SysTick para gerar uma interrupção a cada 1ms
    SysTickPeriodSet(SYS_FREQ / TICKS_PER_SECOND);
    SysTickEnable();
    SysTickIntEnable();
}

void configureGPIO(void)
{
    // Habilita o clock para o port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Configura o pino PF4 (botão SW1) como entrada
    GPIOPinTypeGPIOInput(GPIO_PORTF_AHB_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_AHB_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

void configureDisplay(void)
{
    // Configura os pinos do display de 7 segmentos

    // Exemplo: Configura os pinos como saída
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);

    // ...
    // Configuração adicional dos pinos do display
    // ...
}

void updateDisplay(void)
{
    // Atualiza o display de acordo com o estado do botão SW1

    // Exemplo: Acende ou apaga os segmentos do display
    if (g_sw1Pressed)
    {
        // Acende os segmentos para exibir um número específico
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, 0xFF);
    }
    else
    {
        // Apaga todos os segmentos do display
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, 0x00);
    }
}

int main(void)
{
    // Configura os periféricos e interrupções
    configureSysTick();
    configureGPIO();
    configureDisplay();

    while (1)
    {
        // Atualiza o display
        updateDisplay();
    }
}
