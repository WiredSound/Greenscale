#include "Input.h"

#include <SFML/Window/Mouse.hpp>

Input::Input(sf::RenderWindow &renderWindow) : window(renderWindow) {}

//! \return Returns true if the close event is triggered.
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
		mouseButtonsHeld.push_back(event.mouseButton.button);
		break;

	case sf::Event::MouseButtonReleased:
		std::remove(mouseButtonsHeld.begin(), mouseButtonsHeld.end(), event.mouseButton.button);
		break;

	default:
		miscellaneousEvents.push_back(event);
		break;
	}

	return false;
}

/**
 * Check whether the specified key was pressed in the last frame.
 * \param key The key to test for.
 * \return Whether the key was indeed pressed or not.
 */
bool Input::isKeyJustPressed(sf::Keyboard::Key key) {
	return contains<sf::Keyboard::Key>(keysJustPressed, key);
}
/**
* Check whether the specified key is being held down. Will continuely output `true` until the key is released.
* \param key The key to test for.
* \return Whether the key is being held.
*/
bool Input::isKeyHeld(sf::Keyboard::Key key) {
	return contains<sf::Keyboard::Key>(keysHeld, key);
}
/**
* Check whether the specified mouse button was pressed in the last frame.
* \param button The mouse button to test for.
* \return Whether the mouse button was indeed pressed or not.
*/
bool Input::isMouseButtonJustPressed(sf::Mouse::Button button) {
	return contains<sf::Mouse::Button>(mouseButtonsJustPressed, button);
}
/**
* Check whether the specified mouse button is being held down. Will continuely output `true` until the mouse button is released.
* \param key The mouse button to test for.
* \return Whether the mouse button is being held.
*/
bool Input::isMouseButtonHeld(sf::Mouse::Button button) {
	return contains<sf::Mouse::Button>(mouseButtonsHeld, button);
}

/**
 * Fetch the position of the mouse within the game window.
 * \return Mouse position.
 */
sf::Vector2i Input::getMousePosition() {
	return sf::Mouse::getPosition(window);
}

/**
 * Get the mouse position but as coordinates within world space rather than its position on the window.
 * \return Mouse position.
 */
sf::Vector2f Input::getMouseWorldPosition() {
	return window.mapPixelToCoords(getMousePosition());
}

const std::vector<sf::Mouse::Button> &Input::getMouseButtonsJustPressed() {
	return mouseButtonsJustPressed;
}

const std::vector<sf::Event> &Input::getMiscellaneousEvents() {
	return miscellaneousEvents;
}