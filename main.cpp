#include <ctime>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "hw/bus_driver_spi.h"
#include "hw/display_driver_ssd1306.h"
#include "ui/display_area.h"
#include "ui/display_font_5x7.h"
#include "hw/camera_driver_raspi.h"
#include "ui/keyboard.h"
#include "ui/progress_bar.h"

#include <opencv2/opencv.hpp>

int main ( int argc,char **argv ) {
	
    std::cout << "Starting ..." << std::endl;

	gameAmbiance::hw::bus_driver_spi bus;
	gameAmbiance::hw::display_driver_ssd1306 display(bus, 18, 22, 128, 64);

    if( !bus.init() )
    {
        std::cerr << "Failed to initialize SPI bus !" << std::endl;
        return -1;
    }
    std::cout << "SPI bus ready !" << std::endl;

	display.init();
    std::cout << "Display ready !" << std::endl;

    gameAmbiance::ui::display_font_5x7 font;
	gameAmbiance::ui::display_area fullArea(display, 0, 0, 128, 64);
	gameAmbiance::ui::display_area topArea(fullArea, 0, 0, 128, 16);
	gameAmbiance::ui::display_area mainArea(fullArea, 0, 16, 128, 48);
	
	topArea.drawAlignedText(TEXT_ALIGN_MIDDLE, TEXT_ALIGN_MIDDLE, "BOOTING ...", 2, PXL_COLOR_ON, font);
	mainArea.putText("Display ... OK\n", 1, PXL_COLOR_ON, font);
	mainArea.putText("Camera ...", 1, PXL_COLOR_ON, font);
	fullArea.render();
	
	gameAmbiance::hw::camera_driver_raspi camera;
	if(!camera.init())
	{
		topArea.clear(PXL_COLOR_OFF);
		topArea.drawText(0, 0, "FAILED !!!", 2, PXL_COLOR_ON, font);
		mainArea.putText(" ERR!!!", 1, PXL_COLOR_ON, font);
		fullArea.render();
		std::cerr << "Failed to initialize camera !" << std::endl;
		return -1;
	}
	mainArea.putText(" OK", 1, PXL_COLOR_ON, font);
	fullArea.render();
	std::cout << "Camera ready (Frame size = " << camera.frameWidth() << "x" << camera.frameHeight() << ") !" << std::endl;
	
	//delay(1000);
	
	fullArea.clear(PXL_COLOR_OFF);
	topArea.setTextBkColor(PXL_COLOR_TRANSPARENT);
	topArea.clear(PXL_COLOR_ON);
	topArea.drawAlignedText(TEXT_ALIGN_MIDDLE, TEXT_ALIGN_MIDDLE, "RUNNING", 2, PXL_COLOR_OFF, font);
	fullArea.render();
	
	gameAmbiance::ui::progress_bar progress(mainArea, 0, 37, 128, 11, 1, font);
	progress.setPos(0);
	
	// if( !camera.readFrame(frame) )
	// {
		// std::cout << "Failed to read frame from camera !" << std::endl;
		// return -1;
	// }
    // std::ofstream outFile ( "raspicam_image.ppm",std::ios::binary );
    // outFile<<"P6\n"<<camera.frameWidth() <<" "<<camera.frameHeight() <<" 255\n";
    // outFile.write ( ( char* ) frame.bytes, frame.byteSize);
    // std::cout<<"Image saved at raspicam_image.ppm"<<std::endl;
	
	//cv::Ptr<cv::BackgroundSubtractor> ptrMOG( cv::createBackgroundSubtractorMOG() ); //MOG approach
	cv::Ptr<cv::BackgroundSubtractor> ptrMOG2( cv::createBackgroundSubtractorMOG2() ); //MOG2 approach
	gameAmbiance::hw::video_frame currentFrame;
	cv::Mat fgMaskMOG, fgMaskMOG2;
	uint32_t frameId = 0;
	for( ; ; ++frameId)
	{
		// Check key
		if(gameAmbiance::ui::keyboard::inputAvailable())
		{
			int key = gameAmbiance::ui::keyboard::readKey();
			if(key == UI_KEY_ESCAPE)
			{
				break;
			}
			
			if(key == 'P' || key == 'p')
			{
				std::cout << "PAUSED !" << std::endl;
				std::cin.get();
			}
		}
		
		// Show frame information
		std::stringstream msg;
		msg << "Frame : #" << frameId;
		mainArea.drawText(0, 0, msg.str(), 1, PXL_COLOR_ON, font);
		fullArea.render();
		
        //read the current frame
        if(!camera.readFrame(currentFrame))
		{
            std::cerr << "Unable to read next frame." << std::endl;
            std::cerr << "Exiting..." << std::endl;
            exit(EXIT_FAILURE);
        }
		
        //update the background model
		cv::Mat matCurrentFrame(camera.frameHeight(), camera.frameWidth(), CV_8UC3, currentFrame.bytes);
		// std::stringstream ss;
		// cv::rectangle(matCurrentFrame, cv::Point(10, 2), cv::Point(100,20),
		// cv::Scalar(255,255,255), -1);
		// ss << frameId;
		// std::string frameNumberString = ss.str();
		// cv::putText(matCurrentFrame, frameNumberString.c_str(), cv::Point(15, 15),
		// cv::FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
	//show the current frame and the fg masks
		//cv::imwrite("/tmp/gameAmbiance/video.png", matCurrentFrame);
        //ptrMOG->apply(matCurrentFrame, fgMaskMOG);
		ptrMOG2->apply(matCurrentFrame, fgMaskMOG2);
        //get the frame number and write it on the current frame
        
        // imshow("Frame", frame);
        //imshow("FG Mask MOG 2", fgMaskMOG2);
        //get the input from the keyboard
        //keyboard = (char)waitKey( 30 );
		
		progress.setPos(frameId);
	}
			
	std::cout << "End of processing at user request." << std::endl;
	
	fullArea.clear(PXL_COLOR_OFF);
	fullArea.render();
	
	cv::Mat source_frame(camera.frameHeight(), camera.frameWidth(), CV_8UC3, currentFrame.bytes), output_fog_masked, output_fog2_masked;
	source_frame.copyTo(output_fog_masked, fgMaskMOG);
	source_frame.copyTo(output_fog2_masked, fgMaskMOG2);
	cv::imwrite("source_frame.png", source_frame);
	cv::imwrite("fog_mask.png", fgMaskMOG);
	cv::imwrite("fog2_mask.png", fgMaskMOG2);
	cv::imwrite("output_fog_masked.png", output_fog_masked);
	cv::imwrite("output_fog2_masked.png", output_fog2_masked);

	std::cout << "Saved images." << std::endl;
		
    return 0;
}
