#include "camera_driver_raspi.h"

namespace gameAmbiance
{
    namespace hw
    {
		camera_driver_raspi::camera_driver_raspi()
		{
		}
		
		camera_driver_raspi::~camera_driver_raspi()
		{
			term();
		}

		bool camera_driver_raspi::init()
		{
			return _camera.open();
		}
		
		void camera_driver_raspi::term()
		{
			_camera.release();
		}
		
		bool camera_driver_raspi::getFrame(video_frame& frame)
		{
			if(!frame.alloc( _camera.getImageTypeSize(_camera.getFormat()) ))
			{
				return false;
			}
			
			_camera.retrieve(frame.bytes);
			return true;
		}
    }
}