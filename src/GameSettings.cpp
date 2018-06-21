#include "GameSettings.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include "debugging.h"

// JSON keys:
#define WINDOW_WIDTH "window width"
#define WINDOW_HEIGHT "window height"
#define FONT_SIZE "font size"
#define VSYNC_ENABLED "vsync enabled"
#define FULLSCREEN_ENABLED "fullscreen enabled"
#define DISPLAY_FPS "display fps"

bool GameSettings::loadSettings(std::string filename) {
	nlohmann::json json;
	std::ifstream file(filename);

	if (file.is_open()) {
		try {
			file >> json;

			windowWidth = json[WINDOW_WIDTH].get<unsigned int>();
			windowHeight = json[WINDOW_HEIGHT].get<unsigned int>();
			fontSize = json[FONT_SIZE].get<unsigned int>();
			vsyncEnabled = json[VSYNC_ENABLED].get<bool>();
			fullscreenEnabled = json[FULLSCREEN_ENABLED].get<bool>();
			displayFps = json[DISPLAY_FPS].get<bool>();

			file.close();

			return true;
		}
		catch (nlohmann::json::type_error &e) {
			DEBUG_LOG_ERROR("Failed to load settings file due to type error: " << e.what() << "\nException ID: " << e.id);
		}
		catch (nlohmann::json::parse_error &e) {
			DEBUG_LOG_ERROR("Failed to load settings file due to parse error: " << e.what() << "\nException ID: " << e.id << "\nAt byte: " << e.byte);
		}
	}

	return false;
}

bool GameSettings::writeSettings(std::string filename) {
	nlohmann::json json;
	std::ofstream file(filename);

	if (file.is_open()) {
		json[WINDOW_WIDTH] = windowWidth;
		json[WINDOW_HEIGHT] = windowHeight;
		json[FONT_SIZE] = fontSize;
		json[VSYNC_ENABLED] = vsyncEnabled;
		json[FULLSCREEN_ENABLED] = fullscreenEnabled;
		json[DISPLAY_FPS] = displayFps;

		file << json;

		file.close();

		return true;
	}

	return false;
}