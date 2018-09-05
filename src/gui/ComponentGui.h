#pragma once

#include <SFML/Graphics/Font.hpp>
#include "ComponentGridGui.h"
#include "TextLinesGui.h"

class ComponentGui : public GuiWindow {
public:
	ComponentGui(Gui &parent, ComponentGridGui &componentGridGui, sf::Font &textFont, unsigned int fontSize, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness);

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	ComponentGridGui &gridGui;
	sf::Font &font;
	unsigned int textSize;

	unsigned int linesIndex;
	unsigned int nameLineIndex, descriptionLineIndex;

	sf::Color okTextColour;
	sf::Color warningTextColour;
	sf::Color badTextColour;

	TextWrapper wrapper;

	std::pair<std::string, sf::Color> getHeatLevelColourText(Component &component);
	sf::Color colourBasedOnSign(int value, sf::Color positiveColour, sf::Color zeroColour, sf::Color negativeColour);
};