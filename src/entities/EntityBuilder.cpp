#include "EntityBuilder.h"

EntityBuilder::EntityBuilder(Console &consoleRef) : console(consoleRef), manager(std::make_shared<EntityManager>()) {}

bool EntityBuilder::loadEntityInfo(std::string filename) {
	return manager->loadFromJsonFile(filename);
}

std::shared_ptr<Entity> EntityBuilder::buildEntity(IDs::Entities id, std::string personalName, sf::Vector2u position, Faction faction, std::shared_ptr<EntityController> controller) {
	std::string type = manager->get(id).type;

	if (type == "robot") return std::make_shared<Robot>(id, manager, personalName, position, faction, controller, console);
	//return std::make_shared<Entity>(id, manager, personalName, position, faction, controller);
	throw std::exception("No entity type specified!");
}

sf::Vector2f EntityBuilder::getFrameSize() {
	return manager->getFrameSize();
}