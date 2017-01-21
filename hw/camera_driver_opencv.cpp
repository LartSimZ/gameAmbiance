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
		
		bool camera_driver_opencv::getFrame(video_frame& frame)
		{
			return false;
		}
    }
}