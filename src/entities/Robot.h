#pragma once

#include "Entity.h"
#include "../components/Weapon.h"

class Robot : public Entity {
public:
	using Entity::Entity;
	virtual Animation::Frame fetchFrame() override;
	virtual sf::Color getColour() override;

protected:
	std::shared_ptr<Animation> getIdleAnimation();
	std::shared_ptr<Animation> getMovingAnimation();
	std::shared_ptr<Animation> getDestroyedAnimation();
};