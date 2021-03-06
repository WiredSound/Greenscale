#include "map/pathfinding/MovementPath.h"

#include "map/GameMap.h"
#include "map/GridHelp.h"

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
	if (getLength() > 1)
		return path[getLength() - 1];
	return getStartPosition(); // Return the start position if there is only one position present in the path.
}

void MovementPath::restrictLength(unsigned int size) {
	if (getLength() > size)
		path.resize(size);
}

/**
 * Continue to reduce the length of the path by while the condition function returns `true`.
 * \param condition Condition function - the path will only stop being shortened when either this function returns `true` or there is no path left.
 */
void MovementPath::recursivelyShortenBasedOn(std::function<bool()> condition) {
	while (condition() && getLength() > 1)
		restrictLength(getLength() - 1);
}

// PATH BUILDING:

//! Build a MovementPath that directly connects two points in a line. See GridHelp::buildLine for actual implementation as just wraps the positions returned into a MovementPath instance.
MovementPath MovementPath::buildLinePath(sf::Vector2u start, sf::Vector2u target, unsigned int length) {
	return MovementPath(GridHelp::buildLine(static_cast<sf::Vector2f>(start), static_cast<sf::Vector2f>(target), static_cast<float>(length)));
}

//! Calculate the number of tiles directly between two points by counting the number of positions returned by GridHelp::buildLine.
unsigned int MovementPath::distanceFromTo(sf::Vector2u start, sf::Vector2u target) {
	std::size_t size = GridHelp::buildLine(static_cast<sf::Vector2f>(start), static_cast<sf::Vector2f>(target)).size();
	return static_cast<unsigned int>(size);
}
