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
	//std::unique_ptr<const IDs::ComponentUpgrades[]> possibleUpgrades;
};