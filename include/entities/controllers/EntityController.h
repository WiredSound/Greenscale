#pragma once

#include "../Entity.h"

/*
 * Each Entity is passed an EntityController which dictates what the entity will do each turn.
 */
class EntityController {
public:
	/**
	 * Decides on the given entity's action for this turn.
	 * \return Whether the controller has finished dictating what the entity will do. This method will be called continually by Entity::yourTurnDecision until `true` is returned.
	 */
	virtual bool handle(Entity *entity, Input &input) = 0;
};