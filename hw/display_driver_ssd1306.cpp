#include "display_driver_ssd1306.h"
#include <bcm2835.h>
#include <cstring>

#define _BV(bit) (1 << (bit))

#define SSD_Command_Mode			0x00 	/* C0 and DC bit are 0 				 */
#define SSD_Data_Mode					0x40	/* C0 bit is 0 and DC bit is 1 */

#define SSD_Inverse_Display		0xA7

#define SSD_Display_Off				0xAE
#define SSD_Display_On				0xAF

#define SSD_Set_ContrastLevel	0x81

#define SSD_External_Vcc			0x01
#define SSD_Internal_Vcc			0x02


#define SSD_Activate_Scroll		0x2F
#define SSD_Deactivate_Scroll	0x2E

#define Scroll_Left						0x00
#define Scroll_Right					0x01

#define Scroll_2Frames		0x07
#define Scroll_3Frames		0x04
#define Scroll_4Frames		0x05
#define Scroll_5Frames		0x00
#define Scroll_25Frames		0x06
#define Scroll_64Frames		0x01
#define Scroll_128Frames	0x02
#define Scroll_256Frames	0x03

#define SSD1306_DISPLAYALLON_RESUME	0xA4
#define SSD1306_DISPLAYALLON 				0xA5

#define SSD1306_Normal_Display	0xA6

#define SSD1306_SETDISPLAYOFFSET 		0xD3
#define SSD1306_SETCOMPINS 					0xDA
#define SSD1306_SETVCOMDETECT 			0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 	0xD5
#define SSD1306_SETPRECHARGE 				0xD9
#define SSD1306_SETMULTIPLEX 				0xA8
#define SSD1306_SETLOWCOLUMN 				0x00
#define SSD1306_SETHIGHCOLUMN 			0x10
#define SSD1306_SETSTARTLINE 				0x40
#define SSD1306_MEMORYMODE 					0x20
#define SSD1306_COMSCANINC 					0xC0
#define SSD1306_COMSCANDEC 					0xC8
#define SSD1306_SEGREMAP 						0xA0
#define SSD1306_CHARGEPUMP 					0x8D

// Scrolling #defines
#define SSD1306_SET_VERTICAL_SCROLL_AREA 							0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 							0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 								0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 	0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL		0x2A

namespace gameAmbiance
{
    namespace hw
    {
        void display_driver_ssd1306::sendCommand(uint8_t c) const
        {
            _busDriver.sendCommand(_dcPin, c);
        }

        void display_driver_ssd1306::sendCommand(uint8_t c0, uint8_t c1) const
		{
            _busDriver.sendCommand(_dcPin, c0, c1);
		}

		void display_driver_ssd1306::sendCommand(uint8_t c0, uint8_t c1, uint8_t c2) const
		{
            _busDriver.sendCommand(_dcPin, c0, c1, c2);
		}

		void display_driver_ssd1306::sendData(uint8_t* buf, uint32_t len) const
		{
            _busDriver.sendData(_dcPin, buf, len);
		}

        display_driver_ssd1306::display_driver_ssd1306(const bus_driver_interface& busDriver, uint8_t dcPin, uint8_t rstPin, int16_t width, int16_t height)
            : _busDriver(busDriver)
            , _dcPin(dcPin)
            , _rstPin(rstPin)
            , _screenWidth(width)
            , _screenHeight(height)
            , _screenBuffer((uint8_t *)malloc((_screenWidth * _screenHeight / 8)))
        {
        }

        display_driver_ssd1306::~display_driver_ssd1306()
        {
            term();

            free(_screenBuffer);
            _screenBuffer = 0;
        }

        void display_driver_ssd1306::init()
        {
            _busDriver.setPinOutputMode(_dcPin);
            _busDriver.setPinOutputMode(_rstPin);

			bcm2835_gpio_write(_rstPin, HIGH);
			delay(250);
			bcm2835_gpio_write(_rstPin, LOW);
			delay(250);
			bcm2835_gpio_write(_rstPin, HIGH);

            sendCommand(SSD_Display_Off);                    // 0xAE
            sendCommand(SSD1306_SETDISPLAYCLOCKDIV, 0x80);      // 0xD5 + the suggested ratio 0x80
            sendCommand(SSD1306_SETMULTIPLEX, 0x3F);
            sendCommand(SSD1306_SETDISPLAYOFFSET, 0x00);        // 0xD3 + no offset
            sendCommand(SSD1306_SETSTARTLINE | 0x0);            // line #0
            sendCommand(SSD1306_CHARGEPUMP, 0x14);
            sendCommand(SSD1306_MEMORYMODE, 0x00);              // 0x20 0x0 act like ks0108
            sendCommand(SSD1306_SEGREMAP | 0x1);
            sendCommand(SSD1306_COMSCANDEC);
            sendCommand(SSD1306_SETCOMPINS, 0x12);  // 0xDA
            sendCommand(SSD_Set_ContrastLevel, 0xCF);
            sendCommand(SSD1306_SETPRECHARGE, 0x22); // 0xd9
            sendCommand(SSD1306_SETVCOMDETECT, 0x40);  // 0xDB
            sendCommand(SSD1306_DISPLAYALLON_RESUME);    // 0xA4
            sendCommand(SSD1306_Normal_Display);         // 0xA6
            sendCommand(SSD_Display_On);
        }

        void display_driver_ssd1306::term()
        {
        }

        void display_driver_ssd1306::clear(uint32_t color)
        {
            int c = color ? 0xFF : 0x00;
            std::memset(_screenBuffer, c, _screenWidth*_screenHeight / 8);
        }

        void display_driver_ssd1306::setPixel(int16_t x, int16_t y, uint32_t color)
        {
			if(color == PXL_COLOR_TRANSPARENT)
			{
				return;
			}
			
            if ((x < 0) || (x >= _screenWidth) || (y < 0) || (y >= _screenHeight))
            {
                return;
            }

            // Get where to do the change in the buffer
            uint8_t * target = _screenBuffer + (x + (y / 8)*_screenWidth);

            // x is which column
            if (color)
                *target |= _BV((y % 8));
            else
                *target &= ~_BV((y % 8));
        }

        void display_driver_ssd1306::render()
        {
            sendCommand((uint8_t)(SSD1306_SETLOWCOLUMN | 0x0)); // low col = 0
            sendCommand((uint8_t)(SSD1306_SETHIGHCOLUMN | 0x0)); // hi col = 0
            sendCommand((uint8_t)(SSD1306_SETSTARTLINE | 0x0)); // line #0

            sendData(_screenBuffer, _screenWidth*_screenHeight/8);
        }
    }
}