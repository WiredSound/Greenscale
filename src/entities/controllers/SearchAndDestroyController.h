#pragma once

#include "EntityController.h"

class SearchAndDestroyController : public EntityController {
public:
	SearchAndDestroyController(std::shared_ptr<Entity> target);
	SearchAndDestroyController(Faction target);

	virtual bool handle(Entity *entity, Input &input) override;

	Optional<std::shared_ptr<Entity>> findMostAppropriateTarget(Entity *entity);

private:
	bool targetingIndividual; // Whether to target a specific entity or any entity of a specific faction.
	std::weak_ptr<Entity> targetEntity;
	Faction targetFaction;
};