#include "gui/MainMenuGui.h"

#include "gui/GuiTextButton.h"
#include "states/GameState.h"

MainMenuGui::MainMenuGui(sf::Vector2f size) : RootGui("Main Menu", sf::Vector2f(0, 0), size) {}

void MainMenuGui::load(sf::Font &font, unsigned int fontSize, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness,
	StateManager &stateManager, sf::RenderWindow &window, GameSettings &settings) {
	destroyAllChildren();

	GuiButton::CallbackType playCallback = [&](Input &in) {
		stateManager.changeState(std::make_unique<GameState>(stateManager, window, font, settings));
	};

	GuiButton::CallbackType exitCallback = [&stateManager](Input &in) {
		stateManager.exit();
	};

	addChild(std::make_unique<GuiTextButton>("New Game Button", *this, sf::Vector2f(0.5f, 0.4f), sf::Vector2f(0.15f, 0.05f), sf::Vector2f(0.5f, 0.5f),
		backgroundColour, hoverBackgroundColour, sf::Color::Blue, borderColour, 3.0f, font, settings.fontSize, "New Game", playCallback));

	addChild(std::make_unique<GuiTextButton>("Exit Button", *this, sf::Vector2f(0.5f, 0.48f), sf::Vector2f(0.15f, 0.05f), sf::Vector2f(0.5f, 0.5f),
		backgroundColour, hoverBackgroundColour, sf::Color::Blue, borderColour, 3.0f, font, settings.fontSize, "Exit", exitCallback));
}
