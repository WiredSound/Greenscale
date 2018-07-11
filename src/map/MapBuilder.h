#pragma once

#include <random>
#include "generators/MapGenerator.h"
#include "TileManager.h"
#include "GameMap.h"
#include "SquareRoom.h"
#include "../entities/EntityBuilder.h"
#include "../components/ComponentBuilder.h"
#include "../entities/controllers/PlayerController.h"

// Note that the MapBuilder does not handle any procedual generation, that is done by MapGenerator and its subclasses.

class MapBuilder {
public:
	MapBuilder(unsigned int seed, GameGui &gameGui, sf::Vector2f sizeTile, std::vector<Faction> friendlyFactions);

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

	std::vector<Faction> playerFriendlyFactions;

	GameGui &gui;

	std::default_random_engine rand;
};