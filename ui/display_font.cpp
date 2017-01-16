#include "display_font.h"

namespace gameAmbiance
{
    namespace ui
    {
        display_font::display_font(uint8_t charWidth, const uint8_t* charImages)
            : _charWidth(charWidth)
            , _charImages(charImages)
        {

        }

        uint8_t display_font::charWidth() const
        {
            return _charWidth;
        }

        uint8_t display_font::getByte(char c, uint8_t byte) const
        {
            return _charImages[c*_charWidth + byte];
        }

        void display_font::computeTextBoundingSize(const std::string& text, uint8_t fontSize, uint8_t& cx, uint8_t& cy) const
        {
            cx = (text.length() * _charWidth + text.length() - 1) * fontSize;
            cy = 7;
        }
    }
}