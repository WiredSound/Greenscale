#pragma once

#include <memory>
#include "Component.h"
#include "RangedComponent.h"

class ComponentBuilder {
public:
	ComponentBuilder();
	void loadComponentInfo(std::string filename);
	void loadProjectileInfo(std::string filename);

	std::unique_ptr<Component> buildComponentNoUpgrades(IDs::Components);
	std::unique_ptr<Component> buildComponentRandomised(IDs::Components, unsigned int upgradePoints);

private:
	std::shared_ptr<ComponentManager> componentManager;
	std::shared_ptr<ProjectileManager> projectileManager;
	std::default_random_engine rand;
};