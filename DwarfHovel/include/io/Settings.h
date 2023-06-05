#pragma once

#include <string>

#include "io/Logger.h"
#include "math/math.h"

class Settings {
public:
	static void initialize();
	static void shutdown();
	static Settings* get_instance();

	LogLevel log_level;
	std::string window_title;
	VectorUI virtual_window_size;
	VectorUI actual_window_size;

private:
	Settings();
	~Settings();

	static Settings* instance;
};