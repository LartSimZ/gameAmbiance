#include <ctime>
#include <fstream>
#include <iostream>
// #include <raspicam/raspicam.h>

#include "hw/bus_driver_spi.h"
#include "hw/display_driver_ssd1306.h"
#include "ui/display_area.h"

int main ( int argc,char **argv ) {
	
	gameAmbiance::hw::bus_driver_spi bus;
	gameAmbiance::hw::display_driver_ssd1306 display(bus, 18, 22, 128, 64);

	bus.init();
	display.init();

	gameAmbiance::ui::display_area fullArea(display, 0, 0, 128, 64);
	gameAmbiance::ui::display_area topArea(fullArea, 0, 0, 128, 16);
	gameAmbiance::ui::display_area mainArea(fullArea, 0, 16, 128, 48);
	
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
