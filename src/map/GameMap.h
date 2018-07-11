#pragma once

#include <memory>
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "MapRoom.h"
#include "pathfinding/AStarPathBuilder.h"
#include "TileLayer.h"
#include "EntityLayer.h"
#include "../entities/Faction.h"
#include "../projectiles/ProjectileArc.h"
#include "../gui/GameGui.h"
class Entity;
class Robot;

/*
 * The GameMap handles the storage and rendering of all the tiles, entities and projectiles that make a map within the game. The two classes TileLayer and EntityLayer handle the bulk of
 * this. The GameMap also keeps track of projectiles and pathfiding (via the AStarPathBuilder).
 */

class GameMap {
public:
	GameMap(sf::Vector2u mapSize, sf::Vector2f sizeTile, std::unique_ptr<TileLayer> tileLayer, std::unique_ptr<EntityLayer> entityLayer, std::shared_ptr<sf::Texture> textureProjectiles,
		std::vector<Faction> friendlyFactions, GameGui &gameGui);

	void update();
	void turnPassed();
	void draw(sf::RenderWindow &window);
	void colourTilePath(MovementPath path, sf::Color colour);
	void resetColourTilePath(MovementPath path);

	void fireArcs(std::vector<ProjectileArc> arcs);
	bool areAllProjectileArcsComplete();

	void construct(); // Goes through each room and rebuilds it.
	void addRoom(std::unique_ptr<MapRoom> room);
	bool addEntity(std::shared_ptr<Entity> entity);
	bool addEntities(std::vector<std::shared_ptr<Entity>> entities);
	std::vector<std::shared_ptr<Entity>> getEntitesPriorityOrdered();
	std::vector<std::shared_ptr<Entity>> getEntitiesInFaction(Faction faction);
	std::vector<std::shared_ptr<Entity>> getEntitiesAt(sf::Vector2u position);

	sf::Vector2u worldPosToTilePos(sf::Vector2f worldPos);
	sf::Vector2f tilePosToWorldPos(sf::Vector2u tilePos);

	bool isTilePositionFree(sf::Vector2u position);
	bool isEntityPositionFree(sf::Vector2u position);
	bool isPositionFree(sf::Vector2u position);
	sf::Vector2u findNearestFreePosition(sf::Vector2u position, unsigned int maximumIterations = 100);

	bool enoughPenetrationToDestroyTileAt(sf::Vector2u pos, unsigned int penetration);
	unsigned int applyPenetrationToTileAt(sf::Vector2u pos, unsigned int penetration);

	std::vector<sf::Vector2u> getAdjacentPositions(sf::Vector2u pos) const;

	bool withinBounds(sf::Vector2u pos);

	bool save(std::string path);
	bool load(std::string path);

	const AStarPathBuilder pathfinder;

	const sf::Vector2u size;
	const sf::Vector2f tileSize;

private:
	std::unique_ptr<TileLayer> tiles;
	std::unique_ptr<EntityLayer> entities;

	std::vector<std::unique_ptr<MapRoom>> rooms;

	std::vector<ProjectileArc> projectileArcs;
	std::shared_ptr<sf::Texture> projectilesTexture;
	sf::Sprite projectileSprite;

	std::vector<Faction> playerFriendlyFactions;

	GameGui &gui;

	void updateProjectiles();
};

bool entitySortMethod(const std::shared_ptr<Entity> &left, const std::shared_ptr<Entity> &right);