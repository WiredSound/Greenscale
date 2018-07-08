#pragma once

#include <SFML/Graphics/Font.hpp>
#include "RootGui.h"
#include "ConsoleGui.h"
class TurnManager;

class GameGui : public RootGui {
public:
	GameGui(sf::Vector2f windowSize);
	void setup(TurnManager &turnManager, sf::Font &font, unsigned int fontSize, sf::Vector2f childrenScale,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness);
	virtual void update(Input &input) override;

	void displayConsoleMessage(ConsoleGui::Message message, bool prependMessageType = false);

private:
	std::shared_ptr<sf::Texture> componentsTexture;
	unsigned int consoleGuiIndex;
};