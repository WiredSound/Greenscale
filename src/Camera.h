#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Input.h"

class Camera {
public:
	Camera(sf::RenderWindow &win, sf::Transformable &staticGui);
	void update(Input &input);
	void moveDirectly(sf::Vector2f movement);
	void setCentre(sf::Vector2f centre);
	void focusOnPoint(sf::Vector2f centre, float moveSpeed);

private:
	sf::View view;
	sf::Vector2f target;
	float speed;
	sf::RenderWindow &window;
	sf::Transformable &gui;
};