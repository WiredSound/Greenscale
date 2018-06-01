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
	std::vector<IDs::ComponentUpgrades> possibleUpgrades;
};

struct ComponentUpgrade {
	IDs::Components id;
	std::string name;
	std::string prefix;
	std::string description;

	float maxIntegrityModifier;
	float dangerousHeatLevelModifier;
	float fatalHeatLevelModifier;
	float passivePowerDrainModifer;
	float usePowerDrainModifier;
	float heatDissipationModifier;
};