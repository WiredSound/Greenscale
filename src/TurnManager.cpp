#include "TurnManager.h"

TurnManager::TurnManager(std::unique_ptr<GameMap> &gameMap) : map(gameMap) {}

void TurnManager::update(Input &input) {
	if (currentEntities.size() > 0) {
		std::shared_ptr<Entity> entity = getCurrentEntity();

		if (!turnComplete) {
			if (movementTurn) {
				DEBUG_LOG_SPAM("Entity movement turn: " << entity->name);

				turnComplete = entity->yourMovementTurn(input);
			}
			else {
				DEBUG_LOG_SPAM("Entity attacking turn: " << entity->name);

				turnComplete = entity->yourAttackTurn(input);
			}
		}

		if (turnComplete) { // If the entity has complete its turn then changing from moving to attacking or move onto the next entity.
			turnComplete = false;
			map->turnPassed();

			// Swap turn type between movement and attacking.
			if (movementTurn) {
				movementTurn = false;
			}
			else {
				index++; // If the entity has finished its attacking then move onto the next entity.
				movementTurn = true;
			}
		}
	}
	else {
		fetchOrderedEntities();
	}
}

const std::vector<std::shared_ptr<Entity>> &TurnManager::getCurrentEntities() {
	return currentEntities;
}

std::shared_ptr<Entity> TurnManager::getCurrentEntity() {
	if (index >= currentEntities.size()) // All turns now complete.
		fetchOrderedEntities();
	
	return currentEntities.at(index);
}

void TurnManager::fetchOrderedEntities() {
	index = 0;

	currentEntities = map->getEntitesPriorityOrdered();
}