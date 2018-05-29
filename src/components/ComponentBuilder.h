#pragma once

#include <memory>
#include "Component.h"

class ComponentBuilder {
public:
	ComponentBuilder();
	void loadComponentInfo(std::string filename);

	std::unique_ptr<Component> buildComponentNoUpgrades(IDs::Components);
	std::unique_ptr<Component> buildComponentRandomised(IDs::Components, unsigned int upgradePoints);

private:
	std::shared_ptr<ComponentManager> manager;
	std::default_random_engine rand;
};