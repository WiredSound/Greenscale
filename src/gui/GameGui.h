#pragma once

#include <SFML/Graphics/Font.hpp>
#include "RootGui.h"
#include "ConsoleGui.h"
class TurnManager;

class GameGui : public RootGui {
public:
	GameGui(sf::Vector2f windowSize);
	void load(TurnManager &turnManager, sf::Font &font, unsigned int fontSize,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness);
	virtual void update(Input &input) override;

	ConsoleGui *getConsoleGui();

private:
	std::shared_ptr<sf::Texture> componentsTexture;
	unsigned int consoleGuiIndex;
};