#pragma once

#include <memory>
#include <string>
#include "../IDs.h"

struct ComponentInfo {
	IDs::Components id;
	std::string name;
	std::string description;
	unsigned int textureX; // Texture coordinates.
	unsigned int textureY;
	int maxIntegrity;
	int dangerousHeatLevel;
	int fatalHeatLevel;
	int passivePower;
	int usePower;
	int passiveHeat;
	int useHeat;
	int powerStorage;
	std::vector<IDs::ComponentUpgrades> possibleUpgrades;
};

struct ComponentUpgrade {
	IDs::Components id;
	std::string name;
	std::string prefix;
	std::string description;

	float maxIntegrityModifier = 1.0f;
	float unsafeHeatLevelModifier = 1.0f;
	float powerModifier = 1.0f;
	float heatModifier = 1.0f;
};