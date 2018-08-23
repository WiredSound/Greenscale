#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Input {
public:
	Input(sf::RenderWindow &renderWindow);
	bool update();

	bool isKeyJustPressed(sf::Keyboard::Key key);
	bool isKeyHeld(sf::Keyboard::Key key);
	bool isMouseButtonJustPressed(sf::Mouse::Button button);
	const std::vector<sf::Mouse::Button> &getMouseButtonsJustPressed();
	const std::vector<sf::Event> &getMiscellaneousEvents();

	sf::Vector2i getMousePosition();
	sf::Vector2f getMouseWorldPosition();

private:
	sf::RenderWindow &window;

	std::vector<sf::Keyboard::Key> keysJustPressed;
	std::vector<sf::Keyboard::Key> keysHeld;
	std::vector<sf::Mouse::Button> mouseButtonsJustPressed;
	std::vector<sf::Event> miscellaneousEvents;
};