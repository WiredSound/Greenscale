#pragma once

#include <SFML/Graphics/Font.hpp>
#include "RootGui.h"

class MainMenuGui : public RootGui {
public:
	MainMenuGui(sf::Vector2f size);
	void setup(sf::Font &font, unsigned int fontSize);
};