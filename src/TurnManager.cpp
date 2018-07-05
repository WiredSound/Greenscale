#include "TurnManager.h"

void TurnManager::update(Input &input, std::unique_ptr<GameMap> &map) {
	if (currentEntities.size() > 0) {
		std::shared_ptr<Entity> &entity = getCurrentEntity();

		if (!entity->isMyTurn())
			getCurrentEntity()->yourTurnBegin();

		if (decisionMade) {
			bool complete = entity->yourTurnCurrently();

			if (complete) nextEntity(map);
		}
		else {
			decisionMade = entity->yourTurnDecision(input);
		}
	}
	else {
		fetchOrderedEntities(map);
	}
}

std::shared_ptr<Entity> &TurnManager::getCurrentEntity() {
	return currentEntities.at(index);
}

void TurnManager::nextEntity(std::unique_ptr<GameMap> &map) {
	decisionMade = false;

	getCurrentEntity()->yourTurnEnd(); // End of current entity's turn.

	index++;

	if (index >= currentEntities.size())  // All turns now complete.
		fetchOrderedEntities(map);
}

void TurnManager::fetchOrderedEntities(std::unique_ptr<GameMap> &map) {
	index = 0;

	currentEntities = map->getEntitesPriorityOrdered();
}

const std::vector<std::shared_ptr<Entity>> &TurnManager::getCurrentEntities() {
	return currentEntities;
}