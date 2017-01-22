#pragma once

#define UI_KEY_ESCAPE		27

namespace gameAmbiance
{
    namespace ui
    {
       class keyboard
        {
        public:
			static bool inputAvailable();
			static int readKey();
        };
    }
}