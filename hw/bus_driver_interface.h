#pragma once

#include "../base/type_defs.h"

namespace gameAmbiance
{
	namespace hw
	{
		class bus_driver_interface
		{
		public:
			virtual bool init() const = 0;
			virtual void term() const = 0;
			
			virtual void setPinOutputMode(uint8_t pin) const = 0;
			virtual void setPinInputMode(uint8_t pin) const = 0;

			virtual void sendCommand(uint8_t dcPin, uint8_t c) const = 0;
			virtual void sendCommand(uint8_t dcPin, uint8_t c0, uint8_t c1) const = 0;
			virtual void sendCommand(uint8_t dcPin, uint8_t c0, uint8_t c1, uint8_t c2) const = 0;
			virtual void sendData(uint8_t dcPin, uint8_t* buf, uint32_t len) const = 0;
		};
	}
}