#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow &renderWindow) : State(renderWindow), gui((sf::Vector2f) renderWindow.getSize()) {}

void MainMenuState::update(Input &input) {
	gui.update(input);
}

void MainMenuState::draw() {
	window.draw(gui);
}