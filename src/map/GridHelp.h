#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

class GridHelp {
	// Line building and its required helper functions:
public:
	static std::vector<sf::Vector2u> buildLine(sf::Vector2f start, sf::Vector2f target, float length = 0);
private:
	static float lerp(float start, float end, float t);
	static sf::Vector2f lerpPoint(const sf::Vector2f &point0, const sf::Vector2f &point1, float t);
	static float diagonalDistance(const sf::Vector2f &point0, const sf::Vector2f &point1);
	static sf::Vector2u roundPoint(sf::Vector2f point);

	// Circle building:
public:
	static std::vector<sf::Vector2i> buildCircle(sf::Vector2i origin, int radius, int thickness = 1);
	static std::vector<sf::Vector2i> buildFilledCircle(sf::Vector2i origin, int radius);
};