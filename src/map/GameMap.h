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
	bool isPositionFree(sf::Vector2u position);
	std::vector<std::shared_ptr<Entity>> getEntitesPriorityOrdered();
	std::vector<std::shared_ptr<Entity>> getEntitiesInFaction(Faction faction);
	sf::Vector2u worldPosToTilePos(sf::Vector2f worldPos);

	const AStarPathBuilder pathfinder;

	bool withinBounds(sf::Vector2u pos);

	const sf::Vector2u size;
	const sf::Vector2f tileSize;

private:
	std::unique_ptr<TileLayer> tiles;
	std::unique_ptr<EntityLayer> entities;
	std::vector<std::unique_ptr<MapRoom>> rooms;
};

bool entitySortMethod(const std::shared_ptr<Entity> &left, const std::shared_ptr<Entity> &right);