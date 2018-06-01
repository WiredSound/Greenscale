#pragma once

#include <SFML/Graphics/Font.hpp>
#include "ComponentGridGui.h"
#include "TextLines.h"

class ComponentGui : public GuiWindow {
public:
	ComponentGui(Gui &parent, ComponentGridGui &componentGridGui, sf::Font &textFont, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness, unsigned int fontSize);

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	ComponentGridGui &gridGui;
	sf::Font &font;

	unsigned int propertyNameLines, propertyValueLines;
	unsigned int nameLine, descriptionLine, integrityLine, heatLevelLine, passivePowerLine, usePowerLine;

	sf::Color okTextColour;
	sf::Color warningTextColour;
	sf::Color badTextColour;

	std::pair<std::string, sf::Color> getHeatLevelColourText(Component &component);
	sf::Color colourBasedOnSign(int value, sf::Color positiveColour, sf::Color zeroColour, sf::Color negativeColour);
};