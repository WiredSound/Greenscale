#pragma once

#include <memory>
#include "entities/Faction.h"
#include "map/GameMap.h"
#include "entities/Entity.h"
#include "Input.h"

class TurnManager {
public:
	TurnManager(std::unique_ptr<GameMap> &gameMap);
	void update(Input &input);
	const std::vector<std::shared_ptr<Entity>> &getCurrentEntities();
	std::shared_ptr<Entity> getCurrentEntity();

private:
	std::unique_ptr<GameMap> &map; // Reference to the GameState owned map.
	std::vector<std::shared_ptr<Entity>> currentEntities; // The current entities being updated in order of first to last priority.
	int index;

	bool turnComplete = false;
	bool movementTurn = true; // Is an attacking turn when movementTurn is false.

	void fetchOrderedEntities();
};