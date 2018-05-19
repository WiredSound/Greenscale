#pragma once

#include <SFML/Graphics/Font.hpp>
#include "RootGui.h"
#include "../TurnManager.h"

class GameGui : public RootGui {
public:
	GameGui(sf::Vector2f windowSize);
	void setup(TurnManager &turnManager, sf::Font &font, sf::Vector2f childrenScale, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness);
	virtual void update(Input &input) override;

private:
	std::shared_ptr<sf::Texture> componentsTexture;
};