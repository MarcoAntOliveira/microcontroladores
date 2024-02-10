/*
 * clock.h
 *
 *  Created on: 25 de abr de 2018
 *      Author: Usuario
 */


#include <stdint.h>

#ifndef CLOCK_H_
#define CLOCK_H_




#define _80MHZ                      0xC1000001
#define _50MHZ                      0x01C00001
#define _20MHZ                      0x04C00001
#define _4MHZ                       0x98C00001
#define _250KHZ                     0x9FC02001

//define RCC                         0x400FE060
//define RCC2                        0x400FE070


#define RCC_BYPASS                  1 << 11
#define RCC_USESYSDIV               1 << 22
#define RCC2_BYPASS2                1 << 11
#define RCC_XTAL_M                  0x7C0
#define RCC_OSCSRC                  0x30
#define RCC_XTAL_16MHZ              0x540   //0x15 << 6
#define RCC_OSCSRC_PIOSC            0x10
#define RCC2_USE_RCC2               1 << 31
#define RCC2_OSCSRC2_M              0x70
#define RCC_PWR_DN                  1 << 13
#define RCC2_PWR_DN2                1 << 13

#define ESC_REG(x)                  (*((volatile uint32_t *)(x)))

#define SYSCTL_RCGC2_R              0x400FE108
#define SYSCTL_RCGC2_GPIOF          0x00000020
#define GPIO_PORTF_DIR_R            0x40025400
#define GPIO_PORTF_DEN_R            0x4002551C
#define GPIO_PORTF_DATA_R           0x400253FC
#define INT_PLL_LOCK                0x40
#define MISC                        0x400FE058
#define RIS                         0x400FE050

#define RCC_SYSDIV_M                0x07800000
#define RCC_MOSCDIS                 0x1

#define RCC2_SYSDIV2_M              0x1F800000
#define RCC2_SYSDIV400                 0x40000000
#define RCC2_SYSDIV2_LSB            0x00400000

/* Escreva uma função ConfiguraClock que
 * aceite as seguintes configurações de entrada 80MHz,
 * 50 MHz, 20MHz, 4 MHz e a menor frequência possível usando
 * o oscilador interno (utilize o registrador RCC2). */


#define ESC_REG(x)                          (*((volatile uint32_t *)(x)))

#define SYSCTL_RCGC2_R                      0x400FE108
#define SYSCTL_RCGC2_GPIOF                  0x00000020
#define GPIO_PORTF_DIR_R                    0x40025400
#define GPIO_PORTF_DEN_R                    0x4002551C
#define GPIO_PORTF_DATA_R                   0x400253FC

#define SYSCTL_RCC_R                        0x400FE060
#define RCC_ACG                             0x08000000
#define RCC_SYSDIV                          0x07800000
#define RCC_USEPWMDIV                       0x00100000
#define RCC_PWMDIV                          0x000E0000
#define RCC_PWRDN                           0x00002000
#define RCC_XTAL                            0x000007C0

#define SYSCTL_RCC2_R                       0x400FE070
#define RCC2_USERCC2                        0x80000000
#define RCC2_DIV400                         0x40000000
#define RCC2_SYSDIV2                        0x1F800000
#define RCC2_SYSDIV2LSB                     0x00400000
#define RCC2_USBPWRDN                       0x00004000
#define RCC2_PWRDN2                         0x00002000
#define RCC2_OSCSRC2                        0x00000070

#define SYSCTL_MISC_R                       0x400FE058
#define SYSCTL_RIS_R                        0x400FE050
#define PLLRIS                              0x00000040


void configuraClock(uint32_t config)
{
    //
    int delay_t, RCC, RCC2;
    //
    RCC   = ESC_REG(SYSCTL_RCC_R);                                  //  copying RCC to local variable
    RCC2  = ESC_REG(SYSCTL_RCC2_R);                                 //  copying RCC2 to local variable
    //
    RCC  |= RCC_BYPASS;                                             //  setting RCC BYPASS bit
    RCC  &= ~(RCC_USESYSDIV);                                       //  clearing RCC USESYSDIV bit
    RCC2 |= RCC2_BYPASS2;                                           //  setting RCC2 BYPASS bit
    ESC_REG(SYSCTL_RCC_R)  = RCC;                                   //  writing in RCC
    ESC_REG(SYSCTL_RCC2_R) = RCC;                                   //  writing in RCC2
    //
    RCC  &= ~(RCC_XTAL | RCC_OSCSRC);                               //  clearing XTAL and OSCSRC bit fields
    RCC  |= (config & RCC_XTAL) | (config & RCC_OSCSRC);            //  setting XTAL and OSCSRC bit fields values
    RCC2 &= ~(RCC2_USERCC2 | RCC2_OSCSRC2);                         //  clearing USERCC2 bit and OSCSRC2 bit field
    RCC2 |= (config & RCC2_USERCC2) | (config & RCC2_OSCSRC2);      //  setting USERCC2 bit and OSCSRC bit field values
    ESC_REG(SYSCTL_RCC_R)  = RCC;                                   //  writing in RCC
    ESC_REG(SYSCTL_RCC2_R) = RCC2;                                  //  writing in RCC2
    //
    RCC  &= ~(RCC_PWRDN);                                           //  clearing PWRDN bit in RCC
    RCC  |= config & RCC_PWRDN;                                     //  defining PWRDN bit value
    RCC2 &= ~(RCC2_PWRDN2);                                         //  clearing PWRDN2 bit in RCC2
    RCC2 |= config & RCC2_PWRDN2;                                   //  defining PWRDN2 bit value in RCC2
    ESC_REG(SYSCTL_MISC_R) = PLLRIS;                                //  locking PLL
    //
    if(RCC2 & RCC2_USERCC2)
    {
        ESC_REG(SYSCTL_RCC2_R) = RCC2;                              //  writing in RCC2
        ESC_REG(SYSCTL_RCC_R)  = RCC;                               //  writing in RCC
    }
    else
    {
        ESC_REG(SYSCTL_RCC_R)  = RCC;                               //  writing in RCC
        ESC_REG(SYSCTL_RCC2_R) = RCC2;                              //  writing in RCC2
    }
    //
    RCC  &= ~(RCC_SYSDIV | RCC_USESYSDIV | RCC_MOSCDIS);            //  clearing SYSDIV, USESYSDIV and MOSCDIS bits in RCC
    RCC  |= config & (RCC_SYSDIV | RCC_USESYSDIV | RCC_MOSCDIS);    //  defining SYSDIV, USESYSDIV and MOSCDIS values in RCC
    RCC2 &= ~(RCC2_SYSDIV2);                                        //  clearing SYSDIV2 bits in RCC2
    RCC2 |= config & (RCC2_SYSDIV2);                                //  defining SYSDIV2 values in RCC2
    RCC2 &= ~(RCC2_DIV400 | RCC2_SYSDIV2LSB);                       //  clearing DIV400 and SYSDIV2LSB bits in RCC2
    RCC2 |= config & (RCC2_DIV400 | RCC2_SYSDIV2LSB);               //  defining DIV400 and SYSDIV2LSB values in RCC2
    //
    if(!(config & RCC_BYPASS))                                      //  if PLL is being used
    {
        for(delay_t = 32000; delay_t > 0; delay_t--)                //  maximum delay
        {
            if(ESC_REG(SYSCTL_RIS_R) & PLLRIS)                      //  checking if PLL is ready
                break;
        }
        RCC  &= ~(RCC_BYPASS);                                      //  clearing BYPASS in RCC
        RCC2 &= ~(RCC2_BYPASS2);                                    //  clearing BYPASS2 in RCC2
    }
    //
    ESC_REG(SYSCTL_RCC_R)  = RCC;                                   //  writing values in RCC
    ESC_REG(SYSCTL_RCC2_R) = RCC2;                                  //  writing values in RCC2
}





#endif /* CLOCK_H_ */
