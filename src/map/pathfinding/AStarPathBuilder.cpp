#include "map/pathfinding/AStarPathBuilder.h"

#include "map/pathfinding/MovementPath.h"
#include "map/GameMap.h"

AStarPathBuilder::AStarPathBuilder(GameMap &gameMap) : map(gameMap) {}

struct AStarPathBuilder::AStarTile {
	sf::Vector2u parentPosition;
	unsigned int costFromStart;
	unsigned int estimateToTarget;

	unsigned int score() const {
		return costFromStart + estimateToTarget;
	}

	bool operator==(const AStarTile& other) {
		return parentPosition == other.parentPosition && costFromStart == other.costFromStart && estimateToTarget == other.estimateToTarget;
	}
};

//! `std::map` requires a way to compare keys which sf::Vector2u does not provide by default.
struct AStarPathBuilder::CompareVectors {
public:
	CompareVectors(sf::Vector2u sizeMap) : mapSize(sizeMap) {}

	bool operator()(const sf::Vector2u &left, const sf::Vector2u &right) const {
		return (left.y * mapSize.x + left.x) < (right.y * mapSize.x + right.x);
	}
private:
	const sf::Vector2u mapSize;
};

/**
 * Build a new MovementPath between two points.
 * \param start Start position.
 * \param target Target position.
 * \return Newly constructed path.
 */
MovementPath AStarPathBuilder::buildAStarPath(sf::Vector2u start, sf::Vector2u target) const {
	std::map<sf::Vector2u, AStarTile, CompareVectors> openList(map.size), closedList(map.size);

	// Add the starting tile to the open list.
	AStarTile startTile = { start, 0, 0 };
	openList[start] = startTile;

	int iterations = 0;

	while (openList.size() > 0) {
		// Return an empty path if too many iterations go by (suggesting the target is either too far away or impossible to reach).
		if (iterations > 100) {
			DEBUG_LOG("Abandoning path after iterations: " << iterations);

			return MovementPath(target);
		}

		// Find the lowest scoring tile in the open list.
		sf::Vector2u lowestScoringTilePos = findLowestScoringTilePosition(openList);
		AStarTile lowestScoringTile = openList[lowestScoringTilePos];

		// Remove the lowest scoring tile from the open list and add it to the closed list.
		DEBUG_LOG_SPAM("Lowest scoring tile " << lowestScoringTilePos.x << ", " << lowestScoringTilePos.y << " with score " << lowestScoringTile.score() << " added to closed list.");
		openList.erase(lowestScoringTilePos);
		closedList[lowestScoringTilePos] = lowestScoringTile;

		if (lowestScoringTilePos == target) break; // Leave the loop if the target tile has been reached.

		for (sf::Vector2u position : map.getAdjacentPositions(lowestScoringTilePos)) {
			if (map.isPositionFree(position)) {
				if (closedList.count(position)) continue; // Ignore the tile if it is in the closed list.

				AStarTile walkableTile = {
					lowestScoringTilePos, // Parent position.
					lowestScoringTile.costFromStart + 1, // Cost from the starting position.
					MovementPath::distanceFromTo(position, target) // Estimated cost to target position.
				};

				if (!openList.count(position)) { // Add the tile if it is not present in the open list.
					DEBUG_LOG_SPAM("Adding tile " << position.x << ", " << position.y << " with score " << walkableTile.score() << " to open list.");
					openList[position] = walkableTile;
				}
				else { // If the position is already present in the open list...
					AStarTile existingTile = openList[position];

					if (walkableTile.score() < existingTile.score()) { // Compare the current path to this tile with the existing path.
						DEBUG_LOG_SPAM("Found improved route to tile " << position.x << ", " << position.y << " with a score of: " << walkableTile.score());

						// Replace the existing tile if this route is more efficient.
						openList[position] = walkableTile;
					}
				}
			}
		}

		iterations++;
	}

	DEBUG_LOG_SPAM("Found path after iterations: " << iterations);

	return reconstructPath(start, target, closedList);
}

/**
 * Reconstructs a complete MovementPath from the closed list.
 * \param closedList The closed list of positions.
 * \return Newly constructed path.
 */
MovementPath AStarPathBuilder::reconstructPath(const sf::Vector2u &start, const sf::Vector2u &target, const std::map<sf::Vector2u, AStarTile, CompareVectors> &closedList) const {
	std::vector<sf::Vector2u> finalPath;
	finalPath.insert(finalPath.begin(), target);
	AStarTile tile = closedList.at(target);

	while (tile.parentPosition != start) {
		finalPath.insert(finalPath.begin(), tile.parentPosition);
		tile = closedList.at(tile.parentPosition);
	}

	return MovementPath(finalPath);
}

sf::Vector2u AStarPathBuilder::findLowestScoringTilePosition(std::map<sf::Vector2u, AStarTile, CompareVectors> &list) const {
	sf::Vector2u lowest = list.begin()->first;

	for (const std::pair<sf::Vector2u, AStarTile> &pair : list) {
		if (pair.second.score() <= list[lowest].score())
			lowest = pair.first;
	}

	return lowest;
}
