#include "states/GameState.h"

GameState::GameState(StateManager &manager, sf::RenderWindow &renderWindow, sf::Font &textFont, GameSettings &gameSettings)
	: State("Game", manager, renderWindow), gui((sf::Vector2f) renderWindow.getSize()), font(textFont), settings(gameSettings), camera(renderWindow, gui)
{
	gui.load(world.getTurnManager(), playerController, font, settings.fontSize, settings.guiBackgroundColour, settings.guiHoverBackgroundColour, settings.guiBorderColour, 2.0f);
	console.setConsoleGui(gui.getConsoleGui());
}

void GameState::update(Input &input) {
	world.update(input);
	gui.update(input);
	camera.update(input);
}

void GameState::draw() {
	world.draw(window);
	window.draw(gui);
}
