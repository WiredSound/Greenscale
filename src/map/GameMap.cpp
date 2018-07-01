#include "GameMap.h"

#include <experimental/filesystem>
#include "../entities/Robot.h"

GameMap::GameMap(sf::Vector2u mapSize, sf::Vector2f sizeTile, std::unique_ptr<TileLayer> tileLayer, std::unique_ptr<EntityLayer> entityLayer, std::shared_ptr<sf::Texture> textureProjectiles)
	: size(mapSize), tileSize(sizeTile), tiles(std::move(tileLayer)), entities(std::move(entityLayer)), pathfinder(this), projectilesTexture(textureProjectiles) {}

void GameMap::update() {
	entities->update();
	updateProjectiles();
}

void GameMap::turnPassed() {
	tiles->updateVertices();
}

void GameMap::draw(sf::RenderWindow &window) {
	window.draw(*tiles);
	window.draw(*entities);

	if (!areAllProjectileArcsComplete())
		window.draw(projectileSprite);

	//tiles->resetColouring();
}

void GameMap::colourTilePath(MovementPath path, sf::Color colour) {
	tiles->colourPath(path, colour);
}

void GameMap::resetColourTilePath(MovementPath path) {
	tiles->resetColourPath(path);
}

void GameMap::fireArcs(std::vector<ProjectileArc> arcs) {
	projectileArcs.insert(projectileArcs.end(), arcs.begin(), arcs.end());
}

bool GameMap::areAllProjectileArcsComplete() {
	return projectileArcs.size() == 0;
}

void GameMap::updateProjectiles() {
	if (!areAllProjectileArcsComplete()) {
		ProjectileArc &arc = projectileArcs[0];
		sf::Vector2u &position = arc.getCurrentProjectilePosition();
		const ProjectileVisual &visual = arc.getProjectileVisualInfo();
		const Animation::Frame &frame = visual.animation->getFrame(arc.getAnimationTime());
		sf::Vector2f singleProjectileTextureSize = arc.getSingleProjectileTextureSize();

		bool destroyArc = arc.update(this);

		if (arc.reachedTarget() || destroyArc) {
			projectileArcs.erase(projectileArcs.begin()); // Remove the projectile arc.
		}
		else {
			projectileSprite.setPosition(sf::Vector2f(position.x * tileSize.x, position.y * tileSize.y));
			projectileSprite.setTexture(*projectilesTexture.get());
			projectileSprite.setTextureRect(sf::IntRect(frame.textureX * singleProjectileTextureSize.x, frame.textureY * singleProjectileTextureSize.y, singleProjectileTextureSize.x, singleProjectileTextureSize.y));
			projectileSprite.setColor(arc.getProjectileColour());
		}
	}
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
	auto strength = tiles->getTileAt(pos).strength;

	if (enoughPenetrationToDestroyTileAt(pos, penetration)) {
		tiles->setTileAt(pos, IDs::Tiles::GRASS); // TODO: Replace the tile to something more appropriate.
		penetration -= strength;
	}

	return penetration;
}

bool entitySortMethod(const std::shared_ptr<Entity> &left, const std::shared_ptr<Entity> &right) {
	return left->getPriority() < right->getPriority();
}