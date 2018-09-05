#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow &renderWindow, sf::Font &font) : State(renderWindow), gui((sf::Vector2f) renderWindow.getSize()) {
	gui.setup(font, 16);
}

void MainMenuState::update(Input &input) {
	gui.update(input);
}

void MainMenuState::draw() {
	window.draw(gui);
}