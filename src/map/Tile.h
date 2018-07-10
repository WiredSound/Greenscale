#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>
#include "../IDs.h"

struct Tile {
	IDs::Tiles id;
	std::string name;
	unsigned int textureX; // Texture coordinates.
	unsigned int textureY;
	sf::Color defaultColour;
	bool blocking; // Whether the tile blocks movement.
	float cover; // Chance the tile will block an incoming projectile.
	unsigned int strength; // The amount of damage that needs to be inflicted by a projectile for the tile to break.
};