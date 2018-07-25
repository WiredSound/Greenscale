#pragma once

#include <functional>
#include <vector>
#include <SFML/System/Vector2.hpp>
class GameMap;

class MovementPath {
public:
	MovementPath(sf::Vector2u pos); // Incomplete movement path.
	MovementPath(std::vector<sf::Vector2u> tiles); // Complete movement path.

	sf::Vector2u currentPosition();
	void nextPosition();
	bool reachedTarget();
	void resetPosition();
	unsigned int getIndex();
	unsigned int getLength();
	std::vector<sf::Vector2u> getPathTiles();

	bool isComplete();

	sf::Vector2u getStartPosition();
	sf::Vector2u getTargetPosition();

	void restrictLength(unsigned int size);
	void recursivelyShortenBasedOn(std::function<bool()> condition);

private:
	std::vector<sf::Vector2u> path;
	bool complete;
	unsigned int pathIndex;

public:
	static MovementPath buildLinePath(sf::Vector2u start, sf::Vector2u target, unsigned int length = 0);
	static unsigned int distanceFromTo(sf::Vector2u start, sf::Vector2u target);
};