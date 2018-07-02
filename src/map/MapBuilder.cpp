#include "MapBuilder.h"

#include "GradientTerrainGenerator.h"
#include "../IDs.h"

#define TILES_PATH "assets/tiles/tiles.json"
#define COMPONENTS_PATH "assets/components/components.json"
#define PROJECTILES_PATH "assets/projectiles/projectiles.json"
#define ENTITIES_PATH "assets/entities/entities.json"
#define TILES_TEXTURE_PATH "assets/tiles/tiles.png"
#define ENTITIES_TEXTURE_PATH "assets/entities/entities.png"
#define PROJECTILES_TEXTURE_PATH "assets/projectiles/projectiles.png"

MapBuilder::MapBuilder(unsigned int seed, sf::RenderWindow &window, GameGui &gui)
	: rand(seed), tilesTexture(std::make_shared<sf::Texture>()), entitiesTexture(std::make_shared<sf::Texture>()), projectilesTexture(std::make_shared<sf::Texture>()),
	playerController(std::make_shared<PlayerController>(window, gui)) {
	tileManager.loadFromJsonFile(TILES_PATH);

	entityBuilder.loadEntityInfo(ENTITIES_PATH);

	componentBuilder.loadComponentInfo(COMPONENTS_PATH);
	componentBuilder.loadProjectileInfo(PROJECTILES_PATH);

	tilesTexture->loadFromFile(TILES_TEXTURE_PATH);
	entitiesTexture->loadFromFile(ENTITIES_TEXTURE_PATH);
	projectilesTexture->loadFromFile(PROJECTILES_TEXTURE_PATH);
}

std::unique_ptr<GameMap> MapBuilder::buildMap(sf::Vector2u size, sf::Vector2f tileSize) {
	auto tiles = makeTileLayer(size, tileSize);
	auto entities = makeEntityLayer(size, tileSize);

	GradientTerrainGenerator terrainGen(FastNoise::NoiseType::SimplexFractal, 0.1f, IDs::Tiles::GRASS, sf::Color(130, 200, 80), sf::Color(130, 255, 80));
	terrainGen.fillGradientTerrain(tiles, sf::Vector2u(0, 0), size);

	auto map = std::make_unique<GameMap>(size, tileSize, std::move(tiles), std::move(entities), projectilesTexture);

	map->addRoom(std::make_unique<SquareRoom>("First Room", sf::Vector2u(2, 2), sf::Vector2u(5, 5), IDs::Tiles::GROUND, IDs::Tiles::WALL));
	map->addRoom(std::make_unique<SquareRoom>("Second Room", sf::Vector2u(8, 4), sf::Vector2u(5, 5), IDs::Tiles::GROUND, IDs::Tiles::WALL));

	auto player = entityBuilder.buildEntity(IDs::Entities::TROOP_01, "Player", sf::Vector2u(1, 1), Faction::PLAYER, playerController);
	player->getComponentGrid().getComponentAt(sf::Vector2u(0, 0)).set(componentBuilder.buildComponentNoUpgrades(IDs::Components::HEAT_SINK));
	player->getComponentGrid().getComponentAt(sf::Vector2u(1, 0)).set(componentBuilder.buildComponentNoUpgrades(IDs::Components::FISSION_REACTOR));
	player->getComponentGrid().getComponentAt(sf::Vector2u(2, 0)).set(componentBuilder.buildComponentNoUpgrades(IDs::Components::DEFENSIVE_PLATING));
	player->getComponentGrid().getComponentAt(sf::Vector2u(1, 1)).set(componentBuilder.buildComponentNoUpgrades(IDs::Components::RIFLE));
	map->addEntity(player);
	map->addEntity(entityBuilder.buildEntity(IDs::Entities::SCANNER_01, "Scanner", sf::Vector2u(3, 1), Faction::CORPORATION, playerController));
	map->addEntity(entityBuilder.buildEntity(IDs::Entities::RESTRUCTOR_01, "Scanner", sf::Vector2u(5, 1), Faction::ROGUE, playerController));

	return map;
}

std::unique_ptr<TileLayer> MapBuilder::makeTileLayer(sf::Vector2u size, sf::Vector2f tileSize) {
	return std::make_unique<TileLayer>(size, tileSize, tilesTexture, tileManager);
}
std::unique_ptr<EntityLayer> MapBuilder::makeEntityLayer(sf::Vector2u size, sf::Vector2f tileSize) {
	return std::make_unique<EntityLayer>(size, tileSize, entityBuilder.getFrameSize(), entitiesTexture);
}