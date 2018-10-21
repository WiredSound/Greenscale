#include "entities/Robot.h"

Animation::Frame Robot::fetchFrame() {
	if (isDestroyed()) return getDestroyedAnimation()->getFrame(animationClock.getElapsedTime());
	if (reachedPathTarget()) return getIdleAnimation()->getFrame(animationClock.getElapsedTime());
	return getMovingAnimation()->getFrame(animationClock.getElapsedTime());
}

sf::Color Robot::getColour() {
	return (isMyTurn() ? myTurnColourPulse.getColour(faction.colour) : faction.colour);
}

std::shared_ptr<Animation> Robot::getIdleAnimation() {
	return getAnimation("idle");
}
std::shared_ptr<Animation> Robot::getMovingAnimation() {
	return getAnimation("moving");
}

std::shared_ptr<Animation> Robot::getDestroyedAnimation() {
	return getAnimation("destroyed");
}
