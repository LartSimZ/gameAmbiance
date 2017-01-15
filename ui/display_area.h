#include "../hw/display_pixel_driver_interface.h"

namespace gameAmbiance
{
    namespace ui
    {
       class display_area : public display_pixel_driver_interface
        {
        private:
            gameAmbiance::hw::display_pixel_driver& _pxlDriver;
            int16_t _x;
            int16_t _y;
            int16_t _areaWidth;
            int16_t _areaHeight;
            int16_t _cursorPosX;
            int16_t _cursorPosY;

        public:
            display_area(gameAmbiance::hw::display_pixel_driver& pxlDriver, int16_t x, int16_t y, int16_t areaWidth, int16_t areaHeight);

            virtual void clear(bool on) override;
            virtual void setPixel(int16_t x, int16_t y, bool on) override;
            virtual void render() override;

            void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, bool on);
            void drawVLine(int16_t x0, int16_t y0, int16_t h, bool on);
            void drawHLine(int16_t x0, int16_t y0, int16_t w, bool on);
            void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, bool on);
            void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, bool on);
            void drawChar(int16_t x, int16_t y, char c, uint8_t fontSize, bool on, const DisplayFont& font);
            void drawText(int16_t x, int16_t y, const std::string& text, uint8_t fontSize, bool on, const DisplayFont& font);
            void setCursorPos(int16_t x, int16_t y);
            void putChar(char c, uint8_t fontSize, bool on, const DisplayFont& font);
            void putText(const std::string& text, uint8_t fontSize, bool on, const DisplayFont& font);
        };
    }
}