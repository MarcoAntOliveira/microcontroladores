#include "Nokia5110.h"
//#include "Symbols.h"


uint8_t Screen[SCREENW * SCREENH / 8]; // Buffer stores the next image to be printed on the screen
const unsigned char Masks[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}; // Utilizado na fun��o Nokia5110_ClrPxl


// ================== PRIVATE FUNCTIONS ==================


// The Data/Command pin must be valid when the eighth bit is
// sent. The SSI module has hardware input and output FIFOs
// that are 8 locations deep. Based on the observation that
// the LCD interface tends to send a few commands and then a
// lot of data, the FIFOs are not used when writing
// commands, and they are used when writing data.  This
// ensures that the Data/Command pin status matches the byte
// that is actually being transmitted.
// The write command operation waits until all data has been
// sent, configures the Data/Command pin for commands, sends
// the command, and then waits for the transmission to
// finish.
// The write data operation waits until there is room in the
// transmit FIFO, configures the Data/Command pin for data,
// and then adds the data to the transmit FIFO.
// This is a helper function that sends an 8-bit message to the LCD.
// Inputs: type: COMMAND or DATA and message 8-bit code to transmit
// Assumes: SSI0 and port A have already been initialized and enabled

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
        ,{0x00, 0x06, 0x09, 0x09, 0x06} // 80 celcius
};


static const uint8_t SPECIAL_SIMBOLS[][5] = {
        {0xff, 0xff, 0xff, 0xff, 0xff}
};


static const uint8_t MIX_SIMBOLS[][2] = {
         {0x0, 0x0} // Blank square
        ,{0x3, 0x3} // Black square
        ,{0x2, 0x1}
        ,{0x1, 0x2}
        ,{0x3, 0x0}
        ,{0x0, 0x3}
};


void static lcdwrite(enum typeOfWrite type, uint8_t message)
{
    if(type == COMMAND)
    {
        // Wait until SSI0 not busy/tr/*
        * Nokia_5110.c
        *
        *  Created on: 25/06/2015
        *      Author: Thiago
        */

       #include <stdint.h>
       #include <stdbool.h>
       #include "inc/hw_memmap.h"
       #include "inc/hw_ssi.h"
       #include "inc/hw_types.h"
       #include "driverlib/ssi.h"
       #include "driverlib/gpio.h"
       #include "driverlib/pin_map.h"
       #include "driverlib/sysctl.h"

       #include "Nokia5110.h"

       uint8_t Screen[SCREENW*SCREENH/8]; // buffer stores the next image to be printed on the screen
       const unsigned char Masks[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //usado na fun��o Nokia5110_ClrPxl

       // *************************** Implementa��o Fun��es | Implementation of functions ***************************
       // The Data/Command pin must be valid when the eighth bit is
       // sent.  The SSI module has hardware input and output FIFOs
       // that are 8 locations deep.  Based on the observation that
       // the LCD interface tends to send a few commands and then a
       // lot of data, the FIFOs are not used when writing
       // commands, and they are used when writing data.  This
       // ensures that the Data/Command pin status matches the byte
       // that is actually being transmitted.
       // The write command operation waits until all data has been
       // sent, configures the Data/Command pin for commands, sends
       // the command, and then waits for the transmission to
       // finish.
       // The write data operation waits until there is room in the
       // transmit FIFO, configures the Data/Command pin for data,
       // and then adds the data to the transmit FIFO.

       // This is a helper function that sends an 8-bit message to the LCD.
       // inputs: type     COMMAND or DATA
       //         message  8-bit code to transmit
       // outputs: none
       // assumes: SSI0 and port A have already been initialized and enabled
       void static lcdwrite(enum typeOfWrite type, uint8_t message){
           if(type == COMMAND){
               // wait until SSI0 not busy/transmit FIFO empty
               while((SSI0_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};
               //DC = DC_COMMAND;
               GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
               SSI0_DR_R = message;                // command out
               // wait until SSI0 not busy/transmit FIFO empty
               while((SSI0_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};

           } else{
               while((SSI0_SR_R&SSI_SR_TNF)==0){}; // wait until transmit FIFO not full
               //DC = DC_DATA;
               GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);
               SSI0_DR_R = message;                // data out
           }
           //GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0);
       }
       void static lcddatawrite(uint8_t data){
           while((SSI0_SR_R&0x00000002)==0){}; // wait until transmit FIFO not full
           DC = DC_DATA;
           GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);
           SSI0_DR_R = data;                // data out
       }

       //********Nokia5110_Init*****************
       // Initialize Nokia 5110 48x84 LCD by sending the proper
       // commands to the PCD8544 driver.  One new feature of the
       // LM4F120 is that its SSIs can get their baud clock from
       // either the system clock or from the 16 MHz precision
       // internal oscillator.
       // inputs: none
       // outputs: none
       // assumes: system clock rate of 80 MHz
       void Nokia5110_Init(void){
           volatile uint32_t delay;
           SYSCTL_RCGC1_R |= SYSCTL_RCGC1_SSI0;  // activate SSI0
           SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
           delay = SYSCTL_RCGC2_R;               // allow time to finish activating
           GPIO_PORTA_DIR_R |= 0xC0;             // make PA6,7 out
           GPIO_PORTA_AFSEL_R |= 0x2C;           // enable alt funct on PA2,3,5
           GPIO_PORTA_AFSEL_R &= ~0xC0;          // disable alt funct on PA6,7
           GPIO_PORTA_DEN_R |= 0xEC;             // enable digital I/O on PA2,3,5,6,7
           // configure PA2,3,5 as SSI
           GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFF0F00FF)+0x00202200;
           // configure PA6,7 as GPIO
           GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0x00FFFFFF)+0x00000000;
           GPIO_PORTA_AMSEL_R &= ~0xEC;          // disable analog functionality on PA2,3,5,6,7
           SSI0_CR1_R &= ~SSI_CR1_SSE;           // disable SSI
           SSI0_CR1_R &= ~SSI_CR1_MS;            // master mode
           // configure for system clock/PLL baud clock source
           SSI0_CC_R = (SSI0_CC_R&~SSI_CC_CS_M)+SSI_CC_CS_SYSPLL;
           // clock divider for 3.33 MHz SSIClk (80 MHz PLL/24)
           // SysClk/(CPSDVSR*(1+SCR))
           // 80/(24*(1+0)) = 3.33 MHz (slower than 4 MHz)
           SSI0_CPSR_R = (SSI0_CPSR_R&~SSI_CPSR_CPSDVSR_M)+24; // must be even number
           SSI0_CR0_R &= ~(SSI_CR0_SCR_M |       // SCR = 0 (3.33 Mbps data rate)
                   SSI_CR0_SPH |         // SPH = 0
                   SSI_CR0_SPO);         // SPO = 0
           // FRF = Freescale format
           SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;
           // DSS = 8-bit data
           SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8;
           SSI0_CR1_R |= SSI_CR1_SSE;            // enable SSI

           /*SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
           SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
           GPIOPinConfigure(GPIO_PA2_SSI0CLK);
           GPIOPinConfigure(GPIO_PA3_SSI0FSS);
           GPIOPinConfigure(GPIO_PA5_SSI0TX);
           GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_2);
           SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet()/24, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 10000, 16);
           SSIEnable(SSI0_BASE);*/

           SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
           GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1);

           RESET = RESET_LOW;                    // reset the LCD to a known state
           for(delay=0; delay<10; delay=delay+1);// delay minimum 100 ns
           RESET = RESET_HIGH;                   // negative logic

           lcdwrite(COMMAND, 0x21);              // chip active; horizontal addressing mode (V = 0); use extended instruction set (H = 1)
           // set LCD Vop (contrast), which may require some tweaking:
           lcdwrite(COMMAND, CONTRAST);          // try 0xB1 (for 3.3V red SparkFun), 0xB8 (for 3.3V blue SparkFun), 0xBF if your display is too dark, or 0x80 to 0xFF if experimenting
           lcdwrite(COMMAND, 0x04);              // set temp coefficient
           lcdwrite(COMMAND, 0x14);              // LCD bias mode 1:48: try 0x13 or 0x14

           lcdwrite(COMMAND, 0x20);              // we must send 0x20 before modifying the display control mode
           lcdwrite(COMMAND, 0x0C);              // set display control to normal mode: 0x0D for inverse
       }

       //********Nokia5110_OutChar*****************
       // Print a character to the Nokia 5110 48x84 LCD.  The
       // character will be printed at the current cursor position,
       // the cursor will automatically be updated, and it will
       // wrap to the next row or back to the top if necessary.
       // One blank column of pixels will be printed on either side
       // of the character for readability.  Since characters are 8
       // pixels tall and 5 pixels wide, 12 characters fit per row,
       // and there are six rows.
       // inputs: data  character to print
       // outputs: none
       // assumes: LCD is in default horizontal addressing mode (V = 0)
       void Nokia5110_OutChar(char data){
           int i;
           lcddatawrite(0x00);        // blank vertical line padding
           for(i=0; i<5; i=i+1){
               lcddatawrite(ASCII[data - 0x20][i]);
           }
           lcddatawrite(0x00);        // blank vertical line padding
       }


       void Nokia5110_OutSprite(const uint8_t *data){
           int i;
           lcddatawrite(0x00);        // blank vertical line padding
           for(i=0; i<9; i=i+1){
               lcddatawrite(data[i]);
           }
           lcddatawrite(0x00);        // blank vertical line padding
       }

       void Nokia5110_SetSpritePos(uint8_t newX, uint8_t newY){
           if((newX > 11) || (newY > 5)){        // bad input
               return;                             // do nothing
           }
           // multiply newX by 7 because each character is 7 columns wide
           lcdwrite(COMMAND, 0x80|(newX*8));     // setting bit 7 updates X-position
           lcdwrite(COMMAND, 0x40|newY);         // setting bit 6 updates Y-position
       }


       //********Nokia5110_OutString*****************
       // Print a string of characters to the Nokia 5110 48x84 LCD.
       // The string will automatically wrap, so padding spaces may
       // be needed to make the output look optimal.
       // inputs: ptr  pointer to NULL-terminated ASCII string
       // outputs: none
       // assumes: LCD is in default horizontal addressing mode (V = 0)
       void Nokia5110_OutString(char *ptr){
           while(*ptr){
               Nokia5110_OutChar((unsigned char)*ptr);
               ptr = ptr + 1;
           }
       }

       //********Nokia5110_OutUDec*****************
       // Output a 16-bit number in unsigned decimal format with a
       // fixed size of five right-justified digits of output.
       // Inputs: n  16-bit unsigned number
       // Outputs: none
       // assumes: LCD is in default horizontal addressing mode (V = 0)
       void Nokia5110_OutUDec(uint16_t n){
           if(n < 10){
               Nokia5110_OutString("    ");
               Nokia5110_OutChar(n+'0'); /* n is between 0 and 9 */
           } else if(n<100){
               Nokia5110_OutString("   ");
               Nokia5110_OutChar(n/10+'0'); /* tens digit */
               Nokia5110_OutChar(n%10+'0'); /* ones digit */
           } else if(n<1000){
               Nokia5110_OutString("  ");
               Nokia5110_OutChar(n/100+'0'); /* hundreds digit */
               n = n%100;
               Nokia5110_OutChar(n/10+'0'); /* tens digit */
               Nokia5110_OutChar(n%10+'0'); /* ones digit */
           }
           else if(n<10000){
               Nokia5110_OutChar(' ');
               Nokia5110_OutChar(n/1000+'0'); /* thousands digit */
               n = n%1000;
               Nokia5110_OutChar(n/100+'0'); /* hundreds digit */
               n = n%100;
               Nokia5110_OutChar(n/10+'0'); /* tens digit */
               Nokia5110_OutChar(n%10+'0'); /* ones digit */
           }
           else {
               Nokia5110_OutChar(n/10000+'0'); /* ten-thousands digit */
               n = n%10000;
               Nokia5110_OutChar(n/1000+'0'); /* thousands digit */
               n = n%1000;
               Nokia5110_OutChar(n/100+'0'); /* hundreds digit */
               n = n%100;
               Nokia5110_OutChar(n/10+'0'); /* tens digit */
               Nokia5110_OutChar(n%10+'0'); /* ones digit */
           }
       }

       void Nokia5110_Out_IMAGEM(){
           int i;
           lcddatawrite(0x00);        // blank vertical line padding
           for(i=0; i<48; i=i+1){
               lcddatawrite(RODA[1][i]);
           }
           lcddatawrite(0x00);        // blank vertical line padding
       }

       //********Nokia5110_SetCursor*****************
       // Move the cursor to the desired X- and Y-position.  The
       // next character will be printed here.  X=0 is the leftmost
       // column.  Y=0 is the top row.
       // inputs: newX  new X-position of the cursor (0<=newX<=11)
       //         newY  new Y-position of the cursor (0<=newY<=5)
       // outputs: none
       void Nokia5110_SetCursor(uint8_t newX, uint8_t newY){
           if((newX > 11) || (newY > 5)){        // bad input
               return;                             // do nothing
           }
           // multiply newX by 7 because each character is 7 columns wide
           lcdwrite(COMMAND, 0x80|(newX*7));     // setting bit 7 updates X-position
           lcdwrite(COMMAND, 0x40|newY);         // setting bit 6 updates Y-position
       }

       //********Nokia5110_Clear*****************
       // Clear the LCD by writing zeros to the entire screen and
       // reset the cursor to (0,0) (top left corner of screen).
       // inputs: none
       // outputs: none
       void Nokia5110_Clear(void){
           int i;
           for(i=0; i<(MAX_X*MAX_Y/8); i=i+1){
               lcddatawrite(0x00);
           }
           Nokia5110_SetCursor(0, 0);
       }

       //********Nokia5110_DrawFullImage*****************
       // Fill the whole screen by drawing a 48x84 bitmap image.
       // inputs: ptr  pointer to 504 byte bitmap
       // outputs: none
       // assumes: LCD is in default horizontal addressing mode (V = 0)
       void Nokia5110_DrawFullImage(const uint8_t *ptr){
           int i;
           Nokia5110_SetCursor(0, 0);
           for(i=0; i<(MAX_X*MAX_Y/8); i=i+1){
               lcddatawrite(ptr[i]);
           }
       }

       uint8_t Screen[SCREENW*SCREENH/8]; // buffer stores the next image to be printed on the screen

       //********Nokia5110_PrintBMP*****************
       // Bitmaps defined above were created for the LM3S1968 or
       // LM3S8962's 4-bit grayscale OLED display.  They also
       // still contain their header data and may contain padding
       // to preserve 4-byte alignment.  This function takes a
       // bitmap in the previously described format and puts its
       // image data in the proper location in the buffer so the
       // image will appear on the screen after the next call to
       //   Nokia5110_DisplayBuffer();
       // The interface and operation of this process is modeled
       // after RIT128x96x4_BMP(x, y, image);
       // inputs: xpos      horizontal position of bottom left corner of image, columns from the left edge
       //                     must be less than 84
       //                     0 is on the left; 82 is near the right
       //         ypos      vertical position of bottom left corner of image, rows from the top edge
       //                     must be less than 48
       //                     2 is near the top; 47 is at the bottom
       //         ptr       pointer to a 16 color BMP image
       //         threshold grayscale colors above this number make corresponding pixel 'on'
       //                     0 to 14
       //                     0 is fine for ships, explosions, projectiles, and bunkers
       // outputs: none
       void Nokia5110_PrintBMP(uint8_t xpos, uint8_t ypos, const uint8_t *ptr, uint8_t threshold){
           int32_t width = ptr[18], height = ptr[22], i, j;
           uint16_t screenx, screeny;
           uint8_t mask;
           // check for clipping
           if((height <= 0) ||              // bitmap is unexpectedly encoded in top-to-bottom pixel order
                   ((width%2) != 0) ||           // must be even number of columns
                   ((xpos + width) > SCREENW) || // right side cut off
                   (ypos < (height - 1)) ||      // top cut off
                   (ypos > SCREENH))           { // bottom cut off
               return;
           }
           if(threshold > 14){
               threshold = 14;             // only full 'on' turns pixel on
           }
           // bitmaps are encoded backwards, so start at the bottom left corner of the image
           screeny = ypos/8;
           screenx = xpos + SCREENW*screeny;
           mask = ypos%8;                // row 0 to 7
           mask = 0x01<<mask;            // now stores a mask 0x01 to 0x80
           j = ptr[10];                  // byte 10 contains the offset where image data can be found
           for(i=1; i<=(width*height/2); i=i+1){
               // the left pixel is in the upper 4 bits
               if(((ptr[j]>>4)&0xF) > threshold){
                   Screen[screenx] |= mask;
               } else{
                   Screen[screenx] &= ~mask;
               }
               screenx = screenx + 1;
               // the right pixel is in the lower 4 bits
               if((ptr[j]&0xF) > threshold){
                   Screen[screenx] |= mask;
               } else{
                   Screen[screenx] &= ~mask;
               }
               screenx = screenx + 1;
               j = j + 1;
               if((i%(width/2)) == 0){     // at the end of a row
                   if(mask > 0x01){
                       mask = mask>>1;
                   } else{
                       mask = 0x80;
                       screeny = screeny - 1;
                   }
                   screenx = xpos + SCREENW*screeny;
                   // bitmaps are 32-bit word aligned
                   switch((width/2)%4){      // skip any padding
                   case 0: j = j + 0; break;
                   case 1: j = j + 3; break;
                   case 2: j = j + 2; break;
                   case 3: j = j + 1; break;
                   }
               }
           }
       }
       // There is a buffer in RAM that holds one screen
       // This routine clears this buffer
       void Nokia5110_ClearBuffer(void){int i;
       for(i=0; i<SCREENW*SCREENH/8; i=i+1){
           Screen[i] = 0;              // clear buffer
       }
       }

       //********Nokia5110_DisplayBuffer*****************
       // Fill the whole screen by drawing a 48x84 screen image.
       // inputs: none
       // outputs: none
       // assumes: LCD is in default horizontal addressing mode (V = 0)
       void Nokia5110_DisplayBuffer(void){
           Nokia5110_DrawFullImage(Screen);
       }

       //------------Nokia5110_ClrPxl------------
       // Clear the Image pixel at (i, j), turning it dark.
       // Input: i  the row index  (0 to 47 in this case),    y-coordinate
       //        j  the column index  (0 to 83 in this case), x-coordinate
       // Output: none
       void Nokia5110_ClrPxl(uint32_t i, uint32_t j){
           Screen[84*(i>>3) + j] &= ~Masks[i&0x07];
       }
       //------------Nokia5110_SetPxl------------
       // Set the Image pixel at (i, j), turning it on.
       // Input: i  the row index  (0 to 47 in this case),    y-coordinate
       //        j  the column index  (0 to 83 in this case), x-coordinate
       // Output: none
       void Nokia5110_SetPxl(uint32_t i, uint32_t j){
           Screen[84*(i>>3) + j] |= Masks[i&0x07];
       }

       // configure the system to get its clock from the PLL
       void PLL_Init(void){
           // 0) configure the system to use RCC2 for advanced features
           //    such as 400 MHz PLL and non-integer System Clock Divisor
           SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
           // 1) bypass PLL while initializing
           SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
           // 2) select the crystal value and oscillator source
           SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL field
           SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// configure for 16 MHz crystal
           SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source field
           SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// configure for main oscillator source
           // 3) activate PLL by clearing PWRDN
           SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
           // 4) set the desired system divider and the system divider least significant bit
           SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
           SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) // clear system clock divider field
                                 + (SYSDIV2<<22);      // configure for 80 MHz clock
           // 5) wait for the PLL to lock by polling PLLLRIS
           while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
           // 6) enable use of PLL by clearing BYPASS
           SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
       }ansmit FIFO empty
        while((SSI0_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};
        DC = DC_COMMAND;
        SSI0_DR_R = message; // Command out

        // Wait until SSI0 not busy/transmit FIFO empty
        while((SSI0_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};
    }

    else
    {
        while((SSI0_SR_R&SSI_SR_TNF)==0){}; // Wait until transmit FIFO not full
        DC = DC_DATA;
        SSI0_DR_R = message;                // Data out
    }
}


void static lcddatawrite(uint8_t data)
{
    while((SSI0_SR_R&0x00000002)==0){}; // Wait until transmit FIFO not full

    DC = DC_DATA;
    SSI0_DR_R = data;                   // Data out
}


// =================== PUBLIC FUNCTIONS ===================


// If the system clock is faster than 50 MHz, the SSI baud clock will be
// faster than the 4 MHz maximum of the Nokia 5110.
// Assumes: system clock rate of 50 MHz or less [.h] ???
// Assumes: system clock rate of 80 MHz         [.c] ???
void Nokia5110_Init(void)
{
    volatile uint32_t delay;

    SYSCTL_RCGC1_R |= SYSCTL_RCGC1_SSI0;  // Activate SSI0
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // Activate port A

    delay = SYSCTL_RCGC2_R;               // Allow time to finish activating

    GPIO_PORTA_DIR_R |= 0xC0;             // Make PA6,7 out
    GPIO_PORTA_AFSEL_R |= 0x2C;           // Enable alt funct on PA2,3,5
    GPIO_PORTA_AFSEL_R &= ~0xC0;          // Disable alt funct on PA6,7
    GPIO_PORTA_DEN_R |= 0xEC;             // Enable digital I/O on PA2,3,5,6,7

    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFF0F00FF) + 0x00202200; // Configure PA2,3,5 as SSI

    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0x00FFFFFF) + 0x00000000; // Configure PA6,7 as GPIO

    GPIO_PORTA_AMSEL_R &= ~0xEC;          // Disable analog functionality on PA2,3,5,6,7
    SSI0_CR1_R &= ~SSI_CR1_SSE;           // Disable SSI
    SSI0_CR1_R &= ~SSI_CR1_MS;            // Master mode

    SSI0_CC_R = (SSI0_CC_R&~SSI_CC_CS_M)+SSI_CC_CS_SYSPLL; // Configure for system clock / PLL baud clock source

    // Clock divider for 3.33 MHz SSIClk (80 MHz PLL / 24)
    // SysClk/(CPSDVSR * (1 + SCR))
    // 80 / (24 * (1 + 0)) = 3.33 MHz (slower than 4 MHz)
    SSI0_CPSR_R = (SSI0_CPSR_R & ~SSI_CPSR_CPSDVSR_M) + 24; // Must be even number
    SSI0_CR0_R &= ~(SSI_CR0_SCR_M |       // SCR = 0 (3.33 Mbps data rate)
                    SSI_CR0_SPH |         // SPH = 0
                    SSI_CR0_SPO);         // SPO = 0

    SSI0_CR0_R = (SSI0_CR0_R & ~SSI_CR0_FRF_M) + SSI_CR0_FRF_MOTO; // FRF = Freescale format
    SSI0_CR0_R = (SSI0_CR0_R & ~SSI_CR0_DSS_M) + SSI_CR0_DSS_8;    // DSS = 8-bit data
    SSI0_CR1_R |= SSI_CR1_SSE;                                     // Enable SSI

    RESET = RESET_LOW;                    // Reset the LCD to a known state
    for(delay=0; delay<10; delay=delay+1);// Delay minimum 100 ns
    RESET = RESET_HIGH;                   // Negative logic

    lcdwrite(COMMAND, 0x21);              // Chip active; horizontal addressing mode (V = 0); use extended instruction set (H = 1)

    // Set LCD Vop (contrast), which may require some tweaking:
    lcdwrite(COMMAND, CONTRAST);          // Try 0xB1 (for 3.3V red SparkFun), 0xB8 (for 3.3V blue SparkFun), 0xBF if your display is too dark, or 0x80 to 0xFF if experimenting
    lcdwrite(COMMAND, 0x04);              // Set temp coefficient
    lcdwrite(COMMAND, 0x14);              // LCD bias mode 1:48: try 0x13 or 0x14

    lcdwrite(COMMAND, 0x20);              // We must send 0x20 before modifying the display control mode
    lcdwrite(COMMAND, 0x0C);              // Set display control to normal mode: 0x0D for inverse
}


// The character will be printed at the current cursor position, the cursor
// will automatically be updated, and it will wrap to the next row or back
// to the top if necessary. One blank column of pixels will be printed on
// either side of the character for readability.
void Nokia5110_OutChar(char data)
{
    int i;
    lcddatawrite(0x00); // Blank vertical line padding

    for(i = 0; i < 5; i = i + 1)
        lcddatawrite(ASCII[data - 0x20][i]);

    lcddatawrite(0x00); // Blank vertical line padding
}


// The string will automatically wrap, so padding spaces may
// be needed to make the output look optimal.
void Nokia5110_OutString(char *ptr)
{
    while(*ptr)
    {
        Nokia5110_OutChar((unsigned char) * ptr);
        ptr = ptr + 1;
    }
}


// Output a 16-bit number in unsigned decimal format with a
// fixed size of five right-justified digits of output.
void Nokia5110_OutUDec(uint16_t n)
{
    if(n < 10)
    {
        Nokia5110_OutString("    ");
        Nokia5110_OutChar(n + '0'); // n is between 0 and 9
    }

    else if(n < 100)
    {
        Nokia5110_OutString("    ");
        Nokia5110_OutChar(n / 10 + '0'); // Tens digit
        Nokia5110_OutChar(n % 10 + '0'); // Ones digit
    }

    else if(n < 1000)
    {
        Nokia5110_OutString("  ");
        Nokia5110_OutChar(n / 100 + '0'); n = n % 100;  // Hundreds digit

        Nokia5110_OutChar(n / 10 + '0');                // Tens digit
        Nokia5110_OutChar(n % 10 + '0');                // Ones digit
    }

    else if(n < 10000)
    {
        Nokia5110_OutChar(' ');
        Nokia5110_OutChar(n / 1000 + '0'); n = n % 1000; // Thousands digit

        Nokia5110_OutChar(n / 100 + '0'); n = n % 100;   // Hundreds digit

        Nokia5110_OutChar(n / 10 + '0');                 // Tens digit
        Nokia5110_OutChar(n % 10 + '0');                 // Ones digit
    }

    else
    {
        Nokia5110_OutChar(n / 10000 + '0'); n = n % 10000;  // Ten-thousands digit

        Nokia5110_OutChar(n / 1000 + '0'); n = n % 1000;    // Thousands digit

        Nokia5110_OutChar(n / 100 + '0'); n = n % 100;      // Hundreds digit

        Nokia5110_OutChar(n / 10 + '0');                    // Tens digit
        Nokia5110_OutChar(n % 10 + '0');                    // Ones digit
    }
}


// X = 0 is the leftmost column.
// Y = 0 is the top row.
void Nokia5110_SetCursor(uint8_t newX, uint8_t newY)
{
    if((newX > 11) || (newY > 5))        // Bad input
        return;

    // Multiply newX by 7 because each character is 7 columns wide
    lcdwrite(COMMAND, 0x80 | (newX * 7));   // Setting bit 7 updates X-position
    lcdwrite(COMMAND, 0x40 | newY);         // Setting bit 6 updates Y-position
}
void Nokia5110_Cursor(uint8_t newX, uint8_t newY)
{
    if((newX > 11) || (newY > 5))        // Bad input
        return;

    // Multiply newX by 7 because each character is 7 columns wide
    lcdwrite(COMMAND, 0x80 | (newX*7));   // Setting bit 7 updates X-position
    lcdwrite(COMMAND, 0x40 | newY);         // Setting bit 6 updates Y-position
}


// Clear the LCD by writing zeros to the entire screen and
// reset the cursor to (0,0) (top left corner of screen).
void Nokia5110_Clear(void)
{
    int i;

    for(i = 0; i < (MAX_X * MAX_Y / 8); i = i + 1)
        lcddatawrite(0x00);

    Nokia5110_SetCursor(0, 0);
}


// Fill the whole screen by drawing a 48x84 bitmap image.
// Inputs: ptr pointer to 504 byte bitmap
void Nokia5110_DrawFullImage(const uint8_t *ptr)
{
    int i;

    Nokia5110_SetCursor(0, 0);

    for(i = 0; i < (MAX_X * MAX_Y / 8); i = i + 1)
        lcddatawrite(ptr[i]);
}
void Nokia5110_MyDrawing(const uint8_t *ptr,uint8_t xpos, uint8_t ypos, uint8_t linhas, uint8_t colunas)
{
    /*  Exemplo de parametro
     *  const uint8_t pikachu[] = {
          0x0c, 0x3c, 0xdc, 0x08, 0x48, 0x10, 0x90, 0x10, 0x48, 0x08, 0xdc, 0x3c, 0x8c, 0x48, 0x28, 0x18,
          0x00, 0x1f, 0x2a, 0x40, 0x40, 0x21, 0x21, 0x21, 0x40, 0x40, 0x2a, 0x19, 0x08, 0x05, 0x03, 0x00
        };
     *  Nokia5110_MyDraw(pikachu,posicao no eixo x,posicao no eixo y,2 (numero de linhas do vetor gerado),16 (numero de colunas do vetor gerado));
     *
     *  OBS:
     *      Bitmap gerado por:
     *      https://sparks.gogo.co.nz/pcd8554-bmp.html
     *
     */
    if(xpos!=20){//se passar xpos como 20 ele n�o desenha o bitmap
        int i=0,j=1;

        Nokia5110_SetCursor(xpos, ypos);
        while(j-1<linhas){
            for(i;i < colunas*j;i++){
                lcddatawrite(ptr[i]);
            }
            Nokia5110_SetCursor(xpos, ypos + j);
            j++;
        }
    }
}

// The image will appear on the screen after the next call to Nokia5110_DisplayBuffer();
// threshold: grayscale colors above this number make corresponding pixel 'on' 0 to 14
// 0 is fine for ships, explosions, projectiles, and bunkers
void Nokia5110_PrintBMP(uint8_t xpos, uint8_t ypos, const uint8_t *ptr, uint8_t threshold)
{
    // A formata��o do BitMap deve ser tal que:
    // ptr[18] deve conter a largura
    // ptr[22] deve conter a altura

    int32_t width = ptr[18], height = ptr[22], i, j;
    uint16_t screenx, screeny;
    uint8_t mask;

    // Check for clipping
    if((height <= 0) ||                 // Bitmap is unexpectedly encoded in top-to-bottom pixel order
      ((width % 2) != 0) ||             // Must be even number of columns
      ((xpos + width) > SCREENW) ||     // Right side cut off
      (ypos < (height - 1)) ||          // Top cut off
      (ypos > SCREENH))                 // Bottom cut off
    {
        return;
    }

    if(threshold > 14)
        threshold = 14;                 // Only full 'on' turns pixel on


    // Bitmaps are encoded backwards, so start at the bottom left corner of the image

    screeny = ypos / 8;
    screenx = xpos + SCREENW*screeny;

    mask = ypos % 8;                // Row 0 to 7
    mask = 0x01 << mask;            // Now stores a mask 0x01 to 0x80
    j = ptr[10];                    // Byte 10 contains the offset where image data can be found

    for(i = 1; i <= (width * height / 2); i = i + 1)
    {
        // The left pixel is in the upper 4 bits
        if(((ptr[j] >> 4) & 0xF) > threshold)   Screen[screenx] |= mask;
        else                                    Screen[screenx] &= ~mask;

        screenx = screenx + 1;

        // The right pixel is in the lower 4 bits
        if((ptr[j] & 0xF) > threshold)  Screen[screenx] |= mask;
        else                            Screen[screenx] &= ~mask;

        screenx = screenx + 1;
        j = j + 1;

        if((i % (width / 2)) == 0)     // At the end of a row
        {
            if(mask > 0x01) mask = mask>>1;

            else
            {
                mask = 0x80;
                screeny = screeny - 1;
            }

            screenx = xpos + SCREENW*screeny;

            // Bitmaps are 32-bit word aligned

            switch((width / 2) % 4) // Skip any padding
            {
                case 0: j = j + 0; break;
                case 1: j = j + 3; break;
                case 2: j = j + 2; break;
                case 3: j = j + 1; break;
            }
        }
    }
}


// There is a buffer in RAM that holds one screen. This routine clears this buffer
void Nokia5110_ClearBuffer(void)
{
    int i;
    for(i = 0; i < SCREENW * SCREENH / 8; i = i + 1)
        Screen[i] = 0;              // clear buffer
}


// Fill the whole screen by drawing a 48x84 screen image.
void Nokia5110_DisplayBuffer(void)
{
    Nokia5110_DrawFullImage(Screen);
}


// Clear the Image pixel at (i, j), turning it dark.
// i the column index (0 to 83 in this case), x-coordinate
// j the row index (0 to 47 in this case), y-coordinate
void Nokia5110_ClrPxl(uint32_t j, uint32_t i)
{
    Screen[84 * (j >> 3) + i] &= ~Masks[j & 0x07];
}


// Set the Image pixel at (i, j), turning it on.
// i the column index (0 to 83 in this case), x-coordinate
// j the row index (0 to 47 in this case), y-coordinate
void Nokia5110_SetPxl(uint32_t j, uint32_t i)
{
    Screen[84 * (j >> 3) + i] |= Masks[j & 0x07];
}


// Configure the system to get its clock from the PLL
void PLL_Init(void)
{
    // 0) Configure the system to use RCC2 for advanced features
    //    Such as 400 MHz PLL and non-integer System Clock Divisor
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;

    // 1) Bypass PLL while initializing
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

    // 2) Select the crystal value and oscillator source
    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;         // Clear XTAL field
    SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;      // Configure for 16 MHz crystal
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;    // Clear oscillator source field
    SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;    // Configure for main oscillator source

    // 3) Activate PLL by clearing PWRDN
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;

    // 4) Set the desired system divider and the system divider least significant bit
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;            // Use 400 MHz PLL
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000)   // Clear system clock divider field
                          + (SYSDIV2<<22);          // Configure for 80 MHz clock

    // 5) Wait for the PLL to lock by polling PLLLRIS
    while((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0){};

    // 6) Enable use of PLL by clearing BYPASS
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}


// ===================== MODIFICATIONS =====================


// ???
void Nokia5110_OutDec(uint16_t n)
{
    if(n < 10)
    {
        //Nokia5110_OutString("    ");
        Nokia5110_OutChar(n + '0'); // n is between 0 and 9
    }

    else if(n < 100)
    {
        //Nokia5110_OutString("   ");
        Nokia5110_OutChar(n/10+'0'); // tens digit
        Nokia5110_OutChar(n%10+'0'); // ones digit
    }

    else if(n < 1000)
    {
        //Nokia5110_OutString("  ");
        Nokia5110_OutChar(n / 100 + '0'); n = n % 100; // Hundreds digit

        Nokia5110_OutChar(n / 10 + '0'); // tens digit
        Nokia5110_OutChar(n % 10 + '0'); // ones digit
    }

    else if(n < 10000)
    {
        //Nokia5110_OutChar(' ');
        Nokia5110_OutChar(n / 1000 + '0'); n = n % 1000; // Thousands digit

        Nokia5110_OutChar(n / 100 + '0'); n = n % 100;// Hundreds digit

        Nokia5110_OutChar(n / 10 + '0'); // Tens digit
        Nokia5110_OutChar(n % 10 + '0'); // Ones digit
    }

    else
    {
        Nokia5110_OutChar(n / 10000 + '0'); n = n % 10000;  // Ten-thousands digit

        Nokia5110_OutChar(n / 1000 + '0'); n = n % 1000;    // Thousands digit

        Nokia5110_OutChar(n / 100 + '0'); n = n % 100;      // Hundreds digit

        Nokia5110_OutChar(n / 10 + '0');                    // Tens digit
        Nokia5110_OutChar(n % 10 + '0');                    // Ones digit
    }
}


// ???
void Nokia5110_OutCharInv(char data)
{
    int i;
    lcddatawrite(0x00);        // Blank vertical line padding

    for(i = 4; i > -1; i--)
    {
        char value = 0, j, aux = ASCII[data - 0x20][i];
        for(j = 0; j < 8; j++) value |= (((aux & (0x80 >> j)) != 0) << j);
        lcddatawrite(value);
    }

    lcddatawrite(0x00);        // Blank vertical line padding
}


// ???
void Nokia5110_OutStringInv(char *ptr)
{
    int i = 0;

    while(ptr[i] != '\0') i++;

    for(i--; i > -1; i--) Nokia5110_OutCharInv(ptr[i]);
}


// ???
void Nokia5110_OutSpecial(uint16_t code)
{
    int i;
    lcddatawrite(0x00);        // blank vertical line padding
    for(i = 0; i < 5; i = i + 1) lcddatawrite(SPECIAL_SIMBOLS[code][i]);

    lcddatawrite(0x00);        // blank vertical line padding
}


// ???
void Nokia5110_DrawChar(char data)
{
    int i;
    for(i = 0; i < 5; i++) lcddatawrite(ASCII[data - 0x20][i]);
}


// ???
void Nokia5110_DrawSpecial(uint16_t code)
{
    int i;
    for(i = 0; i < 5; i++) lcddatawrite(SPECIAL_SIMBOLS[code][i]);
}


// ???
void Nokia5110_DrawMix(uint8_t code1, uint8_t code2, uint8_t code3, uint8_t code4)
{
    int i;
    for(i = 0; i < 2; i++) lcddatawrite((MIX_SIMBOLS[code1][i] << 6) | (MIX_SIMBOLS[code2][i] << 4) |
                                        (MIX_SIMBOLS[code3][i] << 2) | MIX_SIMBOLS[code4][i]);
}


// Preenchimento ???
void Nokia5110_Padding()
{
    lcddatawrite(0x00);
}
