#include "Input.h"

#include <SFML/Window/Mouse.hpp>

Input::Input(sf::RenderWindow &renderWindow) : window(renderWindow) {}

// Returns true if the close event is triggered.
bool Input::update() {
	keysJustPressed.clear();
	mouseButtonsJustPressed.clear();
	miscellaneousEvents.clear();

	sf::Event event;
	window.pollEvent(event);

	switch (event.type) {
	case sf::Event::Closed:
		return true;

	case sf::Event::KeyPressed:
		keysJustPressed.push_back(event.key.code);
		keysHeld.push_back(event.key.code);
		break;

	case sf::Event::KeyReleased:
		std::remove(keysHeld.begin(), keysHeld.end(), event.key.code);
		break;

	case sf::Event::MouseButtonPressed:
		mouseButtonsJustPressed.push_back(event.mouseButton.button);
		break;

	default:
		miscellaneousEvents.push_back(event);
		break;
	}

	return false;
}

bool Input::isKeyJustPressed(sf::Keyboard::Key key) {
	return std::find(keysJustPressed.begin(), keysJustPressed.end(), key) != keysJustPressed.end();
}

bool Input::isKeyHeld(sf::Keyboard::Key key) {
	return std::find(keysHeld.begin(), keysHeld.end(), key) != keysHeld.end();
}

bool Input::isMouseButtonJustPressed(sf::Mouse::Button button) {
	return std::find(mouseButtonsJustPressed.begin(), mouseButtonsJustPressed.end(), button) != mouseButtonsJustPressed.end();
}

sf::Vector2i Input::getMousePosition() {
	return sf::Mouse::getPosition(window);
}

sf::Vector2f Input::getMouseWorldPosition() {
	return window.mapPixelToCoords(getMousePosition());
}

const std::vector<sf::Mouse::Button> &Input::getMouseButtonsJustPressed() {
	return mouseButtonsJustPressed;
}

const std::vector<sf::Event> &Input::getMiscellaneousEvents() {
	return miscellaneousEvents;
}