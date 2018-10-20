#pragma once

#include <SFML/Graphics/Font.hpp>
#include "RootGui.h"
#include "../GameSettings.h"
#include "../states/StateManager.h"

class MainMenuGui : public RootGui {
public:
	MainMenuGui(sf::Vector2f size);
	void load(sf::Font &font, unsigned int fontSize, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness,
		StateManager &stateManager, sf::RenderWindow &window, GameSettings &settings);
};