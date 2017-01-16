#pragma once

#include "display_driver_interface.h"
#include "bus_driver_interface.h"

namespace gameAmbiance
{
    namespace hw
    {
		class display_driver_ssd1306 : public display_driver_interface
		{
		private:
			const bus_driver_interface& _busDriver;
            uint8_t _dcPin;
            uint8_t _rstPin;
            int16_t _screenWidth;
            int16_t _screenHeight;
            uint8_t* _screenBuffer;

			void sendCommand(uint8_t c) const;
        	void sendCommand(uint8_t c0, uint8_t c1) const;
			void sendCommand(uint8_t c0, uint8_t c1, uint8_t c2) const;
			void sendData(uint8_t* buf, uint32_t len) const;

		public:
			display_driver_ssd1306(const bus_driver_interface& busDriver, uint8_t dcPin, uint8_t rstPin, int16_t width, int16_t height);
			~display_driver_ssd1306();

			virtual void init() override;
			virtual void term() override;

			virtual void clear(uint32_t color) override;
			virtual void setPixel(int16_t x, int16_t y, uint32_t color) override;
			virtual void render() override;
		};
	}
}