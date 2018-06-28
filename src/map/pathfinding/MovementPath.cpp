#include "MovementPath.h"

#include "../GameMap.h"

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
	return MovementPath(buildLinePathPositions(static_cast<sf::Vector2f>(start), static_cast<sf::Vector2f>(target), length));
}

unsigned int MovementPath::distanceFromTo(sf::Vector2u start, sf::Vector2u target) {
	return buildLinePathPositions(static_cast<sf::Vector2f>(start), static_cast<sf::Vector2f>(target)).size();
}

float MovementPath::lerp(float start, float end, float t) {
	return start + t * (end - start);
}

sf::Vector2f MovementPath::lerpPoint(const sf::Vector2f &point0, const sf::Vector2f &point1, float t) {
	return sf::Vector2f(
		lerp(point0.x, point1.x, t),
		lerp(point0.y, point1.y, t));
}

float MovementPath::diagonalDistance(const sf::Vector2f &point0, const sf::Vector2f &point1) {
	float dx = point1.x - point0.x;
	float dy = point1.y - point0.y;
	return std::max(std::abs(dx), std::abs(dy));
}

sf::Vector2u MovementPath::roundPoint(sf::Vector2f point) {
	return sf::Vector2u(static_cast<unsigned int>(std::round(point.x)), static_cast<unsigned int>(std::round(point.y)));
}

std::vector<sf::Vector2u> MovementPath::buildLinePathPositions(sf::Vector2f start, sf::Vector2f target, float length) {
	std::vector<sf::Vector2u> points;

	float n = diagonalDistance(start, target);

	for (float step = 0; step <= (length == 0 ? n : length); step++) {
		float t = (n == 0) ? 0.0f : step / n;

		points.push_back(roundPoint(lerpPoint(start, target, t)));
	}

	points.erase(points.begin()); // Remove the first position (the start position).

	return points;
}