#include "Settings.h"

#include <fstream>
#include "json.h"
using json = nlohmann::json;

Settings::Settings() {
	std::ifstream f("settings.json");
	json data = json::parse(f);

	log_level = from_string(data["log_level"]);
	window_title = data["window_title"];
	virtual_window_size = Point2UI(
		data["virtual_window_size"]["x"],
		data["virtual_window_size"]["y"]
	);
	actual_window_size = Point2UI(
		data["actual_window_size"]["x"],
		data["actual_window_size"]["y"]
	);
}

Settings::~Settings() {
	// Save settings back to file.
	json data = {
		{ "log_level", to_string(log_level) },
		{ "window_title", window_title },
		{ "virtual_window_size", {
			{ "x", virtual_window_size.x },
			{ "y", virtual_window_size.y },
		}, },
		{ "actual_window_size", {
			{ "x", actual_window_size.x },
			{ "y", actual_window_size.y },
		}, },
	};

	std::ofstream f("settings.json");
	f << data.dump(4) << std::endl;
	f.flush();
	f.close();
}

Settings* Settings::instance = nullptr;

void Settings::initialize() {
	if (instance != nullptr) {
		shutdown();
	}
	instance = new Settings();
}

void Settings::shutdown() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

Settings* Settings::get_instance() {
	return instance;
}