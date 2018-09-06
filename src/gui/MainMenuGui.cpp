#include "MainMenuGui.h"

#include "GuiTextButton.h"
#include "../states/GameState.h"

MainMenuGui::MainMenuGui(sf::Vector2f size) : RootGui("Main Menu", sf::Vector2f(0, 0), size) {}

void MainMenuGui::load(sf::Font &font, unsigned int fontSize, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness,
	StateManager &stateManager, sf::RenderWindow &window, GameSettings &settings) {
	destroyAllChildren();

	GuiButton::CallbackType playCallback = [&stateManager, &window, &font, &settings](Input &in) {
		stateManager.changeState(std::make_unique<GameState>(stateManager, window, font, settings));
	};

	addChild(std::make_unique<GuiTextButton>("Play", *this, sf::Vector2f(0.5f, 0.4f), sf::Vector2f(0.15f, 0.05f), sf::Vector2f(0.5f, 0.5f),
		backgroundColour, hoverBackgroundColour, sf::Color::Blue, borderColour, 3.0f, playCallback, font, settings.fontSize, "New Game"));
}