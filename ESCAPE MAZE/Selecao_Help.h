/*
 * Selecao_Help.h
 *
 *  Created on: 1 de jul de 2019
 *      Author: Danilo
 */

#ifndef SELECAO_HELP_H_
#define SELECAO_HELP_H_

#include "conf_botton.h"

const unsigned char OptionHelp01[] = {
    0x38, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xef, 0xef, 0xef, 0x01, 0xff, 0xff, 0x01, 0x6d, 0x6d, 0x6d, 0x7d, 0xff, 0xff, 0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0x01, 0xed, 0xed, 0xed, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x38,
    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf9, 0x89, 0x89, 0x89, 0x89, 0x01, 0xc1, 0x21, 0x21, 0x41, 0x01, 0xc1, 0x21, 0x21, 0x41, 0x01, 0x41, 0x21, 0x21, 0x21, 0xc1, 0x01, 0xe1, 0x41, 0x21, 0x21, 0xc1, 0x01, 0xc1, 0x21, 0x21, 0x21, 0xc1, 0x01, 0x01, 0x01, 0x01, 0xc1, 0x21, 0x21, 0x41, 0xf9, 0x01, 0xc1, 0x21, 0x21, 0x21, 0xc1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x00, 0x04, 0x09, 0x09, 0x06, 0x00, 0x07, 0x08, 0x08, 0x04, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x7f, 0x04, 0x08, 0x08, 0x07, 0x00, 0x07, 0x09, 0x09, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x04, 0x0f, 0x00, 0x07, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x20, 0x90, 0x90, 0x90, 0xe0, 0x00, 0xfc, 0x20, 0x10, 0x10, 0xe0, 0x00, 0xf4, 0x00, 0xf0, 0x20, 0x10, 0x00, 0xf4, 0x00, 0xf0, 0x20, 0x10, 0x10, 0xe0, 0x10, 0xfc, 0x10, 0xe0, 0x10, 0x10, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x20, 0x90, 0x90, 0x90, 0xe0, 0x00, 0xf0, 0x20, 0x10, 0x10, 0xe0, 0x10, 0xfc, 0x10, 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x00, 0x60, 0x90, 0x90, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x04, 0x04, 0x04, 0x03, 0x04, 0x04, 0x04, 0x07, 0x00, 0x07, 0x02, 0x04, 0x04, 0x03, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x04, 0x03, 0x04, 0x04, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x04, 0x03, 0x04, 0x04, 0x04, 0x02, 0x00, 0x02, 0x04, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf4, 0xe4, 0xc4, 0x84, 0x04, 0x84, 0xc4, 0xe4, 0xf4, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
};

const unsigned char OptionHelp02[] = {
    0x38, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xef, 0xef, 0xef, 0x01, 0xff, 0xff, 0x01, 0x6d, 0x6d, 0x6d, 0x7d, 0xff, 0xff, 0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0x01, 0xed, 0xed, 0xed, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x38,
    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0x41, 0x41, 0x81, 0xc1, 0x01, 0xc1, 0x01, 0x01, 0x01, 0xc1, 0x01, 0x81, 0x41, 0x41, 0x41, 0x81, 0x01, 0x01, 0x01, 0x01, 0x81, 0x41, 0x41, 0x41, 0x81, 0x01, 0x01, 0x01, 0x41, 0xf1, 0x41, 0x81, 0x41, 0x41, 0x41, 0x81, 0x01, 0xc1, 0x81, 0x41, 0x81, 0x81, 0x41, 0x81, 0x01, 0xc1, 0x81, 0x41, 0x41, 0x81, 0x01, 0x81, 0x41, 0x41, 0x41, 0x81, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x10, 0x08, 0xff, 0x00, 0x0f, 0x10, 0x10, 0x08, 0x1f, 0x00, 0x0f, 0x12, 0x12, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x10, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x0f, 0x12, 0x12, 0x12, 0x0b, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0xff, 0x08, 0x10, 0x10, 0x0f, 0x00, 0x0f, 0x10, 0x10, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0xc0, 0x20, 0x20, 0x40, 0x00, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0xf8, 0x40, 0x20, 0x20, 0xc0, 0x00, 0xc0, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xc0, 0x20, 0x20, 0x40, 0x00, 0xc0, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x07, 0x08, 0x08, 0x04, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x04, 0x08, 0x08, 0x07, 0x00, 0x07, 0x09, 0x09, 0x09, 0x05, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x08, 0x04, 0x03, 0x00, 0x04, 0x09, 0x09, 0x06, 0x00, 0x07, 0x09, 0x09, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf4, 0xe4, 0xc4, 0x84, 0x04, 0x84, 0xc4, 0xe4, 0xf4, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
};

const unsigned char OptionHelp03[] = {
    0x38, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xef, 0xef, 0xef, 0x01, 0xff, 0xff, 0x01, 0x6d, 0x6d, 0x6d, 0x7d, 0xff, 0xff, 0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0x01, 0xed, 0xed, 0xed, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x38,
    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xc1, 0x21, 0x21, 0x21, 0xc1, 0x01, 0xe1, 0x41, 0x21, 0x21, 0xc1, 0x01, 0xc1, 0x21, 0x21, 0x41, 0x01, 0x41, 0x21, 0x21, 0x21, 0xc1, 0x01, 0xc1, 0x21, 0x21, 0x21, 0xc1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x07, 0x00, 0x7f, 0x04, 0x08, 0x08, 0x07, 0x00, 0x07, 0x08, 0x08, 0x04, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x07, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x10, 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x00, 0xfc, 0x00, 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x10, 0xfc, 0x10, 0xf0, 0x20, 0x10, 0x00, 0x20, 0x90, 0x90, 0x90, 0xe0, 0x00, 0xf0, 0x20, 0x10, 0x10, 0xe0, 0x00, 0x60, 0x90, 0x90, 0x20, 0x00, 0xf0, 0x20, 0x10, 0x10, 0xe0, 0x00, 0xe0, 0x10, 0x10, 0x10, 0xe0, 0x00, 0xf0, 0x20, 0x10, 0x10, 0xfc, 0x10, 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x03, 0x04, 0x04, 0x04, 0x02, 0x00, 0x07, 0x00, 0x03, 0x04, 0x04, 0x04, 0x02, 0x00, 0x07, 0x04, 0x07, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x02, 0x04, 0x04, 0x03, 0x00, 0x3f, 0x02, 0x04, 0x04, 0x03, 0x00, 0x03, 0x04, 0x04, 0x04, 0x03, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x04, 0x03, 0x04, 0x04, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf4, 0xe4, 0xc4, 0x84, 0x04, 0x84, 0xc4, 0xe4, 0xf4, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
};

const unsigned char OptionHelp04[] = {
    0x38, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xef, 0xef, 0xef, 0x01, 0xff, 0xff, 0x01, 0x6d, 0x6d, 0x6d, 0x7d, 0xff, 0xff, 0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0x01, 0xed, 0xed, 0xed, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x38,
    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xe1, 0x41, 0x21, 0x21, 0xc1, 0x01, 0x41, 0x21, 0x21, 0x21, 0xc1, 0x01, 0xe1, 0x41, 0x21, 0x01, 0x41, 0x21, 0x21, 0x21, 0xc1, 0x01, 0x01, 0x01, 0x01, 0xc1, 0x21, 0x21, 0x41, 0xe1, 0x01, 0x41, 0x21, 0x21, 0x21, 0xc1, 0x01, 0xe1, 0x41, 0x21, 0x21, 0xc1, 0x01, 0xf9, 0x41, 0x21, 0x21, 0xc1, 0x01, 0x41, 0x21, 0x21, 0x21, 0xc1, 0x01, 0xe1, 0x41, 0x21, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x04, 0x08, 0x08, 0x07, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x27, 0x48, 0x48, 0x44, 0x3f, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xfc, 0x10, 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x00, 0xf0, 0x20, 0x10, 0xe0, 0x20, 0x10, 0xe0, 0x00, 0xf0, 0x20, 0x10, 0x10, 0xe0, 0x00, 0xe0, 0x10, 0x10, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x44, 0x44, 0x44, 0x38, 0x00, 0xe0, 0x10, 0x10, 0x10, 0xe0, 0x00, 0xf0, 0x20, 0x10, 0x00, 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x00, 0xf0, 0x20, 0x10, 0xe0, 0x20, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x03, 0x04, 0x04, 0x04, 0x02, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x3f, 0x02, 0x04, 0x04, 0x03, 0x00, 0x03, 0x04, 0x04, 0x04, 0x03, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x03, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x02, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf4, 0xe4, 0xc4, 0x84, 0x04, 0x84, 0xc4, 0xe4, 0xf4, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
};

const unsigned char OptionHelp05[] = {
    0x38, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xef, 0xef, 0xef, 0x01, 0xff, 0xff, 0x01, 0x6d, 0x6d, 0x6d, 0x7d, 0xff, 0xff, 0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0x01, 0xed, 0xed, 0xed, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x38,
    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x41, 0x21, 0x21, 0x21, 0xc1, 0x01, 0x01, 0x01, 0x01, 0xc1, 0x21, 0x21, 0x41, 0x01, 0x41, 0x21, 0x21, 0x21, 0xc1, 0x01, 0xc1, 0x21, 0x21, 0x41, 0xf9, 0x01, 0x41, 0x21, 0x21, 0x21, 0xc1, 0x01, 0x01, 0x01, 0x01, 0xe1, 0x01, 0x01, 0x01, 0xe1, 0x01, 0xc1, 0x21, 0x21, 0x41, 0x01, 0xc1, 0x21, 0x21, 0x21, 0xc1, 0x01, 0x01, 0x01, 0x01, 0xc1, 0x21, 0x21, 0x41, 0xf9, 0x01, 0xc1, 0x21, 0x21, 0x21, 0xc1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x04, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x07, 0x08, 0x08, 0x04, 0x0f, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x04, 0x0f, 0x00, 0x04, 0x09, 0x09, 0x06, 0x00, 0x07, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x04, 0x0f, 0x00, 0x07, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x20, 0x10, 0x00, 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x00, 0xe0, 0x10, 0x10, 0x20, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0x20, 0x10, 0x00, 0x60, 0x90, 0x90, 0x20, 0x00, 0xe0, 0x10, 0x10, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0x20, 0x10, 0xe0, 0x20, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x02, 0x00, 0x03, 0x04, 0x04, 0x02, 0x00, 0x03, 0x04, 0x04, 0x02, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x04, 0x04, 0x03, 0x00, 0x03, 0x04, 0x04, 0x04, 0x03, 0x00, 0x10, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x02, 0x07, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf4, 0xe4, 0xc4, 0x84, 0x04, 0x84, 0xc4, 0xe4, 0xf4, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
};

const unsigned char OptionHelp06[] = {
    0x38, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xef, 0xef, 0xef, 0x01, 0xff, 0xff, 0x01, 0x6d, 0x6d, 0x6d, 0x7d, 0xff, 0xff, 0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0x01, 0xed, 0xed, 0xed, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x38,
    0x00, 0x00, 0x00, 0xf1, 0x41, 0x81, 0x41, 0x41, 0x41, 0x81, 0x01, 0xc1, 0x81, 0x41, 0x81, 0x81, 0x41, 0x81, 0x01, 0xc1, 0x81, 0x41, 0x41, 0x81, 0x01, 0x81, 0x41, 0x41, 0x41, 0x81, 0x01, 0x01, 0x01, 0x01, 0xc1, 0x81, 0x41, 0x81, 0x81, 0x41, 0x81, 0x01, 0xd1, 0x01, 0xc1, 0x81, 0x41, 0x41, 0x81, 0x01, 0xd1, 0x01, 0xc1, 0x81, 0x41, 0x81, 0x81, 0x41, 0x81, 0x01, 0x81, 0x41, 0x41, 0x41, 0x81, 0x01, 0x01, 0x01, 0x01, 0x81, 0x41, 0x41, 0x81, 0xf1, 0x01, 0x81, 0x41, 0x41, 0x41, 0x81, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1f, 0x10, 0x0f, 0x12, 0x12, 0x12, 0x0b, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0xff, 0x08, 0x10, 0x10, 0x0f, 0x00, 0x0f, 0x10, 0x10, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0x0f, 0x10, 0x10, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x10, 0x08, 0x1f, 0x00, 0x0f, 0x12, 0x12, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0x40, 0x00, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0xe0, 0x40, 0x20, 0xc0, 0x40, 0x20, 0xc0, 0x00, 0xe8, 0x00, 0xe0, 0x40, 0x20, 0x20, 0xc0, 0x00, 0xf8, 0x40, 0x20, 0x20, 0xc0, 0x00, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0xc0, 0x20, 0x20, 0x40, 0xf8, 0x00, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x28, 0x24, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x04, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x07, 0x08, 0x08, 0x04, 0x0f, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x07, 0x09, 0x09, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf4, 0xe4, 0xc4, 0x84, 0x04, 0x84, 0xc4, 0xe4, 0xf4, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
};

const unsigned char OptionHelpEnd[] = {
    0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x2f, 0x27, 0x23, 0x21, 0x20, 0x21, 0x23, 0x27, 0x2f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x48, 0x48, 0x48, 0x70, 0x00, 0x30, 0x48, 0x48, 0x90, 0x08, 0xfe, 0x08, 0x90, 0x48, 0x48, 0x48, 0xf0, 0x00, 0xfe, 0x10, 0x08, 0x08, 0xf0, 0x00, 0xf0, 0x48, 0x48, 0x48, 0x70, 0x00, 0xfe, 0x00, 0xf0, 0x48, 0x48, 0x48, 0x70, 0x00, 0xf0, 0x08, 0x08, 0x10, 0x00, 0xfa, 0x00, 0xf0, 0x08, 0x08, 0x10, 0xfe, 0x00, 0xf0, 0x08, 0x08, 0x08, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x01, 0x02, 0x02, 0x01, 0x00, 0x03, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x00, 0x03, 0x01, 0x02, 0x02, 0x01, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x03, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x01, 0x02, 0x02, 0x01, 0x00, 0x03, 0x00, 0x01, 0x02, 0x02, 0x01, 0x03, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void selectHelp(void)
{
    int select = 0;
    //Jogo desenvolvido como Trabalho final para a disciplina EMB5642-Microcontroladores.
    while(1)
    {
        if( get_matriz_botao(1000) == LOW )
        {
            SysCtlDelay( 2500000 );
            select++;
            if( select > 6 ) select--;
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
                Nokia5110_PrintBMP2(0,0,OptionHelp01,84,48);
                Nokia5110_DisplayBuffer();
                break;

           case 1:
                Nokia5110_ClearBuffer();
                Nokia5110_PrintBMP2(0,0,OptionHelp02,84,48);
                Nokia5110_DisplayBuffer();
                break;

           case 2:
                Nokia5110_ClearBuffer();
                Nokia5110_PrintBMP2(0,0,OptionHelp03,84,48);
                Nokia5110_DisplayBuffer();
                break;

           case 3:
                Nokia5110_ClearBuffer();
                Nokia5110_PrintBMP2(0,0,OptionHelp04,84,48);
                Nokia5110_DisplayBuffer();
                break;

           case 4:
                Nokia5110_ClearBuffer();
                Nokia5110_PrintBMP2(0,0,OptionHelp05,84,48);
                Nokia5110_DisplayBuffer();
                break;

           case 5:
               Nokia5110_ClearBuffer();
               Nokia5110_PrintBMP2(0,0,OptionHelp06,84,48);
               Nokia5110_DisplayBuffer();
               break;

           case 6:
                Nokia5110_ClearBuffer();
                Nokia5110_PrintBMP2(0,0,OptionHelpEnd,84,48);
                Nokia5110_DisplayBuffer();
                break;

           default:
               break;
        }

        if(get_matriz_botao(1000) == BACK) break; //caso queira sair do menu sobre
    }
}

#endif /* SELECAO_HELP_H_ */
