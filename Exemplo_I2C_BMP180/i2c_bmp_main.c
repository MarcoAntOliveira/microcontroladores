p// Exemplo de aplicação do protocolo de comunicação I2C utilizando o sensor BMP180 e a placa Tivaware

// Ligação dos pinos

// VCC --- 3.3v
// GND --- GND
// SCL --- PD0
// SDA --- PD1

// Declaração das bibliotecas
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "sensorlib/hw_bmp180.h"
#include "sensorlib/i2cm_drv.h"
#include "sensorlib/bmp180.h"
#include "drivers/rgb.h"


// Usando 8 bits por byte e bit de stop, sem paridade
// O Led rgb pisca a 1 Hz quando a inicialização estiver completa e ocódigo estiver rodando
//*****************************************************************************
// Atribuindo o endereço do sensor
//*****************************************************************************
#define BMP180_I2C_ADDRESS      0x77
//*****************************************************************************
// Array para o led RGB
//*****************************************************************************
uint32_t g_pui32Colors[3];
//*****************************************************************************
// Estrutura para o mestre
//*****************************************************************************
tI2CMInstance g_sI2CInst;
//*****************************************************************************
// Estrutura para o sensor BMP
//*****************************************************************************
tBMP180 g_sBMP180Inst;
//*****************************************************************************
// Flag para alertar o programa principal que o sensor esta pronto
//*****************************************************************************
volatile uint_fast8_t g_vui8DataFlag;
//*****************************************************************************
// Rotina de erro caso ocorra algum
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//Função da chamada do sensor retorna a flag para main
//*****************************************************************************
void BMP180AppCallback(void* pvCallbackData, uint_fast8_t ui8Status)
{
    if(ui8Status == I2CM_STATUS_SUCCESS)
    {
        g_vui8DataFlag = 1;
    }
}

//*****************************************************************************
//Chamada como resultado da interrupção I2C3
//*****************************************************************************
void
BMP180I2CIntHandler(void)
{

// I2C Handler vai receber o ponteiro de instruçao
    I2CMIntHandler(&g_sI2CInst);
}

//*****************************************************************************
// Chamada para interrupção SysTick, usada para gerar o intervalo entre as amostras
//*****************************************************************************
void
SysTickIntHandler()
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
    BMP180DataRead(&g_sBMP180Inst, BMP180AppCallback, &g_sBMP180Inst);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
}

//*****************************************************************************
//Configuração da UART
//*****************************************************************************
void
ConfigureUART(void)
{
    // Habilitando o periferico
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Habilitando a UART0
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Configure GPIO Pins for UART mode.
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Usando o clock interno de 16 MHz
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Configurando o baud rate
    UARTStdioConfig(0, 115200, 16000000);
}

//*****************************************************************************
//*****************************************************************************
int
main(void)
{
    float fTemperature, fPressure, fAltitude;
    int32_t i32IntegerPart;
    int32_t i32FractionPart;

    // Configurando o clock
SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);


    // Inicializando a UART
    ConfigureUART();

    // Printando na tela Exemplo
    UARTprintf("\033[2JBMP180 Exemplo\n");

    //Setando as cores do rgb
    g_pui32Colors[RED] = 0x8000;
    g_pui32Colors[BLUE] = 0x8000;
    g_pui32Colors[GREEN] = 0x8000;

    //Inicializando o RGB
    RGBInit(0);
    RGBColorSet(g_pui32Colors);
    RGBIntensitySet(0.5f);
    RGBEnable();

    // Habilitando o periferico I2C3 para ser usado (PD0 SCL e PD1 SDA)
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Fazendo o mapeamento das portas que vão ser usadas para o i2c
    MAP_GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    MAP_GPIOPinConfigure(GPIO_PD1_I2C3SDA);

    // Selecionando a comunicação i2c para os pinos
    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
    MAP_GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);

    // Fazendo o mapeamento do led
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);

    // Habilitando a interrupção para o processador
    MAP_IntMasterEnable();

    // Inicializando o i2c
    I2CMInit(&g_sI2CInst, I2C3_BASE, INT_I2C3, 0xff, 0xff,
             MAP_SysCtlClockGet());

    // Inicializando o sensor BMP180
    BMP180Init(&g_sBMP180Inst, &g_sI2CInst, BMP180_I2C_ADDRESS,
               BMP180AppCallback, &g_sBMP180Inst);

    // Aguarda a flag de inicialização para continuar o programa
    while(g_vui8DataFlag == 0)
    {
     // Aguardando a I2C
    }

    // Resetando a flag para proxima chamada
    g_vui8DataFlag = 0;

    // Habilitando SysTick em 10 Hz
    MAP_SysTickPeriodSet(MAP_SysCtlClockGet() / (10 * 3));
    MAP_SysTickIntEnable();
    MAP_SysTickEnable();

    // Apos tudo estar configurado e inicializado começa a piscar o led
    RGBBlinkRateSet(1.0f);

    // Loop para coleta e mostra dos dados
    while(1)
    {

        //Comando que inicia a leitura dos dados do sensor
        // Requisita a medição de temperatura e aguarda depois requisita a medição de pressão e aguarda
        // Quando todas as leituras estiverem ok e no buffer os resultados são chamados através da interrupção I2C possibilitando que o processador possa executar outras tarefas enquanto não estiver pronto os dados
        BMP180DataRead(&g_sBMP180Inst, BMP180AppCallback, &g_sBMP180Inst);
        while(g_vui8DataFlag == 0)
        {
         // Esperando que os dados estejam prontos
        }

        //Reseta a flag de dados
        g_vui8DataFlag = 0;

        // Coleta a copia dos dados coletados de temperatura em formato float
        BMP180DataTemperatureGetFloat(&g_sBMP180Inst, &fTemperature);

        // Manipulação dos dados de temperatura em float para que fique melhor impresso
        i32IntegerPart = (int32_t) fTemperature;
        i32FractionPart =(int32_t) (fTemperature * 1000.0f);
        i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
        if(i32FractionPart < 0)
        {
            i32FractionPart *= -1;
        }

        // Escreve a temperatura na tela
        UARTprintf("Temperatura %3d.%03d\t\t", i32IntegerPart, i32FractionPart);

        // Coleta a copia dos dados coletados de pressao em formato float
        BMP180DataPressureGetFloat(&g_sBMP180Inst, &fPressure);

        // Manipulação dos dados de pressão em float para que fique melhor impresso
        i32IntegerPart = (int32_t) fPressure;
        i32FractionPart =(int32_t) (fPressure * 1000.0f);
        i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
        if(i32FractionPart < 0)
        {
            i32FractionPart *= -1;
        }

        // Escreve a pressão na tela
        UARTprintf("Pressão %3d.%03d\t\t", i32IntegerPart, i32FractionPart);

        // Calculo da altitude a partir da pressão encontrada
        fAltitude = 44330.0f * (1.0f - powf(fPressure / 101325.0f,
                                            1.0f / 5.255f));

        // Manipulação dos dados de altitude em float para que fique melhor impresso
        i32IntegerPart = (int32_t) fAltitude;
        i32FractionPart =(int32_t) (fAltitude * 1000.0f);
        i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
        if(i32FractionPart < 0)
        {
            i32FractionPart *= -1;
        }

        // Escreve a altitude na tela
        UARTprintf("Altitude %3d.%03d", i32IntegerPart, i32FractionPart);

        // Quebra de linha
        UARTprintf("\n");

        // Delay para continuar imprimindo os dados a uma boa velocidade 100 mili
        MAP_SysCtlDelay(MAP_SysCtlClockGet() / (10 * 3));

    }
}
