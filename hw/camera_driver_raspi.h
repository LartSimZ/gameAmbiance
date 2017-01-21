#pragma once

#include "raspicam/raspicam.h"
#include "camera_driver_interface.h"

namespace gameAmbiance
{
    namespace hw
    {
		class camera_driver_raspi : public camera_driver_interface
		{
		private:
		raspicam::RaspiCam _camera;

		public:
			camera_driver_raspi();
			~camera_driver_raspi();

			virtual bool init() override;
			virtual void term() override;
			
			virtual bool getFrame(video_frame& frame) override;
		};
	}
}
