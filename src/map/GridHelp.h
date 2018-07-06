#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

namespace GridHelp {
	// Line building and its required helper functions:
	std::vector<sf::Vector2u> buildLine(sf::Vector2f start, sf::Vector2f target, float length = 0);
	float lerp(float start, float end, float t);
	sf::Vector2f lerpPoint(const sf::Vector2f &point0, const sf::Vector2f &point1, float t);
	float diagonalDistance(const sf::Vector2f &point0, const sf::Vector2f &point1);
	sf::Vector2u roundPoint(sf::Vector2f point);

	// Circle building:
	std::vector<sf::Vector2i> buildCircle(sf::Vector2i origin, int radius);
	std::vector<sf::Vector2i> buildFilledCircle(sf::Vector2i origin, int radius);
}