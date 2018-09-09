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
#include "ProjectileLayer.h"
#include "../entities/Faction.h"
#include "../projectiles/ProjectileArc.h"
#include "../Console.h"
class Entity;
class Robot;

/**
 * The GameMap is were all map information (such as entities present, tiles and projectiles) is stored and also where the rendering of this information takes place.
 * Contains both a TileLayer and EntityLayer as well as all ProjectileArcs plus an instance of AStarPathBuilder.
 */
class GameMap {
public:
	GameMap(sf::Vector2u mapSize, sf::Vector2f sizeTile, std::unique_ptr<TileLayer> tileLayer, std::unique_ptr<EntityLayer> entityLayer, std::unique_ptr<ProjectileLayer> projectileLayer,
		std::vector<Faction> friendlyFactions, Console &consoleRef);

	void update();
	void turnPassed();
	void draw(sf::RenderWindow &window);

	void colourTilePath(MovementPath path, sf::Color colour);
	void resetColourTilePath(MovementPath path);

	void fireProjectileArcs(std::vector<ProjectileArc> arcs);
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

	sf::Vector2u getCentre();

	bool isTilePositionFree(sf::Vector2u position);
	bool isEntityPositionFree(sf::Vector2u position);
	bool isPositionFree(sf::Vector2u position);
	bool isPositionFree(sf::Vector2u position, sf::Vector2u size);
	sf::Vector2u findNearestFreePosition(sf::Vector2u position, unsigned int maximumIterations = 100);

	//std::shared_ptr<Entity> findEntityNearestToPoint(sf::Vector2u point);
	//std::shared_ptr<Entity> findEntityNearestToPoint(sf::Vector2u point, std::vector<Faction> factions);

	bool enoughPenetrationToDestroyTileAt(sf::Vector2u pos, unsigned int penetration);
	unsigned int applyPenetrationToTileAt(sf::Vector2u pos, unsigned int penetration);

	std::vector<sf::Vector2u> getAdjacentPositions(sf::Vector2u pos) const;

	bool isFactionPlayerFriendly(Faction faction);

	bool withinBounds(sf::Vector2u pos);

	bool save(std::string path);
	bool load(std::string path);

	const AStarPathBuilder pathfinder;

	const sf::Vector2u size;
	const sf::Vector2f tileSize;

private:
	std::unique_ptr<TileLayer> tiles;
	std::unique_ptr<EntityLayer> entities;
	std::unique_ptr<ProjectileLayer> projectiles;

	std::vector<std::unique_ptr<MapRoom>> rooms; // Obsolete...

	sf::Sprite projectileSprite;

	std::vector<Faction> playerFriendlyFactions;

	Console &console;
};