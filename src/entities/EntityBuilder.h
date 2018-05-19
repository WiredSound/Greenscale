#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Robot.h"
#include "../JsonHelp.h"
#include "../debugging.h"

class EntityBuilder {
public:
	void loadAllAnimations(const std::string filename);
	Robot buildSimpleRobot(sf::Vector2u position, std::shared_ptr<EntityController> controller, Faction faction);

private:
	std::shared_ptr<Animation> robotIdleAnimation;
	std::shared_ptr<Animation> robotMovingAnimation;

	Animation loadAnimation(nlohmann::json &animationsJson, const std::string animationName);
};