#pragma once

#include "display_area.h"
#include "display_font.h"

namespace gameAmbiance
{
    namespace ui
    {
		class progress_bar : public display_area
        {
        private:
			const display_font& _font;
			uint8_t _fontSize;
			uint32_t _lowerBound;
			uint32_t _upperBound;
            uint32_t _pos;

        public:
            progress_bar(gameAmbiance::hw::display_pixel_driver_interface& pxlDriver, int32_t x, int32_t y, uint32_t areaWidth, uint32_t areaHeight, uint8_t fontSize, const display_font& font);

			void setBounds(uint32_t lowerBound, uint32_t upperBound);
			void setPos(uint32_t pos);
        };
    }
}