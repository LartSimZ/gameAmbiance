#include "bus_driver_spi.h"

#include <bmc2835.h>

namespace gameAmbiance
{
	namespace hw
	{
		uint8_t bus_driver_spi::transfer(uint8_t dcPin, uint8_t dc_mode, uint8_t output) const
		{
			// Setup D/C line to low to switch to command mode
			bcm2835_gpio_write(_pinDC, dc_mode);

			// Write Data on SPI and read input data
			return bcm2835_spi_transfer(output);
		}

		void bus_driver_spi::write(uint8_t dcPin, uint8_t dc_mode, uint8_t* buf, uint32_t len) const
		{
			// Setup D/C line to low to switch to command mode
			bcm2835_gpio_write(_pinDC, dc_mode);

			// Write Data on SPI
			bcm2835_spi_writenb((char*)buf, len);
		}

	public:
		bus_driver_spi::bus_driver_spi()
		{
			init();
		}

		bus_driver_spi::~bus_driver_spi()
		{
			term();
		}

		bool bus_driver_spi::init() const
		{
			if (!bcm2835_spi_begin())
			{
				return false;
			}

			bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
			bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
			bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16); // 16 MHz


			// SPI Reset
			bcm2835_gpio_write(_pinRST, HIGH);
			delay(1000);
			bcm2835_gpio_write(_pinRST, LOW);
			delay(10000);
			bcm2835_gpio_write(_pinRST, HIGH);

			return true;
		}
		
		void bus_driver_spi::term() const
		{
			bcm2835_spi_end();
		}
		
		void bus_driver_spi::setPinOutputMode(uint8_t pin) const
		{
			bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
		}
		
		void bus_driver_spi::setPinInputMode(uint8_t pin) const
		{
			bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INTP);
		}

		void bus_driver_spi::sendCommand(uint8_t c) const
		{
			// Write Data on SPI
			transfer(LOW, c);
		}

		void bus_driver_spi::sendCommand(uint8_t c0, uint8_t c1) const
		{
			// Write Data on SPI
			uint8_t buf[] = { c0, c1 };
			write(LOW, buf, 2);
		}

		void bus_driver_spi::sendCommand(uint8_t c0, uint8_t c1, uint8_t c2) const
		{
			// Write Data on SPI
			uint8_t buf[] = { c0, c1, c2 };
			write(LOW, buf, 3);
		}

		void bus_driver_spi::sendData(uint8_t* buf, uint32_t len) const
		{
			// Write Data on SPI
			write(HIGH, buf, len);
		}
	}
}