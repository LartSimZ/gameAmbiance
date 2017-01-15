#include "display_driver_interface.h"

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
            _busDriver.sendCommand(_dcPin, buf, len);
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

        void display_driver_ssd1306::clear(bool on)
        {
            int c = on ? 0xFF : 0x00;
            std::memset(_screenBuffer, c, _screenWidth*_screenHeight / 8);
        }

        void display_driver_ssd1306::setPixel(int16_t x, int16_t y, bool on)
        {
            if ((x < 0) || (x >= _screenWidth) || (y < 0) || (y >= _screenHeight))
            {
                return;
            }

            // Get where to do the change in the buffer
            uint8_t * target = _screenBuffer + (x + (y / 8)*_screenWidth);

            // x is which column
            if (on)
                *target |= _BV((y % 8));
            else
                *target &= ~_BV((y % 8));
        }

        void display_driver_ssd1306::update()
        {
            _busDriver.sendCommand(SSD1306_SETLOWCOLUMN | 0x0); // low col = 0
            _busDriver.sendCommand(SSD1306_SETHIGHCOLUMN | 0x0); // hi col = 0
            _busDriver.sendCommand(SSD1306_SETSTARTLINE | 0x0); // line #0

            _busDriver.sendData(_screenBuffer, _screenWidth*_screenHeight/8);
        }
    }
}