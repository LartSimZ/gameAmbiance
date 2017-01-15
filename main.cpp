#include <ctime>
#include <fstream>
#include <iostream>
// #include <raspicam/raspicam.h>
// #include <bcm2835.h>

#include "hw/bus_driver_spi.h"
private:
	uint8_t _pinDC;
	uint8_t _pinRST;

	void testPin(uint8_t pin, int loop_count)
	{
		printf("Testing pin #%d ...\n", pin);

		bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);

		for (int i = 0; i < loop_count; ++i)
		{
			printf("Loop #%d => H", i);

			bcm2835_gpio_write(pin, HIGH);

			bcm2835_delay(500);

			printf(" => L");

			bcm2835_gpio_write(pin, LOW);

			bcm2835_delay(500);

			printf(" ... Done !\n");
		}
	}

	uint8_t transfer(uint8_t dc_mode, uint8_t output) const
	{
		// Setup D/C line to low to switch to command mode
		bcm2835_gpio_write(_pinDC, dc_mode);

		// Write Data on SPI and read input data
		return bcm2835_spi_transfer(output);
	}

	void write(uint8_t dc_mode, uint8_t* buf, uint32_t len) const
	{
		// Setup D/C line to low to switch to command mode
		bcm2835_gpio_write(_pinDC, dc_mode);

		// Write Data on SPI
		bcm2835_spi_writenb((char*)buf, len);
	}

public:
	BusDriver_Spi(uint8_t pinDC, uint8_t pinRST)
		: _pinDC(pinDC)
		, _pinRST(pinRST)
	{
	}

	~BusDriver_Spi()
	{
		term();
	}

	void testDCpin()
	{
		testPin(_pinDC, 10);
	}

	void testRSTpin()
	{
		testPin(_pinRST, 10);
	}

	virtual bool init() const override
	{
		if (!bcm2835_spi_begin())
		{
			return false;
		}

		bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
		bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
		bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16); // 16 MHz

		bcm2835_gpio_fsel(_pinDC, BCM2835_GPIO_FSEL_OUTP);
		bcm2835_gpio_fsel(_pinRST, BCM2835_GPIO_FSEL_OUTP);

		// SPI Reset
		bcm2835_gpio_write(_pinRST, HIGH);
		delay(1000);
		bcm2835_gpio_write(_pinRST, LOW);
		delay(10000);
		bcm2835_gpio_write(_pinRST, HIGH);

		return true;
	}

	virtual void term() const override
	{
		bcm2835_spi_end();
	}

	virtual void sendCommand(uint8_t c) const override
	{
		// Write Data on SPI
		transfer(LOW, c);
	}

	virtual void sendCommand(uint8_t c0, uint8_t c1) const override
	{
		// Write Data on SPI
		uint8_t buf[] = { c0, c1 };
		write(LOW, buf, 2);
	}

	virtual void sendCommand(uint8_t c0, uint8_t c1, uint8_t c2) const override
	{
		// Write Data on SPI
		uint8_t buf[] = { c0, c1, c2 };
		write(LOW, buf, 3);
	}

	virtual void sendData(uint8_t* buf, uint32_t len) const override
	{
		// Write Data on SPI
		write(HIGH, buf, len);
	}
};

#define RPI_SPI

int main ( int argc,char **argv ) {
	
	bus_driver_spi(18, 22);
	
    raspicam::RaspiCam Camera; //Cmaera object
    //Open camera 
    cout<<"Opening Camera..."<<endl;
    if ( !Camera.open()) {cerr<<"Error opening camera"<<endl;return -1;}
    //wait a while until camera stabilizes
    cout<<"Sleeping for 3 secs"<<endl;
    //sleep(3);
    //capture
    Camera.grab();
    //allocate memory
    unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    //extract the image in rgb format
    Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );//get camera image
    //save
    std::ofstream outFile ( "raspicam_image.ppm",std::ios::binary );
    outFile<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() <<" 255\n";
    outFile.write ( ( char* ) data, Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    cout<<"Image saved at raspicam_image.ppm"<<endl;
    //free resrources    
    delete data;
    return 0;
}
