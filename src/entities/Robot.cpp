#include "Robot.h"

Animation::Frame Robot::fetchFrame() {
	if (reachedPathTarget())
		return getIdleAnimation()->getFrame(animationClock.getElapsedTime());
	else
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