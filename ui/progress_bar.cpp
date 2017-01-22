#include "progress_bar.h"
#include <sstream>

namespace gameAmbiance
{
    namespace ui
    {
		progress_bar::progress_bar(gameAmbiance::hw::display_pixel_driver_interface& pxlDriver, int32_t x, int32_t y, uint32_t areaWidth, uint32_t areaHeight, uint8_t fontSize, const display_font& font)
		: display_area(pxlDriver, x, y, areaWidth, areaHeight)
		, _fontSize(fontSize)
		, _font(font)
		, _lowerBound(0)
		, _upperBound(100)
        , _pos(0)
		{
			setTextBkColor(PXL_COLOR_TRANSPARENT);
		}
		
		void progress_bar::setBounds(uint32_t lowerBound, uint32_t upperBound)
		{
			_lowerBound = lowerBound;
			_upperBound = upperBound;
			
			setPos(_pos);
		}
		
		void progress_bar::setPos(uint32_t pos)
		{
			_pos = pos;
			
			clear(PXL_COLOR_OFF);
			drawRect(0, 0, width(), height(), PXL_COLOR_ON);
			float ratio = float(_pos - _lowerBound) / float(_upperBound - _lowerBound);
			fillRect(0, 0, width() * ratio , height(), PXL_COLOR_ON);
			
			std::stringstream text;
			text << uint32_t(ratio*100.0) << "%";
			drawAlignedText(TEXT_ALIGN_MIDDLE, TEXT_ALIGN_MIDDLE, text.str(), _fontSize, PXL_COLOR_INVERT, _font);
			
			render();
		}
    }
}