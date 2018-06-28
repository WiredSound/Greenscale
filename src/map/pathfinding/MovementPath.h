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
	//MovementPath(sf::Vector2u pos, bool pathComplete);
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
	static MovementPath buildLinePath(sf::Vector2u start, sf::Vector2u target, unsigned int length = 10);
	static unsigned int distanceFromTo(sf::Vector2u start, sf::Vector2u target);

private:
	static float lerp(float start, float end, float t);
	static sf::Vector2f lerpPoint(const sf::Vector2f &point0, const sf::Vector2f &point1, float t);
	static float diagonalDistance(const sf::Vector2f &point0, const sf::Vector2f &point1);
	static sf::Vector2u roundPoint(sf::Vector2f point);
	static std::vector<sf::Vector2u> buildLinePathPositions(sf::Vector2f start, sf::Vector2f target, float length = 0);
};