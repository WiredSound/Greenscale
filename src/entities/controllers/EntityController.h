#pragma once

#include "../Entity.h"

/*
 * Each Entity is passed an EntityController which can dictate what the entity will do. An EntityController has one pure virtual method handle(Entity*, Input&) which should be overriden.
 * The handle method should return true when it has completed its role of ordering the entity. If the method returns false then it will immediately be called again next frame until true is
 * returned. This is so that controllers that rely on and wait for user input can be implemented (such as PlayerController).
 */

class EntityController {
public:
	virtual bool handle(Entity *entity, Input &input) = 0;

	//virtual bool handleMovement(Entity *entity, Input &input) = 0; // Returns true when it has completed - this allows player controlled entities to wait for user input.
	//virtual bool handleAttacking(Entity *entity, Input &input) { return true; }; // Implementing combat is optional to allow for neutral non-combat robots.
};