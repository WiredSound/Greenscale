#include "MovementPath.h"

#include "../GameMap.h"

MovementPath::MovementPath(sf::Vector2u pos) : startPos(pos), targetPos(pos), length(1), pathIndex(1), complete(false) {
	path.push_back(pos);
}

MovementPath::MovementPath(std::vector<sf::Vector2u> tiles)
	: path(tiles), startPos(tiles[0]), targetPos(tiles[tiles.size() - 1]), length((int)tiles.size()), pathIndex(0), complete(true) {}

bool MovementPath::isComplete() {
	return complete;
}

sf::Vector2u MovementPath::currentPosition() {
	return path[pathIndex];
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

MovementPath MovementPath::buildLinePath(const sf::Vector2u &start, const sf::Vector2u &target) {
	return MovementPath(buildLinePathPositions(start, target));
}

std::vector<sf::Vector2u> MovementPath::buildLinePathPositions(const sf::Vector2u &start, const sf::Vector2u &target) {
	std::vector<sf::Vector2u> path;

	if (std::abs((int)target.y - (int)start.y) < std::abs((int)target.x - (int)start.x)) {
		if (start.x > target.x) {
			path = buildLinePathLow(target, start, false);
		}
		else
			path = buildLinePathLow(start, target, true);
	}
	else {
		if (start.y > target.y) {
			path = buildLinePathHigh(target, start, false);
		}
		else
			path = buildLinePathHigh(start, target, true);
	}

	return path;
}

std::vector<sf::Vector2u> MovementPath::buildLinePathLow(const sf::Vector2u &start, const sf::Vector2u &target, bool append) {
	DEBUG_LOG_SPAM("Building line path low. Appending: " << append);

	std::vector<sf::Vector2u> tiles;

	addPosition(start, tiles, append);

	int dx = target.x - start.x;
	int dy = target.y - start.y;
	int yi = 1;

	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}

	int d = 2 * dy - dx;
	int y = start.y;

	for (unsigned int x = start.x; x < target.x; x++) {
		addPosition(sf::Vector2u(x, y), tiles, append);

		if (d > 0) {
			y = y + yi;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
	}

	addPosition(target, tiles, append);

	return tiles;
}
std::vector<sf::Vector2u> MovementPath::buildLinePathHigh(const sf::Vector2u &start, const sf::Vector2u &target, bool append) {
	DEBUG_LOG_SPAM("Building line path high. Appending: " << append)

		std::vector<sf::Vector2u> tiles;

	addPosition(start, tiles, append);

	int dx = target.x - start.x;
	int dy = target.y - start.y;
	int xi = 1;

	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}

	int d = 2 * dx - dy;
	int x = start.x;

	for (unsigned int y = start.y; y < target.y; y++) {
		addPosition(sf::Vector2u(x, y), tiles, append);

		if (d > 0) {
			x = x + xi;
			d = d - 2 * dy;
		}
		d = d + 2 * dx;
	}

	addPosition(target, tiles, append);

	return tiles;
}

unsigned int MovementPath::distanceFromTo(const sf::Vector2u &from, const sf::Vector2u &to) {
	return static_cast<unsigned int>(buildLinePathPositions(from, to).size());
}

void MovementPath::addPosition(const sf::Vector2u pos, std::vector<sf::Vector2u> &list, bool append) {
	if (append)
		list.push_back(pos);
	else
		list.insert(list.begin(), pos);
}