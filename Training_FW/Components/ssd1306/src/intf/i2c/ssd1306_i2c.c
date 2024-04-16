/*
    MIT License

    Copyright (c) 2017-2018, Alexey Dynda

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "ssd1306_i2c.h"
#include "intf/ssd1306_interface.h"
#include "driver/gpio.h"

#define CONFIG_PLATFORM_I2C_AVAILABLE 0X01
#define CONFIG_PLATFORM_I2C_ENABLE 0x01


void ssd1306_i2cInitEx(int8_t scl, int8_t sda, int8_t sa)
{
#if defined(CONFIG_PLATFORM_I2C_AVAILABLE) && defined(CONFIG_PLATFORM_I2C_ENABLE)
    ssd1306_platform_i2cConfig_t cfg;
    cfg.scl = GPIO_NUM_22;
    cfg.sda = GPIO_NUM_21;
    ssd1306_platform_i2cInit(0, sa, &cfg);
#elif defined(CONFIG_TWI_I2C_AVAILABLE) && defined(CONFIG_TWI_I2C_ENABLE)
    ssd1306_i2cConfigure_Twi(0);
    ssd1306_i2cInit_Twi(sa);
#elif defined(CONFIG_SOFTWARE_I2C_AVAILABLE) && defined(CONFIG_SOFTWARE_I2C_ENABLE)
    ssd1306_i2cInit_Embedded(scl, sda, sa);
#else
    #warning "ssd1306 library: no i2c support for the target platform"
#endif
}

void ssd1306_i2cInit(void)
{
    // ssd1306_i2cInitEx(22, 21, SSD1306_SA);
    int8_t sa;
    sa=0x3c;
    ssd1306_platform_i2cConfig_t cfg;
    cfg.scl = GPIO_NUM_22;
    cfg.sda = GPIO_NUM_21;
    ssd1306_platform_i2cInit(0, sa, &cfg);
}
