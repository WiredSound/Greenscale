#include "TurnManager.h"

TurnManager::TurnManager(std::unique_ptr<GameMap> &gameMap) : map(gameMap) {
}

void TurnManager::update(Input &input) {
	if (currentEntities.size() > 0) {
		std::shared_ptr<Entity> &entity = getCurrentEntity();

		if(!entity->isMyTurn())
			getCurrentEntity()->yourTurnBegin();

		if (decisionMade) {
			bool complete = entity->yourTurnCurrently();

			if (complete) nextEntity();
		}
		else {
			decisionMade = entity->yourTurnDecision(input);
		}
	}
	else {
		fetchOrderedEntities();
	}
}

std::shared_ptr<Entity> &TurnManager::getCurrentEntity() {
	return currentEntities.at(index);
}

void TurnManager::nextEntity() {
	decisionMade = false;

	getCurrentEntity()->yourTurnEnd(); // End of current entity's turn.

	index++;

	if (index >= currentEntities.size())  // All turns now complete.
		fetchOrderedEntities();
}

void TurnManager::fetchOrderedEntities() {
	index = 0;

	currentEntities = map->getEntitesPriorityOrdered();
}

const std::vector<std::shared_ptr<Entity>> &TurnManager::getCurrentEntities() {
	return currentEntities;
}