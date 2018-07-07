#include "Camera.h"

Camera::Camera(sf::RenderWindow &win, sf::Transformable &staticGui) : window(win), gui(staticGui), view(win.getView()) {}

void Camera::moveDirectly(sf::Vector2f movement) {
	view.move(movement);
}

void Camera::setCentre(sf::Vector2f centre) {
	view.setCenter(centre);
}

void Camera::update(Input &input) {
	gui.setPosition(sf::Vector2f(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)));
	window.setView(view);
}

void Camera::focusOnPoint(sf::Vector2f centre, float moveSpeed) {
	target = centre;
	speed = moveSpeed;
}