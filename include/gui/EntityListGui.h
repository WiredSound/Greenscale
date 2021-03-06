#pragma once

#include "TextLinesGui.h"
#include "GuiWindow.h"
#include "../TurnManager.h"

class EntityListGui : public GuiWindow {
public:
	EntityListGui(Gui &parent, TurnManager &managerTurns, sf::Font &textFont, unsigned int textSize, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness);

	virtual void update(Input &input) override;

private:
	TurnManager &turnManager; // Turn manager belonging to the game state.
	unsigned int textLines;
};