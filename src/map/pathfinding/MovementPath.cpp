#include "MovementPath.h"

#include "../GameMap.h"
#include "../GridHelp.h"

MovementPath::MovementPath(sf::Vector2u pos) : startPos(pos), targetPos(pos), length(1), pathIndex(1), complete(false) {
	path.push_back(pos);
}

/*
MovementPath::MovementPath(sf::Vector2u pos, bool pathComplete) : startPos(pos), targetPos(pos), length(1), pathIndex(pathComplete ? 0 : 1), complete(pathComplete) {
	path.push_back(pos);
}
*/

MovementPath::MovementPath(std::vector<sf::Vector2u> tiles)
	: path(tiles), startPos(tiles[0]), targetPos(tiles[tiles.size() - 1]), length((int)tiles.size()), pathIndex(0), complete(true) {}

bool MovementPath::isComplete() {
	return complete;
}

sf::Vector2u MovementPath::currentPosition() {
	if (pathIndex < path.size())
		return path[pathIndex];
	return targetPos;
}

void MovementPath::nextPosition() {
	if (pathIndex < length)
		pathIndex++;
}

bool MovementPath::reachedTarget() {
	return pathIndex == length;
}

void MovementPath::resetPosition() {
	pathIndex = 0;
}

unsigned int MovementPath::getIndex() {
	return pathIndex;
}

unsigned int MovementPath::getLength() {
	return length;
}

std::vector<sf::Vector2u> MovementPath::getPathTiles() {
	return path;
}

sf::Vector2u MovementPath::getStartPosition() {
	return startPos;
}

sf::Vector2u MovementPath::getTargetPosition() {
	return targetPos;
}

// PATH BUILDING:

MovementPath MovementPath::buildLinePath(sf::Vector2u start, sf::Vector2u target, unsigned int length) {
	return MovementPath(GridHelp::buildLine(static_cast<sf::Vector2f>(start), static_cast<sf::Vector2f>(target), static_cast<float>(length)));
}

unsigned int MovementPath::distanceFromTo(sf::Vector2u start, sf::Vector2u target) {
	return GridHelp::buildLine(static_cast<sf::Vector2f>(start), static_cast<sf::Vector2f>(target)).size();
}