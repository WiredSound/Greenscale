#include "MovementPath.h"

#include "../GameMap.h"
#include "../GridHelp.h"

MovementPath::MovementPath(sf::Vector2u pos) : pathIndex(1), complete(false) {
	path.push_back(pos);
}

MovementPath::MovementPath(std::vector<sf::Vector2u> tiles)
	: path(tiles), pathIndex(0), complete(true) {}

bool MovementPath::isComplete() {
	return complete;
}

sf::Vector2u MovementPath::currentPosition() {
	if (pathIndex < path.size())
		return path[pathIndex];
	return getTargetPosition();
}

void MovementPath::nextPosition() {
	if (pathIndex < getLength())
		pathIndex++;
}

bool MovementPath::reachedTarget() {
	return pathIndex == getLength();
}

void MovementPath::resetPosition() {
	pathIndex = 0;
}

unsigned int MovementPath::getIndex() {
	return pathIndex;
}

unsigned int MovementPath::getLength() {
	return static_cast<unsigned int>(path.size());
}

std::vector<sf::Vector2u> MovementPath::getPathTiles() {
	return path;
}

sf::Vector2u MovementPath::getStartPosition() {
	return path[0];
}

sf::Vector2u MovementPath::getTargetPosition() {
	return path[getLength() - 1];
}

void MovementPath::restrictLength(unsigned int size) {
	if (getLength() > size)
		path.resize(size);
}

// PATH BUILDING:

MovementPath MovementPath::buildLinePath(sf::Vector2u start, sf::Vector2u target, unsigned int length) {
	return MovementPath(GridHelp::buildLine(static_cast<sf::Vector2f>(start), static_cast<sf::Vector2f>(target), static_cast<float>(length)));
}

unsigned int MovementPath::distanceFromTo(sf::Vector2u start, sf::Vector2u target) {
	return GridHelp::buildLine(static_cast<sf::Vector2f>(start), static_cast<sf::Vector2f>(target)).size();
}