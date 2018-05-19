#pragma once

#include <SFML/Graphics/Text.hpp>
#include "GuiWindow.h"
#include "../TurnManager.h"

class EntityListGui : public GuiWindow {
public:
	EntityListGui(Gui &parent, TurnManager &managerTurns, sf::Font &textFont, unsigned int sizeText, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness);

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	TurnManager &turnManager; // Turn manager belonging to the game state.
	std::vector<sf::Text> lines;
	sf::Font &font;
	unsigned int textSize;
};