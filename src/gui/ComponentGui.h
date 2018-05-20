#pragma once

#include <SFML/Graphics/Font.hpp>
#include "GuiWindow.h"

class ComponentGui : public GuiWindow {
public:
	ComponentGui(Gui &parent, sf::Font &textFont, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness);

private:
	sf::Font &font;
};