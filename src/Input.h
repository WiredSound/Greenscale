#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * This class makes it simpler to know which keys and mouse buttons are held and which have been immediately just pressed in addition to event handling.
 * I created the Input class after I realised that SFML provided no easy why to check if a key had pressed just in the last frame. It also provides the position of the mouse relative to the game window
 * which simply calling sf::Mouse::getPosition() does not account for.
 */
class Input {
public:
	Input(sf::RenderWindow &renderWindow);
	bool update();

	bool isKeyJustPressed(sf::Keyboard::Key key);
	bool isKeyHeld(sf::Keyboard::Key key);

	bool isMouseButtonJustPressed(sf::Mouse::Button button);
	bool isMouseButtonHeld(sf::Mouse::Button button);

	const std::vector<sf::Mouse::Button> &getMouseButtonsJustPressed();
	const std::vector<sf::Event> &getMiscellaneousEvents();

	sf::Vector2i getMousePosition();
	sf::Vector2f getMouseWorldPosition();

protected:
	template <typename T>
	bool contains(std::vector<T> vector, T value) {
		return std::find(vector.begin(), vector.end(), value) != vector.end();
	}

private:
	sf::RenderWindow &window;

	std::vector<sf::Keyboard::Key> keysJustPressed;
	std::vector<sf::Keyboard::Key> keysHeld;
	std::vector<sf::Mouse::Button> mouseButtonsJustPressed;
	std::vector<sf::Mouse::Button> mouseButtonsHeld;
	std::vector<sf::Event> miscellaneousEvents;
};