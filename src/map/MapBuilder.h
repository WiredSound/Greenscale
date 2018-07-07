#pragma once

#include <random>
#include "generators/MapGenerator.h"
#include "TileManager.h"
#include "GameMap.h"
#include "SquareRoom.h"
#include "../entities/EntityBuilder.h"
#include "../entities/PlayerController.h"
#include "../components/ComponentBuilder.h"

// Note that the MapBuilder does not handle any procedual generation, that is done by MapGenerator and its subclasses.

class MapBuilder {
public:
	MapBuilder(unsigned int seed, GameGui &gui, sf::Vector2f sizeTile); // The game gui is required by the player controller.

	std::unique_ptr<GameMap> buildMap(sf::Vector2u size, std::vector<std::shared_ptr<Entity>> initialEntities, std::vector<std::shared_ptr<MapGenerator>> generators);

	std::shared_ptr<PlayerController> playerController;
	EntityBuilder entityBuilder;
	ComponentBuilder componentBuilder;

protected:
	std::unique_ptr<TileLayer> makeTileLayer(sf::Vector2u size, sf::Vector2f tileSize);
	std::unique_ptr<EntityLayer> makeEntityLayer(sf::Vector2u size, sf::Vector2f tileSize);

private:
	TileManager tileManager;

	std::shared_ptr<sf::Texture> tilesTexture;
	std::shared_ptr<sf::Texture> entitiesTexture;
	std::shared_ptr<sf::Texture> projectilesTexture;

	sf::Vector2f tileSize;

	std::default_random_engine rand;
};