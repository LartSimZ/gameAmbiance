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
		
		uint32_t camera_driver_raspi::frameWidth() const
		{
			return _camera.getWidth();
		}
		
		uint32_t camera_driver_raspi::frameHeight() const
		{
			return _camera.getHeight();
		}
		
		bool camera_driver_raspi::readFrame(video_frame& frame)
		{
			if(!_camera.grab())
			{
				return false;
			}
			
			if(!frame.alloc( _camera.getImageTypeSize(_camera.getFormat()) ))
			{
				return false;
			}
			
			_camera.retrieve(frame.bytes);
			return true;
		}
    }
}