#pragma once

#include "../hw/display_pixel_driver_interface.h"
#include "display_font.h"

#define TEXT_ALIGN_LEFT		1
#define TEXT_ALIGN_TOP		1

#define TEXT_ALIGN_MIDDLE	2

#define TEXT_ALIGN_RIGHT	3
#define TEXT_ALIGN_BOTTOM	3

namespace gameAmbiance
{
    namespace ui
    {
       class display_area : public gameAmbiance::hw::display_pixel_driver_interface
        {
        private:
            gameAmbiance::hw::display_pixel_driver_interface& _pxlDriver;
            int32_t _x;
            int32_t _y;
            int32_t _areaWidth;
            int32_t _areaHeight;
            int16_t _cursorPosX;
            int16_t _cursorPosY;
			uint32_t _textBkColor;

        public:
            display_area(gameAmbiance::hw::display_pixel_driver_interface& pxlDriver, int32_t x, int32_t y, uint32_t areaWidth, uint32_t areaHeight);
			
			uint32_t width() const;
			uint32_t height() const;

            virtual void clear(uint32_t color) override;
			virtual uint32_t getPixel(int32_t x, int32_t y) const override;
            virtual void setPixel(int32_t x, int32_t y, uint32_t color) override;
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
			void drawAlignedText(uint8_t horzAlign, uint8_t vertAlign, const std::string& text, uint8_t fontSize, uint32_t color, const display_font& font);
            void setCursorPos(int16_t x, int16_t y);
            void putChar(char c, uint8_t fontSize, uint32_t color, const display_font& font);
            void putText(const std::string& text, uint8_t fontSize, uint32_t color, const display_font& font);
        };
    }
}