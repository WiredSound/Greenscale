#pragma once

#include "EntityController.h"

class FollowEntityController : public EntityController {
public:
	FollowEntityController(std::shared_ptr<Entity> target, unsigned int idealDistance, Console &consoleRef);
	virtual bool handle(Entity *entity, Input &input) override;

private:
	std::weak_ptr<Entity> targetEntity;
	unsigned int idealDistanceFromTarget;
	Console &console;
};