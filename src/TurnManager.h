#pragma once

#include <memory>
#include "entities/Faction.h"
#include "map/GameMap.h"
#include "entities/Entity.h"
#include "Input.h"

class TurnManager {
public:
	void update(Input &input, std::unique_ptr<GameMap> &map);
	std::shared_ptr<Entity> &getCurrentEntity();
	const std::vector<std::shared_ptr<Entity>> &getCurrentEntities();

private:
	std::vector<std::shared_ptr<Entity>> currentEntities; // The current entities being updated in order of first to last priority.
	int index;

	bool decisionMade; // Whether the current entity has decide upon what they will do this turn.

	void fetchOrderedEntities(std::unique_ptr<GameMap> &map);
	void nextEntity(std::unique_ptr<GameMap> &map);
};