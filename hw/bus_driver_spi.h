#include "bus_driver_interface.h"

namespace gameAmbiance
{
	namespace hw
	{
		class bus_driver_spi : public bus_driver_interface
		{
		private:
			uint8_t transfer(uint8_t dcPin, uint8_t dc_mode, uint8_t output) const;
			void write(uint8_t dcPin, uint8_t dc_mode, uint8_t* buf, uint32_t len) const;

		public:
			bus_driver_spi();
			~bus_driver_spi();

			virtual bool init() const override;
			virtual void term() const override;
						
			virtual void setPinOutputMode(uint8_t pin) const override;
			virtual void setPinInputMode(uint8_t pin) const override;

			virtual void sendCommand(uint8_t dcPin, uint8_t c) const override;
			virtual void sendCommand(uint8_t dcPin, uint8_t c0, uint8_t c1) const override;
			virtual void sendCommand(uint8_t dcPin, uint8_t c0, uint8_t c1, uint8_t c2) const override;
			virtual void sendData(uint8_t dcPin, uint8_t* buf, uint32_t len) const override;
		};
	}
}