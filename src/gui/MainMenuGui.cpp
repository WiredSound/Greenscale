#include "MainMenuGui.h"

#include "GuiButton.h"
#include "../states/GameState.h"

MainMenuGui::MainMenuGui(sf::Vector2f size) : RootGui("Main Menu", sf::Vector2f(0, 0), size) {}

void MainMenuGui::load(sf::Font &font, unsigned int fontSize, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness,
	StateManager &stateManager, sf::RenderWindow &window, GameSettings &settings) {
	destroyAllChildren();

	GuiButton::CallbackType playCallback = [&stateManager, &window, &font, &settings](Input &in) {
		stateManager.changeState(std::make_unique<GameState>(stateManager, window, font, settings));
	};

	addChild(std::make_unique<GuiButton>("Play", *this, sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.25f, 0.25f), sf::Vector2f(0.5f, 0.5f),
		backgroundColour, hoverBackgroundColour, sf::Color::Blue, borderColour, 3.0f, playCallback));
}