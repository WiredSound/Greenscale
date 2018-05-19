#include "AggressiveEntityController.h"

#include "Robot.h"

AggressiveEntityController::AggressiveEntityController(std::vector<Faction> factionsToAttack) : enemyFactions(factionsToAttack) {}

bool AggressiveEntityController::handleMovement(Entity *entity, Input &input) {
	GameMap *map = entity->getMapReference();

	std::vector<std::shared_ptr<Entity>> enemies = getEnemies(map);

	if (enemies.size() > 0) {
		std::shared_ptr<Entity> nearestEnemy = findNearestEnemy(entity->getPosition(), enemies);
	}

	return true;
}

bool AggressiveEntityController::handleAttacking(Entity *entity, Input &input) {
	return true;
}

std::vector<std::shared_ptr<Entity>> AggressiveEntityController::getEnemies(GameMap *map) {
	std::vector<std::shared_ptr<Entity>> enemies;

	for (Faction enemyFaction : enemyFactions) {
		auto factionEnemies = map->getEntitiesInFaction(enemyFaction);
		enemies.insert(enemies.begin(), factionEnemies.begin(), factionEnemies.end());
	}

	return enemies;
}

std::shared_ptr<Entity> AggressiveEntityController::findNearestEnemy(sf::Vector2u position, const std::vector<std::shared_ptr<Entity>> &enemies) {
	std::shared_ptr<Entity> nearest = enemies[0];
	unsigned int entityToNearestEnemy = MovementPath::distanceFromTo(position, nearest->getPosition());

	for (std::shared_ptr<Entity> enemy : enemies) {
		unsigned int entityToEnemy = MovementPath::distanceFromTo(position, enemy->getPosition());

		if (entityToEnemy < entityToNearestEnemy) {
			nearest = enemy;
			entityToNearestEnemy = entityToEnemy;
		}
	}

	return nearest;
}