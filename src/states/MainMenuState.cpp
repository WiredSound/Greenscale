#include "states/MainMenuState.h"

MainMenuState::MainMenuState(StateManager &manager, sf::RenderWindow &renderWindow, sf::Font &textFont, GameSettings &gameSettings)
	: State("Main Menu", manager, renderWindow), gui((sf::Vector2f) renderWindow.getSize()), font(textFont), settings(gameSettings)
{
	gui.load(font, settings.fontSize, settings.guiBackgroundColour, settings.guiHoverBackgroundColour, settings.guiBorderColour, 2.0f,
		manager, window, settings);
}

void MainMenuState::update(Input &input) {
	gui.update(input);
}

void MainMenuState::draw() {
	window.clear(sf::Color(0, 180, 0, 255));
	window.draw(gui);
}
