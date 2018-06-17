#pragma once

#include "Entity.h"

// TODO: Do not share entity controllers as that means they cannot save state and are pretty rubbish. Each entity should have a unique pointer to its own controller.

class EntityController {
public:
	virtual bool handle(Entity *entity, Input &input) = 0;

	//virtual bool handleMovement(Entity *entity, Input &input) = 0; // Returns true when it has completed - this allows player controlled entities to wait for user input.
	//virtual bool handleAttacking(Entity *entity, Input &input) { return true; }; // Implementing combat is optional to allow for neutral non-combat robots.
};