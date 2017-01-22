#include "display_area.h"

namespace gameAmbiance
{
    namespace ui
    {
		display_area::display_area(gameAmbiance::hw::display_pixel_driver_interface& pxlDriver, int32_t x, int32_t y, uint32_t areaWidth, uint32_t areaHeight)
		: _pxlDriver(pxlDriver)
		, _x(x)
		, _y(y)
		, _areaWidth(areaWidth)
		, _areaHeight(areaHeight)
		, _cursorPosX(0)
		, _cursorPosY(0)
		, _textBkColor(PXL_COLOR_OFF)
		{
		}
		
		uint32_t display_area::width() const
		{
			return _areaWidth;
		}
		
		uint32_t display_area::height() const
		{
			return _areaHeight;
		}

		void display_area::clear(uint32_t color)
		{
			fillRect(0, 0, _areaWidth, _areaHeight, color);
			setCursorPos(0, 0);
		}
		
		uint32_t display_area::getPixel(int32_t x, int32_t y) const
		{
			return _pxlDriver.getPixel(_x + x, _y + y);
		}

		void display_area::setPixel(int32_t x, int32_t y, uint32_t color)
		{
			if (x < 0
				|| x >= _areaWidth
				|| y < 0
				|| y >= _areaHeight)
			{
				return; // Out of area, does nothing
			}

			_pxlDriver.setPixel(_x + x, _y + y, color);
		}

		void display_area::render()
		{
			_pxlDriver.render();
		}

		void display_area::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)
		{
			int16_t steep = abs(y1 - y0) > abs(x1 - x0);
			if (steep)
			{
				_swap_int(x0, y0);
				_swap_int(x1, y1);
			}

			if (x0 > x1)
			{
				_swap_int(x0, x1);
				_swap_int(y0, y1);
			}

			int16_t dx, dy;
			dx = x1 - x0;
			dy = abs(y1 - y0);

			int16_t err = dx / 2;
			int16_t ystep;

			if (y0 < y1)
			{
				ystep = 1;
			}
			else {
				ystep = -1;
			}

			for (; x0 <= x1; x0++)
			{
				if (steep)
				{
					setPixel(y0, x0, color);
				}
				else
				{
					setPixel(x0, y0, color);
				}
				err -= dy;
				if (err < 0) {
					y0 += ystep;
					err += dx;
				}
			}
		}

		void display_area::drawVLine(int16_t x0, int16_t y0, int16_t h, uint32_t color)
		{
			drawLine(x0, y0, x0, y0 + h - 1, color);
		}

		void display_area::drawHLine(int16_t x0, int16_t y0, int16_t w, uint32_t color)
		{
			drawLine(x0, y0, x0 + w - 1, y0, color);
		}

		void display_area::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
		{
			drawHLine(x, y, w, color);
			drawHLine(x, y + h - 1, w, color);
			drawVLine(x, y, h, color);
			drawVLine(x + w - 1, y, h, color);
		}

		void display_area::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
		{
			for (int16_t i = x; i < x + w; i++) {
				drawVLine(i, y, h, color);
			}
		}

		void display_area::drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)
		{
			int16_t f = 1 - r;
			int16_t ddF_x = 1;
			int16_t ddF_y = -2 * r;
			int16_t x = 0;
			int16_t y = r;

			setPixel(x0, y0 + r, color);
			setPixel(x0, y0 - r, color);
			setPixel(x0 + r, y0, color);
			setPixel(x0 - r, y0, color);

			while (x<y) {
				if (f >= 0) {
					y--;
					ddF_y += 2;
					f += ddF_y;
				}
				x++;
				ddF_x += 2;
				f += ddF_x;

				setPixel(x0 + x, y0 + y, color);
				setPixel(x0 - x, y0 + y, color);
				setPixel(x0 + x, y0 - y, color);
				setPixel(x0 - x, y0 - y, color);
				setPixel(x0 + y, y0 + x, color);
				setPixel(x0 - y, y0 + x, color);
				setPixel(x0 + y, y0 - x, color);
				setPixel(x0 - y, y0 - x, color);
			}
		}

		void display_area::setTextBkColor(uint32_t color)
		{
			_textBkColor = color;
		}
		
		void display_area::drawChar(int16_t x, int16_t y, char c, uint8_t fontSize, uint32_t color, const display_font& font)
		{
			if ((x >= _areaWidth) || // Clip right
				(y >= _areaHeight) || // Clip bottom
				((x + (font.charWidth() + 1) * fontSize - 1) < 0) || // Clip left
				((y + 8 * fontSize - 1) < 0))   // Clip top
				return;

			//if (!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior

			for (int8_t i = 0; i <= font.charWidth(); i++)
			{
				uint8_t line;
				if (i == font.charWidth())
				{
					line = 0x0;
				}
				else
				{
					line = font.getByte(c, i);
				}

				for (int8_t j = 0; j<8; j++)
				{
					if (line & 0x1)
					{
						if (fontSize == 1) // default size
						{
							setPixel(x + i, y + j, color);
						}
						else
						{  // big size
							fillRect(x + (i*fontSize), y + (j*fontSize), fontSize, fontSize, color);
						}
					}
					else if (_textBkColor != color && _textBkColor != PXL_COLOR_TRANSPARENT)
					{
						if (fontSize == 1) // default size
						{
							setPixel(x + i, y + j, !color);
						}
						else
						{  // big size
							fillRect(x + i*fontSize, y + j*fontSize, fontSize, fontSize, _textBkColor);
						}
					}
					line >>= 1;
				}
			}
		}

		void display_area::setCursorPos(int16_t x, int16_t y)
		{
			_cursorPosX = x;
			_cursorPosY = y;
		}

		void display_area::putChar(char c, uint8_t fontSize, uint32_t color, const display_font& font)
		{
			if (c != '\n')
			{
				drawChar(_cursorPosX, _cursorPosY, c, fontSize, color, font);
				_cursorPosX += fontSize*(1+font.charWidth());
			}
			else
			{
				_cursorPosX = 0;
				_cursorPosY += fontSize*8;
			}
		}

		void display_area::drawText(int16_t x, int16_t y, const std::string& text, uint8_t fontSize, uint32_t color, const display_font& font)
		{
			uint8_t textLen = text.length();

			for (uint8_t c = 0; c < textLen; ++c, x = x + fontSize*(font.charWidth() + 1))
			{
				drawChar(x, y, text[c], fontSize, color, font);
			}
		}
		
		void display_area::drawAlignedText(uint8_t horzAlign, uint8_t vertAlign, const std::string& text, uint8_t fontSize, uint32_t color, const display_font& font)
		{
			uint32_t textWidth(0), textHeight(0);
			font.computeTextBoundingSize(text, fontSize, textWidth, textHeight);
			
			int16_t x(0), y(0);
			switch(horzAlign)
			{
				case TEXT_ALIGN_LEFT:
				x = 0;
				break;
				
				case TEXT_ALIGN_MIDDLE:
				x = (_areaWidth - textWidth) / 2;
				break;
				
				case TEXT_ALIGN_RIGHT:
				x = _areaWidth - textWidth;
				break;
			}
			switch(vertAlign)
			{
				case TEXT_ALIGN_TOP:
				y = 0;
				break;
				
				case TEXT_ALIGN_MIDDLE:
				y = (_areaHeight - textHeight) / 2;
				break;
				
				case TEXT_ALIGN_BOTTOM:
				y = _areaHeight - textHeight;
				break;
			}
			drawText(x, y, text, fontSize, color, font);
		}

		void display_area::putText(const std::string& text, uint8_t fontSize, uint32_t color, const display_font& font)
		{
			uint8_t textLen = text.length();

			for (uint8_t c = 0; c < textLen; ++c)
			{
				putChar(text[c], fontSize, color, font);
			}
		}
    }
}