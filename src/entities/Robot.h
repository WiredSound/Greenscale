#pragma once

#include "Entity.h"
#include "../components/Weapon.h"

class Robot : public Entity {
public:
	Robot(std::string entityName, sf::Vector2u pos, sf::Vector2u componentGridSize, std::shared_ptr<EntityController> entityController, Faction entityFaction, int integrityMax,
		std::shared_ptr<Animation> animationIdle, std::shared_ptr<Animation> animationMoving);
	virtual Animation::Frame fetchFrame() override;
	virtual sf::Color getColour() override;
	virtual bool updateAttacking() override;

private:
	std::shared_ptr<Animation> idleAnimation;
	std::shared_ptr<Animation> movingAnimation;
};