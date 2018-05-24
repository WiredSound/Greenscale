#include "GameState.h"

#include <ctime>

GameState::GameState(sf::RenderWindow &renderWindow, sf::Font &textFont)
	: State(renderWindow), turnManager(map), gui((sf::Vector2f) renderWindow.getSize()), mapBuilder(time(0), renderWindow, gui), font(textFont) {
	map = mapBuilder.buildMap(sf::Vector2u(50, 50), sf::Vector2f(64, 64));
	map->construct();

	gui.setup(turnManager, font, sf::Vector2f(1, 1), sf::Color(5, 5, 5, 200), sf::Color(5, 5, 5, 230), sf::Color(35, 140, 35, 255), 2);
}

void GameState::update(Input &input) {
	map->update();
	turnManager.update(input);
	gui.update(input);

	for (sf::Event event : input.getMiscellaneousEvents()) {
		if (event.type == sf::Event::Resized) {
			gui.resize((sf::Vector2f) window.getSize());
		}
	}
}

void GameState::draw() {
	map->draw(window);
	window.draw(gui);
}