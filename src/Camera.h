#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Input.h"

/**
 * Handles the movement of the view around the game world.
 * The Camera class is tasked with handling changes to the render window's sf::View instance in order to move the camera around the world
 * space. It also handles smoothly moving the view to a target point in space (via the `moveTowardsCentre` method) as well as ensuring the
 * GUI remains static. It has `update` method which should be called every frame.
 */
class Camera {
public:
	Camera(sf::RenderWindow &win, sf::Transformable &staticGui);
	void update(Input &input);
	void moveDirectly(sf::Vector2f movement);
	void setCentre(sf::Vector2f centre);
	void moveTowardsCentre(sf::Vector2f centre, float percent);

private:
	sf::View view;
	sf::RenderWindow &window;
	sf::Transformable &gui;

	sf::Vector2f targetCentre;
	float percentMove;
	sf::Clock movementClock;
};