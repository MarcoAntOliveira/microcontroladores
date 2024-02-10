#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "utils/uartstdio.h"
#include "utils/cmdline.h"
//funções da lista de comandos

int Cmd_Help(int argc, char *argv[]){
    tCmdLineEntry *psEntry;
    UARTprintf("\nComandos Disponiveis\n");
    UARTprintf("------------------------\n");

    psEntry = &g_psCmdTable[0];

    while(psEntry -> pcCmd)
    {
        UARTprintf("%6s: %s\n", psEntry -> pcCmd, psEntry ->pcHelp);
        psEntry++;
    }

 return(0);
}
int Cmd_Oi(int argc, char*argv[])
{
    UARTprintf("\nOi\n");
    return(0);
}

int Cmd_Tchau(int argc, char *argv[])
{
    UARTprintf("\nTchau\n");
    return(0);
}

int Cmd_Espere(int argc , char *argv[]){
    UARTprintf("\nEspere\n");
    return(0);
}

int Cmd_Soma(int argc, char *argv[]){
    int quant = argc - 1;
    int i ;
    int val[5] = {0, 0, 0, 0, 0};
    int soma = 0;

    if (quant > 5){
        return CMDLINE_TOO_MANY_ARGS;
    }
        for(i = 0; i <quant; i++){
            val[i]= atoi(argv[i+1]);
            soma += val[i];
        }
  UARTprintf("\nSoma = %d\n", soma);
  return(0);

}

void ConfigureUART(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    GPIOPinConfigure(GPIO_PAO_U0RX);
    GPIOPinConfigure(GPIO_PAO_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);
}

tCmdLineEntry g_psCmdTable [] =
{
  {"help",  Cmd_Help,  "Mostra a lista de comandos"},
  {"oi",     Cmd_Oi,     "Mostra um oi "},
  {"tchau", Cmd_Tchau,    "Mostra um tchau"},
  {"espere",  Cmd_Espere,  "Mostra um Espere"},
 // {"fica",  Cmd_Fica,  "sinonimo para  espere"},
  //{"some",  Cmd_tchau, "sinonimo para tchau"},
  {"soma",  Cmd_Soma,   "soma os valores informados"},
  {0, 0, 0}
};

int main(){
    char g_pcCmdBuf[64];
    int nStatus;
    ConfigureUART();

    UARTprintf("\n\nExemplo de uso biblioteca cmdline\n");
    UARTprintf("Digite \'help\' para ajuda.\n");

    while(1)
    {
        UARTprintf("\n>");
        UARTgets(g_pcCmdBuf, sizeof(g_pcCmdBuf));

        nStatus = CmdLineProcess(g_pcCmdBuf);

        if(nStatus == CMDLINE_BAD_CMD)
        {
            UARTprintf("\nComando Invalido\n");

        }
        else if (nStatus == CMDLINE_TOO_MANY_ARGS)
        {
            UARTprintf("\nMuitos argumentos para o processador\n");

        }
        else if (nStatus == CMDLINE_TOO_FEW_ARGS){
            UARTprintf("\n falta de argumentos para o processador\n");
        }
        else if(nStatus == CMDLINE_INVALID_ARG){
            UARTprintf("\nFalha por argumentos invalidos! \n");
        }
        else if (nStatus != 0){
            UARTprintf("comado retornou codigo de erro %d./n", nStatus);
        }
    }
}
