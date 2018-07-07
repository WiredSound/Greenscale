#include "Camera.h"

Camera::Camera(sf::RenderWindow &win, sf::Transformable &staticGui) : window(win), gui(staticGui), view(win.getView()) {}

void Camera::moveDirectly(sf::Vector2f movement) {
	view.move(movement);
}

void Camera::setCentre(sf::Vector2f centre) {
	view.setCenter(centre);
}

void Camera::update(Input &input) {
	if (movementClock.getElapsedTime() >= sf::milliseconds(10)) {
		movementClock.restart();

		sf::Vector2f diff(targetCentre.x - view.getCenter().x, targetCentre.y - view.getCenter().y);

		moveDirectly(sf::Vector2f(std::ceil(diff.x * percentMove), std::ceil(diff.y * percentMove)));
	}

	gui.setPosition(sf::Vector2f(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)));
	window.setView(view);
}

void Camera::moveTowardsCentre(sf::Vector2f centre, float percent) {
	targetCentre = centre;
	percentMove = percent;
}