#pragma once

#include "Entity.h"

/**
 * Robots are defined as a specific type entity with the three animation states: idle, moving and destroyed.
 * The colour of a robot pulses when it is their turn but is the colour of their faction otherwise.
 */
class Robot : public Entity {
public:
	using Entity::Entity; // Use the same constructor as the Entity class.
	virtual Animation::Frame fetchFrame() override;
	virtual sf::Color getColour() override;

protected:
	std::shared_ptr<Animation> getIdleAnimation();
	std::shared_ptr<Animation> getMovingAnimation();
	std::shared_ptr<Animation> getDestroyedAnimation();
};