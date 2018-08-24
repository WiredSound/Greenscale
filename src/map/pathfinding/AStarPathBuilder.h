#pragma once

#include <memory>
#include <vector>
#include <map>
#include <SFML/System/Vector2.hpp>
#include "../../debugging.h"
class GameMap;
class MovementPath;

/**
 * An implementation of the A* pathfinding algorithm.
 * Unlike the path building methods in MovementPath, buildAStarPath is not static and the AStarPathBuilder has to be initialised with a reference to the GameMap.
 */
class AStarPathBuilder {
public:
	AStarPathBuilder(GameMap &gameMap);
	MovementPath buildAStarPath(sf::Vector2u start, sf::Vector2u target) const;

private:
	GameMap &map;

	struct CompareVectors;
	struct AStarTile;

	MovementPath reconstructPath(const sf::Vector2u &start, const sf::Vector2u &target, const std::map<sf::Vector2u, AStarTile, CompareVectors> &closedList) const;
	sf::Vector2u findLowestScoringTilePosition(std::map<sf::Vector2u, AStarTile, CompareVectors> &list) const;
};