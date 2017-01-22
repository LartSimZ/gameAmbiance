#include "camera_driver_opencv.h"

namespace gameAmbiance
{
    namespace hw
    {
		camera_driver_opencv::camera_driver_opencv(int captureIdx)
		: _captureIdx(captureIdx)
		{
		}
		
		camera_driver_opencv::~camera_driver_opencv()
		{
			term();
		}

		bool camera_driver_opencv::init()
		{
			_capture.open(_captureIdx);
			return _capture.isOpened();
		}
		
		void camera_driver_opencv::term()
		{
			_capture.release();
		}
		
		uint32_t camera_driver_opencv::frameWidth() const
		{
			return 0;
		}
		
		uint32_t camera_driver_opencv::frameHeight() const
		{
			return 0;
		}
		
		bool camera_driver_opencv::readFrame(video_frame& frame)
		{
			return false;
		}
    }
}