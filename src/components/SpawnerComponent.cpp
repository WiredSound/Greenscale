#include "SpawnerComponent.h"

#include "../entities/Entity.h"

IDs::Entities SpawnerComponent::getSpawnerEntityId() {
	return fetchInfo().spawnerEntityId;
}

unsigned int SpawnerComponent::getSpawnerEntityCount() {
	return fetchInfo().spawnerEntityCount;
}

std::vector<ProjectileArc> SpawnerComponent::useEnabled(Entity &user, MovementPath path, PowerPool &pool, Console &console) {
	GameMap *map = user.getMapPtr();

	for (unsigned int i = 0; i < getSpawnerEntityCount(); i++) {
		sf::Vector2u position = map->findNearestFreePosition(user.getPosition());
		std::shared_ptr<Entity> entity = user.builder.buildEntity(getSpawnerEntityId(), "Spawned", position, user.getFaction(), sf::Vector2u(2, 2), user.getController());

		map->addEntity(entity);
	}

	return Component::useEnabled(user, path, pool, console);
}