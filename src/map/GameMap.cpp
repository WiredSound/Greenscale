#include "GameMap.h"

#include <cmath>
#include <experimental/filesystem>
#include "../entities/Robot.h"
#include "../Console.h"

bool entitySortMethod(const std::shared_ptr<Entity> &left, const std::shared_ptr<Entity> &right);

GameMap::GameMap(sf::Vector2u mapSize, sf::Vector2f sizeTile,
	std::unique_ptr<TileLayer> tileLayer, std::unique_ptr<EntityLayer> entityLayer, std::unique_ptr<ProjectileLayer> projectileLayer, std::vector<Faction> friendlyFactions, Console &consoleRef)
	: size(mapSize), tileSize(sizeTile), tiles(std::move(tileLayer)), entities(std::move(entityLayer)), projectiles(std::move(projectileLayer)), pathfinder(*this), console(consoleRef),
	playerFriendlyFactions(friendlyFactions) {}

void GameMap::update() {
	entities->update();
	projectiles->update(this);
}

void GameMap::turnPassed() {
	tiles->updateVertices();
}

void GameMap::draw(sf::RenderWindow &window) {
	window.draw(*tiles);
	window.draw(*entities);
	window.draw(*projectiles);
}

/**
 * Change the display colour of all tiles (and entities in the future but this is not yet implemented) in the specified movement path to the given colour.
 * \param path The path to colour in.
 * \param colour The colour to set the path to.
 */
void GameMap::colourTilePath(MovementPath path, sf::Color colour) {
	tiles->colourPath(path, colour);
}

/**
 * Set the colour of all the tiles in the given movement path to their default colours.
 * \param path The path to reset the colours of.
 */
void GameMap::resetColourTilePath(MovementPath path) {
	tiles->resetColourPath(path);
}

void GameMap::fireProjectileArcs(std::vector<ProjectileArc> arcs) {
	projectiles->fireArcs(arcs);
}

bool GameMap::areAllProjectileArcsComplete() {
	return projectiles->areAllArcsComplete();
}

void GameMap::construct() {
	for (std::unique_ptr<MapRoom> &room : rooms) {
		room->build(tiles);
	}
}

void GameMap::addRoom(std::unique_ptr<MapRoom> room) {
	rooms.push_back(std::move(room));
}

/**
 * Added a new entity to the map and sets said entity's map pointer. An entity's map pointer is not set correctly when added directly to an EntityLayer so always use this method over EntityLayer::addEntity.
 * \param entity The entity to add to the map.
 * \return Whether adding the entity was successful. This is determinded by whether the position the entity is at is not already occupied on this map.
 */
bool GameMap::addEntity(std::shared_ptr<Entity> entity) {
	if (isPositionFree(entity->getPosition())) {
		entity->setMap(this);
		entities->addEntity(entity);
		return true;
	}

	return false;
}

bool GameMap::addEntities(std::vector<std::shared_ptr<Entity>> entities) {
	bool success = true;

	for (auto &entity : entities) {
		if (!addEntity(entity)) success = false;
	}

	return success;
}

/**
 * Fetches all the entities on the map ordered based on their faction's priority value from smallest to largest.
 * \return Vector of all entities ordered on priority.
 */
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

sf::Vector2f GameMap::tilePosToWorldPos(sf::Vector2u tilePos) {
	return sf::Vector2f(static_cast<float>(tilePos.x) * tileSize.x, static_cast<float>(tilePos.y) * tileSize.y);
}

sf::Vector2u GameMap::getCentre() {
	return tiles->getCentre();
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

bool GameMap::isPositionFree(sf::Vector2u position, sf::Vector2u size) {
	for (unsigned int x = position.x; x < position.x + size.x; x++) {
		for (unsigned int y = position.y; y < position.y + size.y; y++) {
			if (!isPositionFree(sf::Vector2u(x, y)))
				return false;
		}
	}

	return true;
}

/**
 * Finds the nearest position to the given position where there are no blocking tiles or entities.
 * \param position The position to begin searching from.
 * \param maximumIterations The number of positions to look through before giving up. If the `maximumIterations` limit is reached then `position` is returned.
 * \return The nearest free position or just `position` if no free position was found in the given number of iterations.
 */
sf::Vector2u GameMap::findNearestFreePosition(sf::Vector2u position, unsigned int maximumIterations) {
	std::vector<sf::Vector2u> adjacentPositions = getAdjacentPositions(position);
	adjacentPositions.insert(adjacentPositions.begin(), position); // Add the given position so that it is returned should it happen to already be a free position.

	for (unsigned int i = 0; i < maximumIterations && i < adjacentPositions.size(); i++) {
		sf::Vector2u adjacentTile = adjacentPositions[i];

		if (isPositionFree(adjacentTile)) return adjacentTile;

		auto newAdjacentPositions = getAdjacentPositions(adjacentTile);
		adjacentPositions.insert(adjacentPositions.end(), newAdjacentPositions.begin(), newAdjacentPositions.end()); // Warning: This vector can get very large, very quickly.
	}

	return position;
}

bool GameMap::withinBounds(sf::Vector2u pos) {
	return tiles->withinBounds(pos) && entities->withinBounds(pos);
}

bool GameMap::save(std::string path) {
	if (path[path.size() - 1] != '/') path.push_back('/');

	std::experimental::filesystem::create_directories(path);

	return tiles->save(path + "tiles.sav");// && entities->save(path + "entities.sav");
}

bool GameMap::load(std::string path) {
	if (path[path.size() - 1] != '/') path.push_back('/');

	return tiles->load(path + "tiles.sav");// && entities->load(path + "entities.sav");
}

bool GameMap::enoughPenetrationToDestroyTileAt(sf::Vector2u pos, unsigned int penetration) {
	return penetration >= tiles->getTileAt(pos).strength;
}

unsigned int GameMap::applyPenetrationToTileAt(sf::Vector2u pos, unsigned int penetration) {
	auto &tileAt = tiles->getTileAt(pos);
	auto strength = tileAt.strength;

	if (enoughPenetrationToDestroyTileAt(pos, penetration)) {
		tiles->setIdAt(pos, tileAt.replacementOnDestruction);

		penetration -= strength;
	}

	return penetration;
}

std::vector<sf::Vector2u> GameMap::getAdjacentPositions(sf::Vector2u pos) const {
	std::vector<sf::Vector2u> adjacent;

	if (pos.x > 0) adjacent.push_back(sf::Vector2u(pos.x - 1, pos.y));								// LEFT
	if (pos.x < size.x) adjacent.push_back(sf::Vector2u(pos.x + 1, pos.y));							// RIGHT
	if (pos.y > 0) adjacent.push_back(sf::Vector2u(pos.x, pos.y - 1));								// TOP
	if (pos.y < size.y) adjacent.push_back(sf::Vector2u(pos.x, pos.y + 1));							// BOTTOM
	if (pos.x < size.x && pos.y < size.y) adjacent.push_back(sf::Vector2u(pos.x + 1, pos.y + 1));	// BOTTOM RIGHT
	if (pos.x > 0 && pos.y > 0) adjacent.push_back(sf::Vector2u(pos.x - 1, pos.y - 1));				// TOP LEFT
	if (pos.y < size.y && pos.x > 0) adjacent.push_back(sf::Vector2u(pos.x - 1, pos.y + 1));		// BOTTOM LEFT
	if (pos.y > 0 && pos.x < size.x) adjacent.push_back(sf::Vector2u(pos.x + 1, pos.y - 1));		// TOP RIGHT

	return adjacent;
}

bool GameMap::isFactionPlayerFriendly(Faction faction) {
	return std::find(playerFriendlyFactions.begin(), playerFriendlyFactions.end(), faction) != playerFriendlyFactions.end();
}

bool entitySortMethod(const std::shared_ptr<Entity> &left, const std::shared_ptr<Entity> &right) {
	return left->getPriority() < right->getPriority();
}