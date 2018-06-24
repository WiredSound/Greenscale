#pragma once

#include <memory>
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include "MapRoom.h"
#include "pathfinding/AStarPathBuilder.h"
#include "TileLayer.h"
#include "EntityLayer.h"
#include "../entities/Faction.h"
class Entity;
class Robot;

class GameMap {
public:
	GameMap(sf::Vector2u mapSize, sf::Vector2f sizeTile, std::unique_ptr<TileLayer> tileLayer, std::unique_ptr<EntityLayer> entityLayer);

	void update();
	void turnPassed();
	void draw(sf::RenderWindow &window);
	void colourTilePath(MovementPath path, sf::Color colour);
	void resetColourTilePath(MovementPath path);

	void construct(); // Goes through each room and rebuilds it.
	void addRoom(std::unique_ptr<MapRoom> room);
	bool addEntity(std::shared_ptr<Entity> entity);
	std::vector<std::shared_ptr<Entity>> getEntitesPriorityOrdered();
	std::vector<std::shared_ptr<Entity>> getEntitiesInFaction(Faction faction);
	std::vector<std::shared_ptr<Entity>> getEntitiesAt(sf::Vector2u position);

	sf::Vector2u worldPosToTilePos(sf::Vector2f worldPos);
	sf::Vector2u mousePosToTilePos(sf::Vector2i mousePos, sf::RenderWindow &window);
	sf::Vector2u mousePosToTilePos(sf::RenderWindow &window);

	bool isTilePositionFree(sf::Vector2u position);
	bool isEntityPositionFree(sf::Vector2u position);
	bool isPositionFree(sf::Vector2u position);

	unsigned int applyPenetrationToTileAt(sf::Vector2u pos, unsigned int penetration);

	bool withinBounds(sf::Vector2u pos);

	const AStarPathBuilder pathfinder;

	const sf::Vector2u size;
	const sf::Vector2f tileSize;

	std::unique_ptr<TileLayer> tiles;
	std::unique_ptr<EntityLayer> entities;

private:
	std::vector<std::unique_ptr<MapRoom>> rooms;
};

bool entitySortMethod(const std::shared_ptr<Entity> &left, const std::shared_ptr<Entity> &right);