#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
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

private:
	std::vector<sf::Vector2u> path;

	sf::Vector2u startPos;
	sf::Vector2u targetPos;

	bool complete;
	unsigned int length;
	unsigned int pathIndex;

public:
	static MovementPath buildLinePath(const sf::Vector2u &start, const sf::Vector2u &target);
	static unsigned int distanceFromTo(const sf::Vector2u &from, const sf::Vector2u &to);

private:
	static std::vector<sf::Vector2u> buildLinePathPositions(const sf::Vector2u &start, const sf::Vector2u &target);
	static std::vector<sf::Vector2u> buildLinePathLow(const sf::Vector2u &start, const sf::Vector2u &target, bool append);
	static std::vector<sf::Vector2u> buildLinePathHigh(const sf::Vector2u &start, const sf::Vector2u &target, bool append);
	static void addPosition(const sf::Vector2u pos, std::vector<sf::Vector2u> &list, bool append);
};