
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/rom.h"
#include "driverlib/lcd.h"
#include "driverlib/ssi.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

enum typeOfWrite{
COMMAND, // the transmission is an LCD command
DATA // the transmission is data
};

#define CONTRAST        0xB1
#define MAX_X           84
#define MAX_Y           48
#define SCREENW         84
#define SCREENH         48


#define SCREENW     84
#define SCREENH     48

#define DC                      (*((volatile uint32_t *)0x40004100))
#define DC_COMMAND              0
#define DC_DATA                 0x40
#define RESET                   (*((volatile uint32_t *)0x40004200))
#define RESET_LOW               0
#define RESET_HIGH              0x80
#define GPIO_PORTA_DIR_R        (*((volatile uint32_t *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile uint32_t *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile uint32_t *)0x4000451C))
#define GPIO_PORTA_AMSEL_R      (*((volatile uint32_t *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile uint32_t *)0x4000452C))
#define SSI0_CR0_R              (*((volatile uint32_t *)0x40008000))
#define SSI0_CR1_R              (*((volatile uint32_t *)0x40008004))
#define SSI0_DR_R               (*((volatile uint32_t *)0x40008008))
#define SSI0_SR_R               (*((volatile uint32_t *)0x4000800C))
#define SSI0_CPSR_R             (*((volatile uint32_t *)0x40008010))
#define SSI0_CC_R               (*((volatile uint32_t *)0x40008FC8))
#define SSI_CR0_SCR_M           0x0000FF00  // SSI Serial Clock Rate
#define SSI_CR0_SPH             0x00000080  // SSI Serial Clock Phase
#define SSI_CR0_SPO             0x00000040  // SSI Serial Clock Polarity
#define SSI_CR0_FRF_M           0x00000030  // SSI Frame Format Select
#define SSI_CR0_FRF_MOTO        0x00000000  // Freescale SPI Frame Format
#define SSI_CR0_DSS_M           0x0000000F  // SSI Data Size Select
#define SSI_CR0_DSS_8           0x00000007  // 8-bit data
#define SSI_CR1_MS              0x00000004  // SSI Master/Slave Select
#define SSI_CR1_SSE             0x00000002  // SSI Synchronous Serial Port
                                            // Enable
#define SSI_SR_BSY              0x00000010  // SSI Busy Bit
#define SSI_SR_TNF              0x00000002  // SSI Transmit FIFO Not Full
#define SSI_CPSR_CPSDVSR_M      0x000000FF  // SSI Clock Prescale Divisor
#define SSI_CC_CS_M             0x0000000F  // SSI Baud Clock Source
#define SSI_CC_CS_SYSPLL        0x00000000  // Either the system clock (if the
                                            // PLL bypass is in effect) or the
                                            // PLL output (default)
#define SYSCTL_RCGC1_R          (*((volatile uint32_t *)0x400FE104))
#define SYSCTL_RCGC2_R          (*((volatile uint32_t *)0x400FE108))
#define SYSCTL_RCGC1_SSI0       0x00000010  // SSI0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOA      0x00000001  // port A Clock Gating Control


#define SSI1_CR0_R      (*((volatile uint32_t *)0x40009000))
#define SSI1_CR1_R      (*((volatile uint32_t *)0x40009004))
#define SSI1_DR_R       (*((volatile uint32_t *)0x40009008))
#define SSI1_SR_R       (*((volatile uint32_t *)0x4000900C))
#define SSI1_CPSR_R     (*((volatile uint32_t *)0x40009010))
#define SSI1_CC_R       (*((volatile uint32_t *)0x40009FC8))
#define SSI_SR_BSY      0x00000010 // SSI Busy Bit
#define SSI_SR_TNF      0x00000002 // SSI Transmit FIFO Not Full

void static         lcdwrite                    (enum typeOfWrite type, uint8_t message);
void static         lcddatawrite                (uint8_t data);
void                Nokia5110_Init              (void);
void                Nokia5110_OutChar           (char data);
void                Nokia5110_OutCharInv        (char data);
void                Nokia5110_OutString         (char *ptr);
void                Nokia5110_OutStringInv      (char *ptr);
void                Nokia5110_OutUDec           (uint16_t n);
void                Nokia5110_OutSpecial        (uint16_t code);
void                Nokia5110_DrawChar          (char data);
void                Nokia5110_DrawSpecial       (uint16_t code);
void                Nokia5110_DrawMix           (uint8_t code1, uint8_t code2, uint8_t code3, uint8_t code4);
void                Nokia5110_Padding           (void);
void                Nokia5110_SetCursor         (uint8_t newX, uint8_t newY);
void                Nokia5110_Clear             (void);
void                Nokia5110_DrawFullImage     (const uint8_t *ptr);
void                Nokia5110_PrintBMP          (uint8_t xpos, uint8_t ypos, const uint8_t *ptr, uint8_t threshold);
void                Nokia5110_ClearBuffer       (void);
void                Nokia5110_DisplayBuffer     (void);
void                Nokia5110_ClrPxl            (uint32_t i, uint32_t j);
void                Nokia5110_SetPxl            (uint32_t i, uint32_t j);

#endif
