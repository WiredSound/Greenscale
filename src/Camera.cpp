#include "Camera.h"

#include <cmath>

/**
 * Construct a new Camera.
 * \param win The render window for the camera to use.
 * \param staticGui The game GUI so that the camera can ensure that it remains static on the screen.
 */
Camera::Camera(sf::RenderWindow &win, sf::Transformable &staticGui) : window(win), gui(staticGui), view(win.getView()) {}

/**
 * Moves the camera view by the given vector.
 * \param movement Vector to translate the view by.
 */
void Camera::moveDirectly(sf::Vector2f movement) {
	view.move(movement);
}

/**
 * Directly set the centre point for the camera to focus on.
 * \param centre The new centre point.
 */
void Camera::setCentre(sf::Vector2f centre) {
	view.setCenter(centre);
}

/**
 * Updates camera movement and view.
 * Performs the movements required for the camera to move towards the target position (as specified by calling Camera::moveTowardsCentre), sets the render window view and positions the GUI.
 */
void Camera::update(Input &input) {
	if (movementClock.getElapsedTime() >= sf::milliseconds(10)) {
		movementClock.restart();

		sf::Vector2f diff(targetCentre.x - view.getCenter().x, targetCentre.y - view.getCenter().y);

		moveDirectly(sf::Vector2f(std::ceil(diff.x * percentMove), std::ceil(diff.y * percentMove)));
	}

	gui.setPosition(sf::Vector2f(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)));
	window.setView(view);
}

/**
 * Makes the camera over to towards a given centre point at a specific rate.
 * \param centre The centre point for the camera to move towards.
 * \param percent The fraction of the difference between the current point and the target point to move each frame.
 */
void Camera::moveTowardsCentre(sf::Vector2f centre, float percent) {
	targetCentre = centre;
	percentMove = percent;
}
