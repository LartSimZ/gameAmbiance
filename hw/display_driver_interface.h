#include "display_pixel_driver_interface.h"

namespace gameAmbiance
{
    namespace hw
    {
        class display_driver_interface : public display_pixel_driver_interface
        {
        public:
            virtual void init() = 0;
            virtual void term() = 0;
        };
    }
}