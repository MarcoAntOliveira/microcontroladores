
#include "display.h"

#include "simbolos.h"

const unsigned char Masks[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //usado na função Nokia5110_ClrPxl

void static lcdwrite(enum typeOfWrite type, uint8_t message){
  if(type == COMMAND){
                                        // wait until SSI0 not busy/transmit FIFO empty
    while(SSIBusy(SSI0_BASE)){};
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,0);
    SSIDataPutNonBlocking(SSI0_BASE, message);                // command out
                                        // wait until SSI0 not busy/transmit FIFO empty
    while(SSIBusy(SSI0_BASE)){};
  } else{
    while((SSI0_SR_R&SSI_SR_TNF)==0){}; // wait until transmit FIFO not full
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,0xFF);
    SSIDataPutNonBlocking(SSI0_BASE, message);                // data out
  }
}
void static lcddatawrite(uint8_t data){
  while((SSI0_SR_R&0x00000002)==0){}; // wait until transmit FIFO not full
  GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,0xFF);
  SSIDataPutNonBlocking(SSI0_BASE, data);                // data out
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
  SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);                                   // activate SSI0
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);                                  // activate port A
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);                                  // activate port E
  //delay = SYSCTL_RCGC2_R;                                                     // allow time to finish activating
  GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); // make PE1,2,3 out
  GPIOPinConfigure(GPIO_PA2_SSI0CLK);                                           // enable alt funct on PA2
  GPIOPinConfigure(GPIO_PA5_SSI0TX);                                            // enable alt funct on PA5
  GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_5);                     // configure PA2,5 as SSI
  //GPIO_PORTA_AMSEL_R &= ~0xEC;          // disable analog functionality on PA2,3,5,6,7
  //SSIDisable(SSI0_BASE);                                                        // disable SSI
  SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 150000, 8);   // master mode
  SSIEnable(SSI0_BASE);                                                         // enable SSI

  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);                                 // reset the LCD to a known state
  SysCtlDelay(10);                                                              // delay minimum 100 ns
  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0xFF);                              // negative logic

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

void Nokia5110_OutCharInv(char data){
  int i;
  lcddatawrite(0x00);        // blank vertical line padding

  for(i = 4; i > -1; i--){

    char value = 0, j, aux = ASCII[data - 0x20][i];

    for(j = 0; j < 8; j++) value |= (((aux & (0x80 >> j)) != 0) << j);

    lcddatawrite(value);
  }

  lcddatawrite(0x00);        // blank vertical line padding
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

void Nokia5110_OutStringInv(char *ptr){

  int i = 0;

  while(ptr[i] != '\0') i++;

  for(i--; i > -1; i--){
    Nokia5110_OutCharInv(ptr[i]);
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

void Nokia5110_OutSpecial(uint16_t code){

  int i;
  lcddatawrite(0x00);        // blank vertical line padding
  for(i=0; i<5; i=i+1){
    lcddatawrite(SPECIAL_SIMBOLS[code][i]);
  }
  lcddatawrite(0x00);        // blank vertical line padding
}

void Nokia5110_DrawChar(char data){

    int i;

    for(i=0; i<5; i++) lcddatawrite(ASCII[data - 0x20][i]);
}

void Nokia5110_DrawSpecial(uint16_t code){

    int i;

    for(i = 0; i < 5; i++) lcddatawrite(SPECIAL_SIMBOLS[code][i]);
}

void Nokia5110_DrawMix(uint8_t code1, uint8_t code2, uint8_t code3, uint8_t code4){

    int i;

    for(i = 0; i < 2; i++) lcddatawrite((MIX_SIMBOLS[code1][i] << 6) | (MIX_SIMBOLS[code2][i] << 4) |
                                        (MIX_SIMBOLS[code3][i] << 2) | MIX_SIMBOLS[code4][i]);
}

void Nokia5110_Padding(){

    lcddatawrite(0x00);
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

//const unsigned char Masks[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
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


