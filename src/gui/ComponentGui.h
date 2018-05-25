#pragma once

#include <SFML/Graphics/Font.hpp>
#include "ComponentGridGui.h"
#include "TextLine.h"

class ComponentGui : public GuiWindow {
public:
	ComponentGui(Gui &parent, ComponentGridGui &componentGridGui, sf::Font &textFont, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness);

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	ComponentGridGui &gridGui;
	sf::Font &font;
	TextLine line;
};