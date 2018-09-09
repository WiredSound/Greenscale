#pragma once

#include <SFML/Graphics/Font.hpp>
#include "RootGui.h"
#include "ConsoleGui.h"
#include "../FpsCounter.h"
#include "../entities/controllers/PlayerController.h"
class TurnManager;

class GameGui : public RootGui {
public:
	GameGui(sf::Vector2f windowSize);
	void load(TurnManager &turnManager, std::shared_ptr<PlayerController> playerController,
		sf::Font &font, unsigned int fontSize, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness);
	virtual void update(Input &input) override;

	ConsoleGui *getConsoleGui();

private:
	FpsCounter fps;
	std::shared_ptr<sf::Texture> componentsTexture;
	unsigned int consoleGuiIndex, fpsGuiIndex;
};