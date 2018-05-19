#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Input.h"

class State {
public:
	State(sf::RenderWindow &renderWindow) : window(renderWindow) {};
	virtual void update(Input &input) = 0;
	virtual void draw() = 0;

protected:
	sf::RenderWindow &window;
};