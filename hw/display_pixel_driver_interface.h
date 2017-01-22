#pragma once

#include "../base/type_defs.h"

namespace gameAmbiance
{
    namespace hw
    {
        #define     PXL_COLOR_ON    		0x00FFFFFF
        #define     PXL_COLOR_OFF   		0x00000000
		#define		PXL_COLOR_TRANSPARENT	0x80000000
		#define		PXL_COLOR_INVERT		0xFF000000

        class display_pixel_driver_interface
        {
        public:
            virtual void clear(uint32_t color) = 0;
			virtual uint32_t getPixel(int32_t x, int32_t y) const = 0;
            virtual void setPixel(int32_t x, int32_t y, uint32_t color) = 0;
            virtual void render() = 0;
        };
    }
}