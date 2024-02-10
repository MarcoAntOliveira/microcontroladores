/*
 * Selecao_Menu.h
 *
 *  Created on: 31 de mai de 2019
 *      Author: Danilo
 */

#ifndef SELECAO_MENU_H_
#define SELECAO_MENU_H_

#include "Selecao_Sobre.h"
#include "Selecao_Play.h"
#include "Selecao_Help.h"
#include "conf_botton.h"

const unsigned char Menu01_BG01[] = {
    0xc7, 0xc7, 0xc7, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x80, 0xc0, 0xc0, 0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xe0, 0x67, 0x67, 0x67, 0x60, 0xe0, 0xe0, 0xe7, 0x67, 0xe7, 0xe0, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7, 0x60, 0x60, 0x60, 0xe7, 0xe7, 0xe7, 0x60, 0xe0, 0xe0, 0xe7, 0x67, 0xe7, 0xe0, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xe0, 0xe7, 0xc7, 0xc7, 0x80, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x38, 0x38, 0x38,
    0x71, 0x71, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xfb, 0xfb, 0xfb, 0xfc, 0xff, 0xff, 0xc0, 0xdf, 0xdf, 0xdf, 0xdf, 0xff, 0xff, 0xc0, 0xf7, 0xf7, 0xf7, 0xc0, 0xff, 0xff, 0xfc, 0xfb, 0xc7, 0xfb, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x8e,
    0x1c, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0xf0, 0x80, 0xf0, 0x10, 0xf0, 0x00, 0xf0, 0x10, 0xd0, 0xd0, 0xd0, 0xd0, 0x70, 0x00, 0xf0, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0xd0, 0xd0, 0xd0, 0x30, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0xe3, 0xe3,
    0xc7, 0xc7, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x1e, 0x02, 0x1e, 0x10, 0x1f, 0x00, 0x1f, 0x10, 0x16, 0x16, 0x16, 0x17, 0x1c, 0x00, 0x1f, 0x10, 0x17, 0x14, 0x14, 0x14, 0x1c, 0x00, 0x1f, 0x10, 0x1e, 0x02, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38,
    0x71, 0x71, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x06, 0xba, 0xaa, 0xba, 0x06, 0xfc, 0x00, 0xfe, 0x02, 0xda, 0xda, 0xda, 0x26, 0xdc, 0x00, 0xfc, 0x06, 0xfa, 0x8a, 0xfa, 0x06, 0xfc, 0x00, 0xfe, 0x02, 0xfe, 0x80, 0xfe, 0x02, 0xfe, 0x00, 0x0e, 0x0a, 0xfa, 0x02, 0xfa, 0x0a, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x8e,
    0x1c, 0x1c, 0x1c, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe3, 0x02, 0x03, 0x00, 0xe3, 0xe2, 0xe3, 0x00, 0x03, 0x02, 0xe2, 0xe2, 0xe2, 0x03, 0x01, 0x00, 0xe1, 0xe3, 0xe2, 0x02, 0x02, 0x03, 0xe1, 0xe0, 0xe1, 0x03, 0x02, 0x02, 0xe2, 0xe3, 0xe1, 0x00, 0x00, 0x00, 0xe3, 0xe2, 0xe3, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe3, 0xe3, 0xe3
};

const unsigned char Menu01_BG02[] = {
    0x38, 0x38, 0x38, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x87, 0xc7, 0xc7, 0xe0, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7, 0x60, 0x60, 0x60, 0x67, 0xe7, 0xe7, 0xe0, 0x60, 0xe0, 0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xe0, 0x67, 0x67, 0x67, 0xe0, 0xe0, 0xe0, 0x67, 0xe7, 0xe7, 0xe0, 0x60, 0xe0, 0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7, 0xe0, 0xc0, 0xc0, 0x87, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0xc7, 0xc7, 0xc7,
    0x8e, 0x8e, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xfb, 0xfb, 0xfb, 0xfc, 0xff, 0xff, 0xc0, 0xdf, 0xdf, 0xdf, 0xdf, 0xff, 0xff, 0xc0, 0xf7, 0xf7, 0xf7, 0xc0, 0xff, 0xff, 0xfc, 0xfb, 0xc7, 0xfb, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x71, 0x71,
    0xe3, 0xe3, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0xf0, 0x80, 0xf0, 0x10, 0xf0, 0x00, 0xf0, 0x10, 0xd0, 0xd0, 0xd0, 0xd0, 0x70, 0x00, 0xf0, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0xd0, 0xd0, 0xd0, 0x30, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x1c, 0x1c,
    0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x1e, 0x02, 0x1e, 0x10, 0x1f, 0x00, 0x1f, 0x10, 0x16, 0x16, 0x16, 0x17, 0x1c, 0x00, 0x1f, 0x10, 0x17, 0x14, 0x14, 0x14, 0x1c, 0x00, 0x1f, 0x10, 0x1e, 0x02, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0xc7, 0xc7,
    0x8e, 0x8e, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x06, 0xba, 0xaa, 0xba, 0x06, 0xfc, 0x00, 0xfe, 0x02, 0xda, 0xda, 0xda, 0x26, 0xdc, 0x00, 0xfc, 0x06, 0xfa, 0x8a, 0xfa, 0x06, 0xfc, 0x00, 0xfe, 0x02, 0xfe, 0x80, 0xfe, 0x02, 0xfe, 0x00, 0x0e, 0x0a, 0xfa, 0x02, 0xfa, 0x0a, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x71, 0x71,
    0xe3, 0xe3, 0xe3, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x03, 0xe2, 0xe3, 0xe0, 0x03, 0x02, 0x03, 0xe0, 0xe3, 0xe2, 0x02, 0x02, 0x02, 0xe3, 0xe1, 0xe0, 0x01, 0x03, 0x02, 0xe2, 0xe2, 0xe3, 0x01, 0x00, 0x01, 0xe3, 0xe2, 0xe2, 0x02, 0x03, 0x01, 0xe0, 0xe0, 0xe0, 0x03, 0x02, 0x03, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x1c, 0x1c, 0x1c
};

const unsigned char Menu02_BG01[] = {
    0xc7, 0xc7, 0xc7, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0xc0, 0x47, 0x47, 0x47, 0x40, 0xc0, 0x80, 0xc7, 0x47, 0xc7, 0x00, 0x00, 0x00, 0x07, 0x87, 0xc7, 0x40, 0x40, 0x40, 0xc7, 0x87, 0xc7, 0x40, 0xc0, 0x00, 0xc7, 0x47, 0xc7, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x38, 0x38, 0x38,
    0x71, 0x71, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x40, 0x7b, 0x0b, 0x0b, 0x0c, 0x07, 0x7f, 0x40, 0x5f, 0x50, 0x50, 0x50, 0x70, 0x7f, 0x40, 0x77, 0x15, 0x77, 0x40, 0x7f, 0x07, 0x0c, 0x7b, 0x46, 0x7b, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x8e,
    0x1c, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x18, 0xf8, 0xf8, 0xf8, 0x18, 0xf8, 0xf8, 0xf8, 0x18, 0xd8, 0xd8, 0xd8, 0xd8, 0xf8, 0xf8, 0xf8, 0x18, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x18, 0xd8, 0xd8, 0xd8, 0x38, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0xe3, 0xe3,
    0xc7, 0xc7, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x30, 0x3e, 0x3e, 0x3e, 0x30, 0x3f, 0x3f, 0x3f, 0x30, 0x36, 0x36, 0x36, 0x37, 0x3f, 0x3f, 0x3f, 0x30, 0x37, 0x37, 0x37, 0x37, 0x3f, 0x3f, 0x3f, 0x30, 0x3e, 0x3e, 0x3e, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38,
    0x71, 0x71, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x06, 0xba, 0xaa, 0xba, 0x06, 0xfc, 0x00, 0xfe, 0x02, 0xda, 0xda, 0xda, 0x26, 0xdc, 0x00, 0xfc, 0x06, 0xfa, 0x8a, 0xfa, 0x06, 0xfc, 0x00, 0xfe, 0x02, 0xfe, 0x80, 0xfe, 0x02, 0xfe, 0x00, 0x0e, 0x0a, 0xfa, 0x02, 0xfa, 0x0a, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x8e,
    0x1c, 0x1c, 0x1c, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe3, 0x02, 0x03, 0x00, 0xe3, 0xe2, 0xe3, 0x00, 0x03, 0x02, 0xe2, 0xe2, 0xe2, 0x03, 0x01, 0x00, 0xe1, 0xe3, 0xe2, 0x02, 0x02, 0x03, 0xe1, 0xe0, 0xe1, 0x03, 0x02, 0x02, 0xe2, 0xe3, 0xe1, 0x00, 0x00, 0x00, 0xe3, 0xe2, 0xe3, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe3, 0xe3, 0xe3
};

const unsigned char Menu02_BG02[] = {
    0x38, 0x38, 0x38, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0xc7, 0x40, 0x40, 0x40, 0x47, 0xc7, 0x87, 0xc0, 0x40, 0xc0, 0x07, 0x07, 0x07, 0x00, 0x80, 0xc0, 0x47, 0x47, 0x47, 0xc0, 0x80, 0xc0, 0x47, 0xc7, 0x07, 0xc0, 0x40, 0xc0, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0xc7, 0xc7, 0xc7,
    0x8e, 0x8e, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x40, 0x7b, 0x0b, 0x0b, 0x0c, 0x07, 0x7f, 0x40, 0x5f, 0x50, 0x50, 0x50, 0x70, 0x7f, 0x40, 0x77, 0x15, 0x77, 0x40, 0x7f, 0x07, 0x0c, 0x7b, 0x46, 0x7b, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x71, 0x71,
    0xe3, 0xe3, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x18, 0xf8, 0xf8, 0xf8, 0x18, 0xf8, 0xf8, 0xf8, 0x18, 0xd8, 0xd8, 0xd8, 0xd8, 0xf8, 0xf8, 0xf8, 0x18, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x18, 0xd8, 0xd8, 0xd8, 0x38, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x1c, 0x1c,
    0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x30, 0x3e, 0x3e, 0x3e, 0x30, 0x3f, 0x3f, 0x3f, 0x30, 0x36, 0x36, 0x36, 0x37, 0x3f, 0x3f, 0x3f, 0x30, 0x37, 0x37, 0x37, 0x37, 0x3f, 0x3f, 0x3f, 0x30, 0x3e, 0x3e, 0x3e, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0xc7, 0xc7,
    0x8e, 0x8e, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x06, 0xba, 0xaa, 0xba, 0x06, 0xfc, 0x00, 0xfe, 0x02, 0xda, 0xda, 0xda, 0x26, 0xdc, 0x00, 0xfc, 0x06, 0xfa, 0x8a, 0xfa, 0x06, 0xfc, 0x00, 0xfe, 0x02, 0xfe, 0x80, 0xfe, 0x02, 0xfe, 0x00, 0x0e, 0x0a, 0xfa, 0x02, 0xfa, 0x0a, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x71, 0x71,
    0xe3, 0xe3, 0xe3, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x03, 0xe2, 0xe3, 0xe0, 0x03, 0x02, 0x03, 0xe0, 0xe3, 0xe2, 0x02, 0x02, 0x02, 0xe3, 0xe1, 0xe0, 0x01, 0x03, 0x02, 0xe2, 0xe2, 0xe3, 0x01, 0x00, 0x01, 0xe3, 0xe2, 0xe2, 0x02, 0x03, 0x01, 0xe0, 0xe0, 0xe0, 0x03, 0x02, 0x03, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x1c, 0x1c, 0x1c
};


const unsigned char Menu03_BG01[] = {
    0xc7, 0xc7, 0xc7, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0xc0, 0x47, 0x47, 0x47, 0x40, 0xc0, 0x80, 0xc7, 0x47, 0xc7, 0x00, 0x00, 0x00, 0x07, 0x87, 0xc7, 0x40, 0x40, 0x40, 0xc7, 0x87, 0xc7, 0x40, 0xc0, 0x00, 0xc7, 0x47, 0xc7, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x38, 0x38, 0x38,
    0x71, 0x71, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x40, 0x7b, 0x0b, 0x0b, 0x0c, 0x07, 0x7f, 0x40, 0x5f, 0x50, 0x50, 0x50, 0x70, 0x7f, 0x40, 0x77, 0x15, 0x77, 0x40, 0x7f, 0x07, 0x0c, 0x7b, 0x46, 0x7b, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x8e,
    0x1c, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0xf0, 0x80, 0xf0, 0x10, 0xf0, 0x00, 0xf0, 0x10, 0xd0, 0xd0, 0xd0, 0xd0, 0x70, 0x00, 0xf0, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0xd0, 0xd0, 0xd0, 0x30, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0xe3, 0xe3,
    0xc7, 0xc7, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x1e, 0x02, 0x1e, 0x10, 0x1f, 0x00, 0x1f, 0x10, 0x16, 0x16, 0x16, 0x17, 0x1c, 0x00, 0x1f, 0x10, 0x17, 0x14, 0x14, 0x14, 0x1c, 0x00, 0x1f, 0x10, 0x1e, 0x02, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38,
    0x71, 0x71, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xbb, 0xbb, 0xbb, 0x07, 0xff, 0xff, 0xff, 0x03, 0xdb, 0xdb, 0xdb, 0x27, 0xff, 0xff, 0xff, 0x07, 0xfb, 0xfb, 0xfb, 0x07, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0x03, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x8e,
    0x1c, 0x1c, 0x1c, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe1, 0xe3, 0xe3, 0x07, 0x07, 0x07, 0xe7, 0xe7, 0xe7, 0x06, 0x07, 0x07, 0xe7, 0xe6, 0xe7, 0x07, 0x07, 0x06, 0xe6, 0xe6, 0xe6, 0x07, 0x07, 0x07, 0xe7, 0xe7, 0xe6, 0x06, 0x06, 0x07, 0xe7, 0xe7, 0xe7, 0x07, 0x06, 0x06, 0xe6, 0xe7, 0xe7, 0x07, 0x07, 0x07, 0xe7, 0xe6, 0xe7, 0x07, 0x07, 0x07, 0xe7, 0xe7, 0xe7, 0x07, 0x03, 0x03, 0xe1, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe3, 0xe3, 0xe3
};

const unsigned char Menu03_BG02[] = {
    0x38, 0x38, 0x38, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0xc7, 0x40, 0x40, 0x40, 0x47, 0xc7, 0x87, 0xc0, 0x40, 0xc0, 0x07, 0x07, 0x07, 0x00, 0x80, 0xc0, 0x47, 0x47, 0x47, 0xc0, 0x80, 0xc0, 0x47, 0xc7, 0x07, 0xc0, 0x40, 0xc0, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0xc7, 0xc7, 0xc7,
    0x8e, 0x8e, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x40, 0x7b, 0x0b, 0x0b, 0x0c, 0x07, 0x7f, 0x40, 0x5f, 0x50, 0x50, 0x50, 0x70, 0x7f, 0x40, 0x77, 0x15, 0x77, 0x40, 0x7f, 0x07, 0x0c, 0x7b, 0x46, 0x7b, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x71, 0x71,
    0xe3, 0xe3, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0xf0, 0x80, 0xf0, 0x10, 0xf0, 0x00, 0xf0, 0x10, 0xd0, 0xd0, 0xd0, 0xd0, 0x70, 0x00, 0xf0, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0xd0, 0xd0, 0xd0, 0x30, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x1c, 0x1c,
    0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x1e, 0x02, 0x1e, 0x10, 0x1f, 0x00, 0x1f, 0x10, 0x16, 0x16, 0x16, 0x17, 0x1c, 0x00, 0x1f, 0x10, 0x17, 0x14, 0x14, 0x14, 0x1c, 0x00, 0x1f, 0x10, 0x1e, 0x02, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0xc7, 0xc7,
    0x8e, 0x8e, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xbb, 0xbb, 0xbb, 0x07, 0xff, 0xff, 0xff, 0x03, 0xdb, 0xdb, 0xdb, 0x27, 0xff, 0xff, 0xff, 0x07, 0xfb, 0xfb, 0xfb, 0x07, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0x03, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x71, 0x71,
    0xe3, 0xe3, 0xe3, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x01, 0x03, 0x03, 0xe7, 0xe7, 0xe7, 0x07, 0x07, 0x07, 0xe6, 0xe7, 0xe7, 0x07, 0x06, 0x07, 0xe7, 0xe7, 0xe6, 0x06, 0x06, 0x06, 0xe7, 0xe7, 0xe7, 0x07, 0x07, 0x06, 0xe6, 0xe6, 0xe7, 0x07, 0x07, 0x07, 0xe7, 0xe6, 0xe6, 0x06, 0x07, 0x07, 0xe7, 0xe7, 0xe7, 0x07, 0x06, 0x07, 0xe7, 0xe7, 0xe7, 0x07, 0x07, 0x07, 0xe7, 0xe3, 0xe3, 0x01, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x1c, 0x1c, 0x1c
};

uint32_t ui32ADC0Value[4];
volatile uint32_t ui32TempAvg;
volatile uint32_t ui32TempAvg2; //item 2 da tarefa
volatile uint32_t ui32TempValueC;

void SelectMenu(int option)
{
    if( get_matriz_botao(1000) == SELECT )
    {
        switch(option)
        {
            case 0:
                selectPlay(ui32TempValueC);
                break;

            case 1:
                selectHelp();
                break;

            case 2:
                selectAbout();
                break;

            default:
                break;
        }
    }
}

int cont = 0;
int Select( int select )
{

    if( get_matriz_botao(1000) == LOW )
    {
        SysCtlDelay( 2500000 );
        select++;
        if( select > 2 ) select--;
    }

    else if( get_matriz_botao(1000) == HIGH )
    {
        SysCtlDelay( 2500000 );
        select--;
        if( select < 0 ) select++;
    }

    switch(select)
    {
        case 0:
            Nokia5110_ClearBuffer();
            if(cont == 0) Nokia5110_PrintBMP2(0,0,Menu01_BG01,84,48);
            else if(cont == 1) Nokia5110_PrintBMP2(0,0,Menu01_BG02,84,48);
            Nokia5110_DisplayBuffer();
            break;

        case 1:
            Nokia5110_ClearBuffer();
            if(cont == 0) Nokia5110_PrintBMP2(0,0,Menu02_BG01,84,48);
            else if(cont == 1) Nokia5110_PrintBMP2(0,0,Menu02_BG02,84,48);
            Nokia5110_DisplayBuffer();
            break;

        case 2:
            Nokia5110_ClearBuffer();
            if(cont == 0) Nokia5110_PrintBMP2(0,0,Menu03_BG01,84,48);
            else if(cont == 1) Nokia5110_PrintBMP2(0,0,Menu03_BG02,84,48);
            Nokia5110_DisplayBuffer();
            break;

        default:
            break;
    }

    SelectMenu(select);

    SysCtlDelay( 1000 );

    return select;
}

//funcao usada na interupcao timer
void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    cont++;
    if(cont > 1) cont = 0;
}

#endif /* SELECAO_MENU_H_ */
