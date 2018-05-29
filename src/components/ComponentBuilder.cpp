#include "ComponentBuilder.h"

ComponentBuilder::ComponentBuilder() : manager(std::make_shared<ComponentManager>()) {}

void ComponentBuilder::loadComponentInfo(std::string filename) {
	manager->loadFromJsonFile(filename);
}

std::unique_ptr<Component> ComponentBuilder::buildComponentNoUpgrades(IDs::Components id) {
	return std::make_unique<Component>(id, manager);
}

std::unique_ptr<Component> ComponentBuilder::buildComponentRandomised(IDs::Components id, unsigned int upgradePoints) {
	auto component = std::make_unique<Component>(id, manager);

	std::vector<IDs::ComponentUpgrades> possibleUpgrades = component->getPossibleUpgrades();

	// TODO...

	return component;
}