#pragma once

#include <memory>
#include <string>
#include "Damage.h"
#include "../IDs.h"

struct ComponentInfo {
	IDs::Components id;
	std::string name;
	std::string description;
	std::string type; // Determines what Component-derived class this component requires.
	unsigned int textureX; // Texture coordinates.
	unsigned int textureY;
	unsigned int maxIntegrity;
	unsigned int dangerousHeatLevel;
	unsigned int fatalHeatLevel;
	unsigned int passivePowerGen;
	unsigned int passivePowerConsume;
	unsigned int usePowerGen;
	unsigned int usePowerConsume;
	unsigned int passiveHeatDissipate;
	unsigned int passiveHeatGen;
	unsigned int useHeatDissipate;
	unsigned int useHeatGen;
	unsigned int powerStorage;
	unsigned int movementRange;
	std::vector<IDs::ComponentUpgrades> possibleUpgrades;

	IDs::Projectiles projectileId;
	unsigned int projectileCount;
	Damage projectileDamage;
	unsigned int projectileRange;
	unsigned int projectilePenetration;

	unsigned int spawnerEntityCount;
	IDs::Entities spawnerEntityId;
};

struct ComponentUpgrade {
	IDs::Components id;
	std::string name;
	std::string prefix;
	std::string description;

	float maxIntegrityModifier = 0.0f;
	float unsafeHeatLevelModifier = 0.0f;
	float powerModifier = 0.0f;
	float heatModifier = 0.0f;
	float projectileModifier = 0.0f;
	float transportModifier = 0.0f;
};