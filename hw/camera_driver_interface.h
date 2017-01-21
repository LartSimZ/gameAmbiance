#pragma once

#include "../base/type_defs.h"

namespace gameAmbiance
{
    namespace hw
    {
		struct video_frame
		{
			video_frame()
			: bytes(NULL)
			, byteSize(0)
			{
			}
			
			~video_frame()
			{
				free();
			}
			
			bool alloc(size_t newSize)
			{
				free();
				
				if(newSize > 0)
				{
					try
					{
						bytes = new uint8_t[newSize];
						byteSize = newSize;
					}
					catch(std::bad_alloc& e)
					{
						bytes = NULL;
						byteSize = 0;
						
						return false;
					}
				}
				
				return true;
			}
			
			void free()
			{
				if(bytes != NULL)
				{
					delete [] bytes;
					bytes = NULL;
				}
			}
			
			uint8_t* bytes;
			uint32_t byteSize;
		};
		
		class camera_driver_interface
		{
		public:
			virtual bool init() = 0;
			virtual void term() = 0;
			
			virtual bool getFrame(video_frame& frame) = 0;
		};
	}
}
