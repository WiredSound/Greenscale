#pragma once

#include "EntityManager.h"
#include "Entity.h"
#include "Robot.h"

class EntityBuilder {
public:
	EntityBuilder(Console &consoleRef);
	bool loadEntityInfo(std::string filename);
	std::shared_ptr<Entity> buildEntity(IDs::Entities id, std::string personalName, sf::Vector2u position, Faction faction, std::shared_ptr<EntityController> controller);
	sf::Vector2f getFrameSize();

private:
	std::shared_ptr<EntityManager> manager;
	Console &console;
};