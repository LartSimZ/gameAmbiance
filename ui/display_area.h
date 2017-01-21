#pragma once

#include "../hw/display_pixel_driver_interface.h"
#include "display_font.h"

namespace gameAmbiance
{
    namespace ui
    {
       class display_area : public gameAmbiance::hw::display_pixel_driver_interface
        {
        private:
            gameAmbiance::hw::display_pixel_driver_interface& _pxlDriver;
            int16_t _x;
            int16_t _y;
            int16_t _areaWidth;
            int16_t _areaHeight;
            int16_t _cursorPosX;
            int16_t _cursorPosY;
			uint32_t _textBkColor;

        public:
            display_area(gameAmbiance::hw::display_pixel_driver_interface& pxlDriver, int16_t x, int16_t y, int16_t areaWidth, int16_t areaHeight);

            virtual void clear(uint32_t color) override;
            virtual void setPixel(int16_t x, int16_t y, uint32_t color) override;
            virtual void render() override;

            void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);
            void drawVLine(int16_t x0, int16_t y0, int16_t h, uint32_t color);
            void drawHLine(int16_t x0, int16_t y0, int16_t w, uint32_t color);
            void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
            void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
            void drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);
			void setTextBkColor(uint32_t color);
            void drawChar(int16_t x, int16_t y, char c, uint8_t fontSize, uint32_t color, const display_font& font);
            void drawText(int16_t x, int16_t y, const std::string& text, uint8_t fontSize, uint32_t color, const display_font& font);
            void setCursorPos(int16_t x, int16_t y);
            void putChar(char c, uint8_t fontSize, uint32_t color, const display_font& font);
            void putText(const std::string& text, uint8_t fontSize, uint32_t color, const display_font& font);
        };
    }
}