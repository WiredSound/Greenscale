#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow &renderWindow, sf::Font &font, GameSettings &settings) : State(renderWindow), gui((sf::Vector2f) renderWindow.getSize())
{
	gui.setup(font, settings.fontSize, settings.guiBackgroundColour, settings.guiHoverBackgroundColour, settings.guiBorderColour, 2.0f);
}

void MainMenuState::update(Input &input) {
	gui.update(input);
}

void MainMenuState::draw() {
	window.draw(gui);
}