#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>

class GameSettings {
public:
	bool loadSettings(std::string filename);
	bool writeSettings(std::string filename);

	unsigned int windowWidth;
	unsigned int windowHeight;
	unsigned int fontSize;
	bool vsyncEnabled;
	bool fullscreenEnabled;
	bool displayFps;
	sf::Color guiBackgroundColour;
	sf::Color guiHoverBackgroundColour;
	sf::Color guiBorderColour;
};