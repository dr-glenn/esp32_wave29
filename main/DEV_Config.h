/*****************************************************************************
* | File      	:   DEV_Config.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-02-19
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

//#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include "driver/gpio.h"

// next two needed for vTaskDelay?
#include "portmacro.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define HIGH 1
#define LOW 0

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/
// gpio_num_t required for ESP-IDF C++ code
#define EPD_SCK_PIN  (gpio_num_t)18
#define EPD_MOSI_PIN (gpio_num_t)23
#define EPD_CS_PIN   (gpio_num_t)5
#define EPD_RST_PIN  (gpio_num_t)10
#define EPD_DC_PIN   (gpio_num_t)8
#define EPD_BUSY_PIN (gpio_num_t)11

#define GPIO_PIN_SET   1
#define GPIO_PIN_RESET 0

/**
 * GPIO read and write
**/
#define digitalWrite(_pin, _value) gpio_set_level(_pin, _value)
#define digitalRead(_pin) gpio_get_level(_pin)
//#define DEV_Digital_Write(_pin, _value) digitalWrite(_pin, _value == 0? LOW:HIGH)
//#define DEV_Digital_Read(_pin) digitalRead(_pin)
#define DEV_Digital_Write(_pin, _value) gpio_set_level(_pin, _value)
#define DEV_Digital_Read(_pin) gpio_get_level(_pin)

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) vTaskDelay(__xms / portTICK_PERIOD_MS)

/*------------------------------------------------------------------------------------------------------*/
UBYTE DEV_Module_Init(void);
void GPIO_Mode(UWORD GPIO_Pin, UWORD Mode);
void DEV_SPI_WriteByte(UBYTE data);
UBYTE DEV_SPI_ReadByte();
void DEV_SPI_Write_nByte(UBYTE *pData, UDOUBLE len);

#endif