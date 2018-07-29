#pragma once

#include <SFML/Graphics/Font.hpp>
#include "GuiWindow.h"
#include "TextLinesGui.h"
#include "../TurnManager.h"

class EntityGui : public GuiWindow {
public:
	EntityGui(Gui &parent, sf::Font &textFont, unsigned int fontSize, TurnManager &manager, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness);

	virtual void update(Input &input) override;

private:
	TurnManager &turnManager;
	sf::Font &font;
	unsigned int entityInfoLines;
	unsigned int nameLine, integrityLine, powerLine, movementRangeLine;

	sf::Color colourBasedOnPercentage(unsigned int integrity, unsigned int maxIntegrity);
};