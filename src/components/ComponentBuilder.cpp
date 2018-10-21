#include "components/ComponentBuilder.h"

#include "components/RangedComponent.h"
#include "components/SpawnerComponent.h"

ComponentBuilder::ComponentBuilder() : componentManager(std::make_shared<ComponentManager>()), projectileManager(std::make_shared<ProjectileManager>()) {}

bool ComponentBuilder::loadComponentInfo(std::string filename) {
	return componentManager->loadFromJsonFile(filename);
}

bool ComponentBuilder::loadProjectileInfo(std::string filename) {
	return projectileManager->loadFromJsonFile(filename);
}

std::unique_ptr<Component> ComponentBuilder::buildComponentNoUpgrades(IDs::Components id) {
	// Rather annoyingly, C++ does not allow switch statements to operate on strings...

	std::string type = componentManager->get(id).type;

	if (type == "ranged") return std::make_unique<RangedComponent>(id, componentManager, projectileManager);
	if (type == "spawner") return std::make_unique<SpawnerComponent>(id, componentManager);
	return std::make_unique<Component>(id, componentManager);
}

std::unique_ptr<Component> ComponentBuilder::buildComponentRandomised(IDs::Components id, unsigned int upgradePoints) {
	auto component = std::make_unique<Component>(id, componentManager);

	std::vector<IDs::ComponentUpgrades> possibleUpgrades = component->getPossibleUpgrades();

	// TODO: ...

	return component;
}
