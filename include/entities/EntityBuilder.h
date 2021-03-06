#pragma once

#include "EntityManager.h"
#include "Faction.h"
#include "../Console.h"
class Entity;
class EntityController;

/**
 * Handles the setup of the EntityManager and allows for the construction of new entities.
 */
class EntityBuilder {
public:
	EntityBuilder(Console &consoleRef);
	bool loadEntityInfo(std::string filename);
	std::shared_ptr<Entity> buildEntity(IDs::Entities id, std::string personalName, sf::Vector2u position, Faction faction, sf::Vector2u gridSize, std::shared_ptr<EntityController> controller);
	sf::Vector2f getFrameSize();

private:
	std::shared_ptr<EntityManager> manager;
	Console &console;
};