/*****************************************************************************
* | File      	:   DEV_Config.c
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
#include "DEV_Config.h"
#include "esp_log.h"
char *TAG = "config";

void GPIO_Config(void)
{
    EPAPER_PIN epaper_spi[6];
    epaper_spi[0] = { .pin=EPD_BUSY_PIN, .mode=GPIO_MODE_INPUT, .init=PIN_NOT_SET };
    epaper_spi[1] = { .pin=EPD_RST_PIN, .mode=GPIO_MODE_OUTPUT, .init=PIN_NOT_SET };
    epaper_spi[2] = { .pin=EPD_DC_PIN, .mode=GPIO_MODE_OUTPUT, .init=PIN_NOT_SET };
    epaper_spi[3] = { .pin=EPD_SCK_PIN, .mode=GPIO_MODE_OUTPUT, .init=LOW };
    epaper_spi[4] = { .pin=EPD_MOSI_PIN, .mode=GPIO_MODE_OUTPUT, .init=PIN_NOT_SET };
    epaper_spi[5] = { .pin=EPD_CS_PIN, .mode=GPIO_MODE_OUTPUT, .init=HIGH };

    for (int i=0; i < 6; i++) {
        gpio_reset_pin(epaper_spi[i].pin);
        gpio_set_direction(epaper_spi[i].pin, epaper_spi[i].mode);
        if (epaper_spi[i].init != PIN_NOT_SET) gpio_set_level(epaper_spi[i].pin, epaper_spi[i].init);
    }
    // Show me how the pins are configured.
    // They need to be GPIO, not IOMUX.
    uint64_t pins = 0;
    pins |= 1 << EPD_BUSY_PIN;
    pins |= 1 << EPD_RST_PIN;
    pins |= 1 << EPD_DC_PIN;
    pins |= 1 << EPD_SCK_PIN;
    pins |= 1 << EPD_MOSI_PIN;
    pins |= 1 << EPD_CS_PIN;
    pins |= 1 << GPIO_NUM_3;
    gpio_dump_io_configuration(stdout, pins);
}

void GPIO_Mode(gpio_num_t GPIO_Pin, UWORD Mode)
{
    esp_err_t status;
    if(Mode == 0) {
        status = gpio_set_direction(GPIO_Pin , GPIO_MODE_INPUT);
	} else {
		status = gpio_set_direction(GPIO_Pin , GPIO_MODE_INPUT_OUTPUT);
	}
}
/******************************************************************************
function:	Module Initialize, the BCM2835 library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_Module_Init(void)
{
	//gpio
	GPIO_Config();

	//serial printf
	//Serial.begin(115200);

	// spi
	// SPI.setDataMode(SPI_MODE0);
	// SPI.setBitOrder(MSBFIRST);
	// SPI.setClockDivider(SPI_CLOCK_DIV4);
	// SPI.begin();

	return 0;
}

/******************************************************************************
function:
			SPI read and write
******************************************************************************/
void DEV_SPI_WriteByte(UBYTE data)
{
    //SPI.beginTransaction(spi_settings);
    digitalWrite(EPD_CS_PIN, GPIO_PIN_RESET);

    for (int i = 0; i < 8; i++)
    {
        if ((data & 0x80) == 0) digitalWrite(EPD_MOSI_PIN, GPIO_PIN_RESET); 
        else                    digitalWrite(EPD_MOSI_PIN, GPIO_PIN_SET);

        data <<= 1;
        digitalWrite(EPD_SCK_PIN, GPIO_PIN_SET);     
        digitalWrite(EPD_SCK_PIN, GPIO_PIN_RESET);
    }

    //SPI.transfer(data);
    digitalWrite(EPD_CS_PIN, GPIO_PIN_SET);
    //SPI.endTransaction();	
}

UBYTE DEV_SPI_ReadByte()
{
    UBYTE j=0xff;
    GPIO_Mode(EPD_MOSI_PIN, 0);
    digitalWrite(EPD_CS_PIN, GPIO_PIN_RESET);
    for (int i = 0; i < 8; i++)
    {
        j = j << 1;
        if (digitalRead(EPD_MOSI_PIN))  j = j | 0x01;
        else                            j = j & 0xfe;
        
        digitalWrite(EPD_SCK_PIN, GPIO_PIN_SET);
        digitalWrite(EPD_SCK_PIN, GPIO_PIN_RESET);
    }
    digitalWrite(EPD_CS_PIN, GPIO_PIN_SET);
    GPIO_Mode(EPD_MOSI_PIN, 1);
    return j;
}

void DEV_SPI_Write_nByte(UBYTE *pData, UDOUBLE len)
{
    for (int i = 0; i < len; i++)
        DEV_SPI_WriteByte(pData[i]);
}
