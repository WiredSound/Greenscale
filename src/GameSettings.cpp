#include "GameSettings.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include "JsonHelp.h"
#include "debugging.h"

// JSON keys:
#define WINDOW_WIDTH "window width"
#define WINDOW_HEIGHT "window height"
#define FONT_SIZE "font size"
#define VSYNC_ENABLED "vsync enabled"
#define FULLSCREEN_ENABLED "fullscreen enabled"
#define DISPLAY_FPS "display fps"
#define GUI_BACKGROUND_COLOUR "gui background colour"
#define GUI_HOVER_BACKGROUND_COLOUR "gui hover background colour"
#define GUI_BORDER_COLOUR "gui border colour"

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
			guiBackgroundColour = JsonHelp::parseColour(json[GUI_BACKGROUND_COLOUR]);
            guiHoverBackgroundColour = JsonHelp::parseColour(json[GUI_HOVER_BACKGROUND_COLOUR]);
            guiBorderColour = JsonHelp::parseColour(json[GUI_BORDER_COLOUR]);

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
		// TODO: Convert colours to JSON.
		//json[GUI_BACKGROUND_COLOUR] = guiBackgroundColour;
		//json[GUI_HOVER_BACKGROUND_COLOUR] = guiHoverBackgroundColour;
		//json[GUI_BORDER_COLOUR] = guiBorderColour;

		file << json;

		file.close();

		return true;
	}

	return false;
}
