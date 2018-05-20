#include "Robot.h"

Robot::Robot(std::string entityName, sf::Vector2u pos, sf::Vector2u componentGridSize, std::shared_ptr<EntityController> entityController, Faction entityFaction, int integrityMax,
	std::shared_ptr<Animation> animationIdle, std::shared_ptr<Animation> animationMoving)
	: Entity(entityName, pos, entityFaction, integrityMax, componentGridSize, entityController), idleAnimation(animationIdle), movingAnimation(animationMoving) {}

Animation::Frame Robot::fetchFrame() {
	if (reachedPathTarget())
		return idleAnimation->getFrame(animationClock.getElapsedTime());
	else
		return movingAnimation->getFrame(animationClock.getElapsedTime());
}

sf::Color Robot::getColour() {
	return (isMyTurn() ? MY_TURN_COLOUR : faction.colour);
}

bool Robot::updateAttacking() {
	// TODO...
	return true;
}