#pragma once

#include "EntityController.h"

class SpawnerController : public EntityController {
public:
	virtual bool handle(Entity *entity, Input &input) override;
};