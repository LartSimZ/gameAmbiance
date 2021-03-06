#include "keyboard.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <iostream>

namespace gameAmbiance
{
    namespace ui
    {
		bool keyboard::inputAvailable()
		{
			struct timeval tv;
			fd_set fds;
			tv.tv_sec = 0;
			tv.tv_usec = 0;
			FD_ZERO(&fds);
			FD_SET(STDIN_FILENO, &fds);
			select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
			return (FD_ISSET(0, &fds));
		}
		
		int keyboard::readKey()
		{
			return std::cin.get();
		}
    }
}