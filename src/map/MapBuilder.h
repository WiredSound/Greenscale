#pragma once

#include <random>
#include "generators/MapGenerator.h"
#include "TileManager.h"
#include "GameMap.h"
#include "SquareRoom.h"
#include "../entities/EntityBuilder.h"
#include "../components/ComponentBuilder.h"
#include "../entities/controllers/PlayerController.h"

/**
 * This class handles the construction of a new GameMap instance and also performs all the processes required to do so (it does not prefer any procedual generation).
 * This includes loading all the required textures from the assets folder, building tile and entity layers, calling map generators, adding the initial group and entities, and finally actually building
 * and returning a unique pointer to an instance of GameMap.
 */
class MapBuilder {
public:
	MapBuilder(sf::Vector2f sizeTile, std::vector<Faction> friendlyFactions, std::shared_ptr<PlayerController> controller, Console &consoleRef);

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

	Console &console;
};