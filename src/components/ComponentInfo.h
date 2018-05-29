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
	int passivePowerDrain;
	int heatDissipation;
	std::vector<IDs::ComponentUpgrades> possibleUpgrades;
};

struct ComponentUpgrade {
	IDs::Components id;
	std::string name;
	std::string prefix;
	std::string description;
};