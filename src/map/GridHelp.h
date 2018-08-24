#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

/**
 * Various helper functions for building lines and circles on grids.
 */
namespace GridHelp {
	std::vector<sf::Vector2u> buildLine(sf::Vector2f start, sf::Vector2f target, float length = 0);
	std::vector<sf::Vector2i> buildCircle(sf::Vector2i origin, int radius, int thickness = 1);
	std::vector<sf::Vector2i> buildFilledCircle(sf::Vector2i origin, int radius);
};