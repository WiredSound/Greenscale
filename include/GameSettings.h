#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>

class GameSettings {
public:
	bool loadSettings(std::string filename);
	bool writeSettings(std::string filename);

	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 720;
	unsigned int fontSize = 14;
	bool vsyncEnabled = false;
	bool fullscreenEnabled = false;
	bool displayFps = true;
	sf::Color guiBackgroundColour = sf::Color(5, 5, 5, 200);
	sf::Color guiHoverBackgroundColour = sf::Color(5, 5, 5, 230);
	sf::Color guiBorderColour = sf::Color(35, 140, 35, 255);
};
