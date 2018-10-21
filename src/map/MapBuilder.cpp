#include "map/MapBuilder.h"

#include "map/GradientTerrainGenerator.h"
#include "IDs.h"

#define TILES_PATH "assets/tiles/tiles.json"
#define COMPONENTS_PATH "assets/components/components.json"
#define PROJECTILES_PATH "assets/projectiles/projectiles.json"
#define ENTITIES_PATH "assets/entities/entities.json"
#define TILES_TEXTURE_PATH "assets/tiles/tiles.png"
#define ENTITIES_TEXTURE_PATH "assets/entities/entities.png"
#define PROJECTILES_TEXTURE_PATH "assets/projectiles/projectiles.png"

MapBuilder::MapBuilder(sf::Vector2f sizeTile, std::vector<Faction> friendlyFactions, std::shared_ptr<PlayerController> controller, Console &consoleRef)
	: tilesTexture(std::make_shared<sf::Texture>()), entitiesTexture(std::make_shared<sf::Texture>()), projectilesTexture(std::make_shared<sf::Texture>()),
	playerController(controller), entityBuilder(consoleRef), tileSize(sizeTile), playerFriendlyFactions(friendlyFactions), console(consoleRef)
{
	tileManager.loadFromJsonFile(TILES_PATH);

	entityBuilder.loadEntityInfo(ENTITIES_PATH);

	componentBuilder.loadComponentInfo(COMPONENTS_PATH);
	componentBuilder.loadProjectileInfo(PROJECTILES_PATH);

	tilesTexture->loadFromFile(TILES_TEXTURE_PATH);
	entitiesTexture->loadFromFile(ENTITIES_TEXTURE_PATH);
	projectilesTexture->loadFromFile(PROJECTILES_TEXTURE_PATH);
}

std::unique_ptr<GameMap> MapBuilder::buildMap(sf::Vector2u size, std::vector<std::shared_ptr<Entity>> initialEntities, std::vector<std::shared_ptr<MapGenerator>> generators) {
	auto tiles = makeTileLayer(size);
	auto entities = makeEntityLayer(size);
	auto projectiles = makeProjectileLayer(size);

	for (auto &generator : generators)
		generator->generateTiles(tiles);

	DEBUG_LOG("Building " << size.x << "x" << size.y << " map with " << tileSize.x << "x" << tileSize.y << " tile size...");

	auto map = std::make_unique<GameMap>(size, tileSize, std::move(tiles), std::move(entities), std::move(projectiles), playerFriendlyFactions, console);
	map->addEntities(initialEntities);

	for (auto &generator : generators)
		generator->generateEntities(map, entityBuilder, componentBuilder);

	return map;
}

std::unique_ptr<TileLayer> MapBuilder::makeTileLayer(sf::Vector2u layerSize) {
	return std::make_unique<TileLayer>(layerSize, tileSize, tilesTexture, tileManager);
}
std::unique_ptr<EntityLayer> MapBuilder::makeEntityLayer(sf::Vector2u layerSize) {
	return std::make_unique<EntityLayer>(layerSize, tileSize, entityBuilder.getFrameSize(), entitiesTexture);
}
std::unique_ptr<ProjectileLayer> MapBuilder::makeProjectileLayer(sf::Vector2u layerSize) {
	return std::make_unique<ProjectileLayer>(layerSize, tileSize, tileManager.getSingleTileTextureSize(), projectilesTexture);
}
