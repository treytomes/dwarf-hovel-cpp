#pragma once

#include <string>

#include "Logger.h"
#include "Point2UI.h"

class Settings {
public:
	static void initialize();
	static void shutdown();
	static Settings* get_instance();

	LogLevel log_level;
	std::string window_title;
	Point2UI virtual_window_size;
	Point2UI actual_window_size;

private:
	Settings();
	~Settings();

	static Settings* instance;
};