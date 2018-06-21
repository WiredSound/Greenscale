#pragma once

#include <string>

class GameSettings {
public:
	bool loadSettings(std::string filename);
	bool writeSettings(std::string filename);

	unsigned int windowWidth = 1728;
	unsigned int windowHeight = 972;
	unsigned int fontSize = 14;
	bool vsyncEnabled = false;
	bool fullscreenEnabled = false;
	bool displayFps = true;
};