#pragma once

#include <memory>
#include "Component.h"

/**
 * Handles the setup of both the component and projectile managers as well as allows for the construction of new components.
 */
class ComponentBuilder {
public:
	ComponentBuilder();
	bool loadComponentInfo(std::string filename);
	bool loadProjectileInfo(std::string filename);

	std::unique_ptr<Component> buildComponentNoUpgrades(IDs::Components id);
	std::unique_ptr<Component> buildComponentRandomised(IDs::Components id, unsigned int upgradePoints);

private:
	std::shared_ptr<ComponentManager> componentManager;
	std::shared_ptr<ProjectileManager> projectileManager;
};