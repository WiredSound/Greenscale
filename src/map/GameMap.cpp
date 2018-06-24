#include "GameMap.h"

#include "../entities/Robot.h"

GameMap::GameMap(sf::Vector2u mapSize, sf::Vector2f sizeTile, std::unique_ptr<TileLayer> tileLayer, std::unique_ptr<EntityLayer> entityLayer)
	: size(mapSize), tileSize(sizeTile), tiles(std::move(tileLayer)), entities(std::move(entityLayer)), pathfinder(this) {}

void GameMap::update() {
	entities->update();
}

void GameMap::turnPassed() {
	tiles->updateVertices();
}

void GameMap::draw(sf::RenderWindow &window) {
	window.draw(*tiles);
	window.draw(*entities);

	//tiles->resetColouring();
}

void GameMap::colourTilePath(MovementPath path, sf::Color colour) {
	tiles->colourPath(path, colour);
}

void GameMap::resetColourTilePath(MovementPath path) {
	tiles->resetColourPath(path);
}

void GameMap::construct() {
	for (std::unique_ptr<MapRoom> &room : rooms) {
		room->build(tiles);
	}
}

void GameMap::addRoom(std::unique_ptr<MapRoom> room) {
	rooms.push_back(std::move(room));
}

bool GameMap::addEntity(std::shared_ptr<Entity> entity) {
	if (isPositionFree(entity->getPosition())) {
		entity->setMap(this);
		entities->addEntity(entity);
		return true;
	}

	return false;
}

std::vector<std::shared_ptr<Entity>> GameMap::getEntitesPriorityOrdered() {
	std::vector<std::shared_ptr<Entity>> entityList = entities->getEntities();
	std::sort(entityList.begin(), entityList.end(), entitySortMethod);
	return entityList;
}

std::vector<std::shared_ptr<Entity>> GameMap::getEntitiesInFaction(Faction faction) {
	std::vector<std::shared_ptr<Entity>> factionEntities;

	for (std::shared_ptr<Entity> entity : entities->getEntities()) {
		if (entity->getFaction() == faction)
			factionEntities.push_back(entity);
	}

	return factionEntities;
}

std::vector<std::shared_ptr<Entity>> GameMap::getEntitiesAt(sf::Vector2u position) {
	if (withinBounds(position))
		return entities->getEntitiesAt(position);

	return std::vector<std::shared_ptr<Entity>>();
}

sf::Vector2u GameMap::worldPosToTilePos(sf::Vector2f worldPos) {
	return sf::Vector2u(static_cast<unsigned int>(std::floor(worldPos.x / tileSize.x)), static_cast<unsigned int>(std::floor(worldPos.y / tileSize.y)));
}

sf::Vector2u GameMap::mousePosToTilePos(sf::Vector2i mousePos, sf::RenderWindow &window) {
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	return worldPosToTilePos(worldPos);
}

bool GameMap::isTilePositionFree(sf::Vector2u position) {
	return !tiles->getTileAt(position).blocking;
}

bool GameMap::isEntityPositionFree(sf::Vector2u position) {
	return entities->isPositionFree(position);
}

bool GameMap::isPositionFree(sf::Vector2u position) {
	return isTilePositionFree(position) && isEntityPositionFree(position);
}

sf::Vector2u GameMap::mousePosToTilePos(sf::RenderWindow &window) {
	return mousePosToTilePos(sf::Mouse::getPosition(window), window);
}

bool GameMap::withinBounds(sf::Vector2u pos) {
	return tiles->withinBounds(pos.x, pos.y) && entities->withinBounds(pos.x, pos.y);
}

unsigned int GameMap::applyPenetrationToTileAt(sf::Vector2u pos, unsigned int penetration) {
	auto strength = tiles->getTileAt(pos).strength;

	if (penetration >= strength) {
		tiles->setTileAt(pos, IDs::Tiles::DIRT); // TODO: Replace the tile to something more appropriate.
		penetration -= strength;
	}

	return penetration;
}

bool entitySortMethod(const std::shared_ptr<Entity> &left, const std::shared_ptr<Entity> &right) {
	return left->getPriority() < right->getPriority();
}