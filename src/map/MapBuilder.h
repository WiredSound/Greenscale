#pragma once

#include <random>
#include "TileManager.h"
#include "GameMap.h"
#include "SquareRoom.h"
#include "../entities/EntityBuilder.h"
#include "../entities/PlayerController.h"

class MapBuilder {
public:
	MapBuilder(unsigned int seed, sf::RenderWindow &window, GameGui &gui);
	std::unique_ptr<GameMap> buildMap(sf::Vector2u size, sf::Vector2f tileSize, sf::Vector2f tileTextureSize);

private:
	std::shared_ptr<PlayerController> playerController;

	TileManager tileManager;
	ComponentManager componentManager;
	EntityBuilder entityBuilder;

	std::shared_ptr<sf::Texture> tilesTexture;
	std::shared_ptr<sf::Texture> entitiesTexture;

	std::default_random_engine rand;
};