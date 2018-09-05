#include "GameState.h"

GameState::GameState(sf::RenderWindow &renderWindow, sf::Font &textFont, GameSettings &gameSettings)
	: State(renderWindow), gui((sf::Vector2f) renderWindow.getSize()), font(textFont), settings(gameSettings), camera(renderWindow, gui),
	world(camera, std::make_shared<PlayerController>(gui, console, camera), console, sf::Vector2f(32, 32))
{
	gui.setup(world.getTurnManager(), font, settings.fontSize, settings.guiBackgroundColour, settings.guiHoverBackgroundColour, settings.guiBorderColour, 2.0f);
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