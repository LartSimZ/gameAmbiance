#pragma once

#include "../base/type_defs.h"

namespace gameAmbiance
{
    namespace ui
    {
        class display_font
        {
        private:
            uint8_t _charWidth;
            const uint8_t * _charImages;

        protected:
            display_font(uint8_t charWidth, const uint8_t* charImages);

        public:
            uint8_t charWidth() const;
            uint8_t getByte(char c, uint8_t byte) const;
            void computeTextBoundingSize(const std::string& text, uint8_t fontSize, uint8_t& cx, uint8_t& cy) const;
        };
    }
}