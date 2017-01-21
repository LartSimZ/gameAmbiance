#pragma once

#include "opencv2/videoio.hpp"
#include "camera_driver_interface.h"

namespace gameAmbiance
{
    namespace hw
    {
		class camera_driver_opencv : public camera_driver_interface
		{
		private:
			int _captureIdx;
			cv::VideoCapture _capture;

		public:
			camera_driver_opencv(int captureIdx);
			~camera_driver_opencv();

			virtual bool init() override;
			virtual void term() override;
			
			virtual bool getFrame(video_frame& frame) override;
		};
	}
}
