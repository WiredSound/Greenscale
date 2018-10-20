#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateManager.h"
#include "../Input.h"

/**
 * The main program is based around a state machine so that distinct parts of the game (such as the main menu, the game itself, the options menu, etc) are seperated and can be switched
 * between. All states must override the pure virtual methods in the State class below. These states also hold a reference to the SFML render window for drawing and input handling.
 */
class State {
public:
	State(std::string stateName, StateManager &stateManager, sf::RenderWindow &renderWindow)
		: name(stateName), manager(stateManager), window(renderWindow) {};
	virtual void update(Input &input) = 0; //! Where all game logic takes place.
	virtual void draw() = 0; //! Where rendering takes place.

	const std::string name;

protected:
	StateManager &manager;
	sf::RenderWindow &window;
};