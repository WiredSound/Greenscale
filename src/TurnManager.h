#pragma once

#include <memory>
#include "entities/Faction.h"
#include "map/GameMap.h"
#include "entities/Entity.h"
#include "Input.h"
#include "Camera.h"

/*
 * The game is of course turn-based so it is the role of the TurnManager class is to handle the turn system. It takes a GameMap reference in its update function and then fetches all the entities
 * present on that map. Each turn for an entity is split into several distinct phases:
 * First, the entity's yourTurnBegin method is called once.
 * Next, yourTurnDecision is called which in turn calls upon the entity's controller. This method is called every frame until true is returned which indicates that the controller has at that
 * point decided what the entity will do this turn.
 * The next method called by the turn manager is yourTurnCurrently which is where the entity actually carries out their action (whether that may be attacking, moving, etc). This is again called
 * continually until true is returned.
 * Finally, the entity's yourTurnEnd method is called once before the turn manager moves on to the next entity.
 */

class TurnManager {
public:
	TurnManager(Camera &gameCamera);
	void update(Input &input, std::unique_ptr<GameMap> &map);
	std::shared_ptr<Entity> &getCurrentEntity();
	const std::vector<std::shared_ptr<Entity>> &getCurrentEntities();

private:
	Camera &camera;

	std::vector<std::shared_ptr<Entity>> currentEntities; // The current entities being updated in order of first to last priority.
	int index;

	bool decisionMade; // Whether the current entity has decide upon what they will do this turn.

	void fetchOrderedEntities(std::unique_ptr<GameMap> &map);
	void nextEntity(std::unique_ptr<GameMap> &map);
};