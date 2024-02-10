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
#include "functions_matriz.h"
#include "Nokia5110.h"
#include "frames_tela_inicial.h"
#include "Selecao_Menu.h"

int selection_menu = 0;
int main(void)
{
    volatile uint32_t ui32Loop;

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);//habilitita a frequencia do tiva para 40Mhz

    // Blue Nokia 5110
    // ---------------
    // Signal        (Nokia 5110) LaunchPad pin
    // Reset         (RST, pin 1) connected to PA7
    // SSI0Fss       (CE,  pin 2) connected to PA3
    // Data/Command  (DC,  pin 3) connected to PA6
    // SSI0Tx        (Din, pin 4) connected to PA5
    // SSI0Clk       (Clk, pin 5) connected to PA2
    // 3.3V          (Vcc, pin 6) power
    // back light    (BL,  pin 7) not connected
    // Ground        (Gnd, pin 8) ground

    //Inicializa a tela
    Nokia5110_Init();
    Nokia5110_Clear();

    //codigos linha para uso do timer 0
    uint32_t ui32Period;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    ui32Period = SysCtlClockGet()/2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
    TimerEnable(TIMER0_BASE, TIMER_A);

    //codigos linha para uso do timer 1
    uint32_t ui32Period3;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    ui32Period3 = SysCtlClockGet();
    TimerLoadSet(TIMER1_BASE, TIMER_A, ui32Period3 -1);
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
    TimerEnable(TIMER1_BASE, TIMER_A);

    //pag 118 workbook
    //codigos linha para uso do sensor do tiva
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//Habilita o portal F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//Habilita o portal A para o display Nokia
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//Habilita o portal B

    //desbloquear SW2
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);

    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_5);
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_5, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);

    //tela inicial
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_SetCursor(0,0);
    ImprimeImagem();
    SysCtlDelay( 40000000 );

    Nokia5110_Clear();
    Nokia5110_ClearBuffer();

    //para coletar temperatura do tiva, que sera usada como semente
    ADCIntClear(ADC0_BASE, 1);
    ADCProcessorTrigger(ADC0_BASE, 1);
    while(!ADCIntStatus(ADC0_BASE, 1, false))
    {
    }
    ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
    ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
    ui32TempAvg2 = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4; //item 2 da tarefa
    ui32TempValueC = (1475. - ((2475. * ((double)(ui32TempAvg+ui32TempAvg2)/2.))) / 4096.)/10.;

    srand( (unsigned)ui32TempValueC );

    while(1)
    {
        selection_menu = Select( selection_menu );
    }
}
