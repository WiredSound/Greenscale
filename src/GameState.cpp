#include "GameState.h"

#include <ctime>

GameState::GameState(sf::RenderWindow &renderWindow, sf::Font &textFont, GameSettings &gameSettings)
	: State(renderWindow), turnManager(map), gui((sf::Vector2f) renderWindow.getSize()), font(textFont), settings(gameSettings) {
	MapBuilder mapBuilder(static_cast<unsigned int>(time(0)), renderWindow, gui);

	map = mapBuilder.buildMap(sf::Vector2u(50, 50), sf::Vector2f(32, 32));
	map->construct();

	gui.setup(turnManager, font, settings.fontSize, sf::Vector2f(1, 1), sf::Color(5, 5, 5, 200), sf::Color(5, 5, 5, 230), sf::Color(35, 140, 35, 255), 2);
}

void GameState::update(Input &input) {
	map->update();
	turnManager.update(input);
	gui.update(input);

	if (input.isKeyJustPressed(sf::Keyboard::Key::S))
		map->save("M:/Visual Studio Projects/Greenscale/test");
	if (input.isKeyJustPressed(sf::Keyboard::Key::L))
		map->load("M:/Visual Studio Projects/Greenscale/test");

	for (sf::Event event : input.getMiscellaneousEvents()) {
		//if (event.type == sf::Event::Resized) gui.resize((sf::Vector2f) window.getSize());
	}
}

void GameState::draw() {
	map->draw(window);
	window.draw(gui);
}