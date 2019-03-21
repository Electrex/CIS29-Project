#pragma once
#include <string>
#include <stdio.h>

namespace notify {
	class NotificationWindow
	{
	public:
		NotificationWindow(const std::string message, const std::string buttonText, const char * image, const char * button);
		~NotificationWindow();
	};

}