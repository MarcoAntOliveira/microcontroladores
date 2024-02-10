/*
 * Nokia_5110.h
 *
 *  Created on: 25/06/2015
 *      Author: Thiago
 */
#ifndef NOKIA_5110_H_
#define NOKIA_5110_H_
#include <stdint.h>

/* *************************** Pinagem | Pinou***************************
// Red SparkFun Nokia 5110 (LCD-10168)
-----------------------------------
Signal        (Nokia 5110) LaunchPad pin
3.3V          (VCC, pin 1) power
Ground        (GND, pin 2) ground
SSI0Fss       (SCE, pin 3) connected to PA3
Reset         (RST, pin 4) connected to PA7
Data/Command  (D/C, pin 5) connected to PA6
SSI0Tx        (DN,  pin 6) connected to PA5
SSI0Clk       (SCLK, pin 7) connected to PA2
 */

/*
SYSDIV2  Divisor  Clock (MHz)
 0        1       reserved
 1        2       reserved
 2        3       reserved
 3        4       reserved
 4        5       80.000
 5        6       66.667
 6        7       reserved
 7        8       50.000
 8        9       44.444
 9        10      40.000
 10       11      36.364
 11       12      33.333
 12       13      30.769
 13       14      28.571
 14       15      26.667
 15       16      25.000
 16       17      23.529
 17       18      22.222
 18       19      21.053
 19       20      20.000
 20       21      19.048
 21       22      18.182
 22       23      17.391
 23       24      16.667
 24       25      16.000
 25       26      15.385
 26       27      14.815
 27       28      14.286
 28       29      13.793
 29       30      13.333
 30       31      12.903
 31       32      12.500
 32       33      12.121
 33       34      11.765
 34       35      11.429
 35       36      11.111
 36       37      10.811
 37       38      10.526
 38       39      10.256
 39       40      10.000
 40       41      9.756
 41       42      9.524
 42       43      9.302
 43       44      9.091
 44       45      8.889
 45       46      8.696
 46       47      8.511
 47       48      8.333
 48       49      8.163
 49       50      8.000
 50       51      7.843
 51       52      7.692
 52       53      7.547
 53       54      7.407
 54       55      7.273
 55       56      7.143
 56       57      7.018
 57       58      6.897
 58       59      6.780
 59       60      6.667
 60       61      6.557
 61       62      6.452
 62       63      6.349
 63       64      6.250
 64       65      6.154
 65       66      6.061
 66       67      5.970
 67       68      5.882
 68       69      5.797
 69       70      5.714
 70       71      5.634
 71       72      5.556
 72       73      5.479
 73       74      5.405
 74       75      5.333
 75       76      5.263
 76       77      5.195
 77       78      5.128
 78       79      5.063
 79       80      5.000
 80       81      4.938
 81       82      4.878
 82       83      4.819
 83       84      4.762
 84       85      4.706
 85       86      4.651
 86       87      4.598
 87       88      4.545
 88       89      4.494
 89       90      4.444
 90       91      4.396
 91       92      4.348
 92       93      4.301
 93       94      4.255
 94       95      4.211
 95       96      4.167
 96       97      4.124
 97       98      4.082
 98       99      4.040
 99       100     4.000
 100      101     3.960
 101      102     3.922
 102      103     3.883
 103      104     3.846
 104      105     3.810
 105      106     3.774
 106      107     3.738
 107      108     3.704
 108      109     3.670
 109      110     3.636
 110      111     3.604
 111      112     3.571
 112      113     3.540
 113      114     3.509
 114      115     3.478
 115      116     3.448
 116      117     3.419
 117      118     3.390
 118      119     3.361
 119      120     3.333
 120      121     3.306
 121      122     3.279
 122      123     3.252
 123      124     3.226
 124      125     3.200
 125      126     3.175
 126      127     3.150
 127      128     3.125
 */

// *************************** Enumerações, Constantes e Variáveis | ENUMS, CONSTANTS AND VARIABLES***************************
enum typeOfWrite{
    COMMAND,                              // the transmission is an LCD command
    DATA                                  // the transmission is data
};

 // This table contains the hex values that represent pixels
 // for a font that is 5 pixels wide and 8 pixels high
 static const uint8_t ASCII[][5] = {
         {0x00, 0x00, 0x00, 0x00, 0x00} // 20
         ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
         ,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
         ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
         ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
         ,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
         ,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
         ,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
         ,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
         ,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
         ,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
         ,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
         ,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
         ,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
         ,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
         ,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
         ,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
         ,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
         ,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
         ,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
         ,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
         ,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
         ,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
         ,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
         ,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
         ,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
         ,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
         ,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
         ,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
         ,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
         ,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
         ,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
         ,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
         ,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
         ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
         ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
         ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
         ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
         ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
         ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
         ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
         ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
         ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
         ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
         ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
         ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
         ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
         ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
         ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
         ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
         ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
         ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
         ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
         ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
         ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
         ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
         ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
         ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
         ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
         ,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
         ,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c '\'
         ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
         ,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
         ,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
         ,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
         ,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
         ,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
         ,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
         ,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
         ,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
         ,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
         ,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
         ,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
         ,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
         ,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
         ,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
         ,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
         ,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
         ,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
         ,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
         ,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
         ,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
         ,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
         ,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
         ,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
         ,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
         ,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
         ,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
         ,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
         ,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
         ,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
         ,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
         ,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
         ,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
         ,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ~
         //  ,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f DEL
         ,{0x1f, 0x24, 0x7c, 0x24, 0x1f} // 7f UT sign
 };

// *************************** Tamanho da tela | WINDOWS SIZE ***************************
#define SCREENW     84
#define SCREENH     48
// *************************** Definições | DEFINES ***************************
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

// *************************** Definições Nokia5110.h | MORE DEFINES ***************************
#define MAX_X                   84
#define MAX_Y                   48
#define CONTRAST                0xBF//0xB1

// *************************** Definições PLL | DEFINES PLL ***************************
#define SYSCTL_RIS_R            (*((volatile uint32_t *)0x400FE050))
#define SYSCTL_RIS_PLLLRIS      0x00000040  // PLL Lock Raw Interrupt Status
#define SYSCTL_RCC_R            (*((volatile uint32_t *)0x400FE060))
#define SYSCTL_RCC_XTAL_M       0x000007C0  // Crystal Value
#define SYSCTL_RCC_XTAL_6MHZ    0x000002C0  // 6 MHz Crystal
#define SYSCTL_RCC_XTAL_8MHZ    0x00000380  // 8 MHz Crystal
#define SYSCTL_RCC_XTAL_16MHZ   0x00000540  // 16 MHz Crystal
#define SYSCTL_RCC2_R           (*((volatile uint32_t *)0x400FE070))
#define SYSCTL_RCC2_USERCC2     0x80000000  // Use RCC2
#define SYSCTL_RCC2_DIV400      0x40000000  // Divide PLL as 400 MHz vs. 200
// MHz
#define SYSCTL_RCC2_SYSDIV2_M   0x1F800000  // System Clock Divisor 2
#define SYSCTL_RCC2_SYSDIV2LSB  0x00400000  // Additional LSB for SYSDIV2
#define SYSCTL_RCC2_PWRDN2      0x00002000  // Power-Down PLL 2
#define SYSCTL_RCC2_BYPASS2     0x00000800  // PLL Bypass 2
#define SYSCTL_RCC2_OSCSRC2_M   0x00000070  // Oscillator Source 2
#define SYSCTL_RCC2_OSCSRC2_MO  0x00000000  // MOSC

#define SYSDIV2 7
// *************************** Definições usadas no Exemplo ***************************
#define PIN_SCE   7 //Pin 3 on LCD
#define PIN_RESET 6 //Pin 4 on LCD
#define PIN_DC    5 //Pin 5 on LCD
#define PIN_SDIN  4 //Pin 6 on LCD
#define PIN_SCLK  3 //Pin 7 on LCD

//The DC pin tells the LCD if we are sending a command or data
#define LCD_COMMAND 0
#define LCD_DATA  1

//You may find a different size screen, but this one is 84 by 48 pixels
#define LCD_X     84
#define LCD_Y     48



// *************************** Protótipos Funções ***************************

void static lcdwrite(enum typeOfWrite type, uint8_t message);
void static lcddatawrite(uint8_t data);
void Nokia5110_Init(void); //inicializa as portas necessarias para o display de LCD Nokia 5110
void Nokia5110_OutChar(char data);
void Nokia5110_OutString(char *ptr);
void Nokia5110_OutUDec(uint16_t n);
void Nokia5110_SetCursor(uint8_t newX, uint8_t newY);
void Nokia5110_Clear(void);
void Nokia5110_DrawFullImage(const uint8_t *ptr);
void Nokia5110_PrintBMP(uint8_t xpos, uint8_t ypos, const uint8_t *ptr, uint8_t threshold);
void Nokia5110_ClearBuffer(void);
void Nokia5110_DisplayBuffer(void);
void Nokia5110_ClrPxl(uint32_t i, uint32_t j);
void Nokia5110_SetPxl(uint32_t i, uint32_t j);
void PLL_Init(void);
void Nokia5110_Out_IMAGEM(void);
void Nokia5110_OutSprite();
void Nokia5110_SetSpritePos(uint8_t newX, uint8_t newY);
#endif /* NOKIA_5110_H_ */
