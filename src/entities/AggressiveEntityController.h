#pragma once

#include "EntityController.h"

/*
This AI will stop at nothing to destroy any entities belonging the factions
it is commanded to attack.
*/

class AggressiveEntityController : public EntityController {
public:
	AggressiveEntityController(std::vector<Faction> attackFactions);
	virtual bool handleMovement(Entity *entity, Input &input) override;
	virtual bool handleAttacking(Entity *entity, Input &input) override;

private:
	std::vector<Faction> enemyFactions;

	std::vector<std::shared_ptr<Entity>> getEnemies(GameMap *map);
	std::shared_ptr<Entity> findNearestEnemy(sf::Vector2u position, const std::vector<std::shared_ptr<Entity>> &enemies);
};