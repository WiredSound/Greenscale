#include "EntityBuilder.h"

#include "controllers/EntityController.h"
#include "Entity.h"
#include "Robot.h"

EntityBuilder::EntityBuilder(Console &consoleRef) : console(consoleRef), manager(std::make_shared<EntityManager>()) {}

bool EntityBuilder::loadEntityInfo(std::string filename) {
	return manager->loadFromJsonFile(filename);
}

/**
 * Constructs a new entity.
 * \param id The ID of the entity to be constructed.
 * \param personalName The unique name of the entity that is not defined by their type.
 * \param position The entity's position on the map.
 * \param Faction The faction that the entity is aligned with.
 * \param gridSize The dimensions of the ComponentGrid the entity has.
 * \param controller The EntityController tasked with controlling the entity.
 * \return The newly constructed entity.
 */
std::shared_ptr<Entity> EntityBuilder::buildEntity(IDs::Entities id, std::string personalName, sf::Vector2u position, Faction faction, sf::Vector2u gridSize, std::shared_ptr<EntityController> controller) {
	std::string type = manager->get(id).type;

	if (type == "robot") return std::make_shared<Robot>(id, manager, personalName, position, faction, gridSize, controller, console, *this);
	//return std::make_shared<Entity>(id, manager, personalName, position, faction, controller);
	throw std::exception("No entity type specified!");
}

sf::Vector2f EntityBuilder::getFrameSize() {
	return manager->getFrameSize();
}