#include "ComponentGui.h"

ComponentGui::ComponentGui(Gui &parent, sf::Font &textFont, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Components", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness), font(textFont) {}