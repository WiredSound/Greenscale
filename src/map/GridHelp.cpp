#include "GridHelp.h"

#include <algorithm>

float lerp(float start, float end, float t);
sf::Vector2f lerpPoint(const sf::Vector2f &point0, const sf::Vector2f &point1, float t);
float diagonalDistance(const sf::Vector2f &point0, const sf::Vector2f &point1);
sf::Vector2u roundPoint(sf::Vector2f point);

/**
 * Finds all the grid positions from the start to the target position using linear interpolation.
 * \param start Start position.
 * \param target Target position.
 * \param length Specify a maximum length for the line produced.
 * \return `std::vector` of positions that make up the line.
 */
std::vector<sf::Vector2u> GridHelp::buildLine(sf::Vector2f start, sf::Vector2f target, float length) {
	std::vector<sf::Vector2u> points;

	float n = diagonalDistance(start, target);

	for (float step = 0; step <= (length == 0 ? n : length); step++) {
		float t = (n == 0) ? 0.0f : step / n;

		points.push_back(roundPoint(lerpPoint(start, target, t)));
	}

	points.erase(points.begin()); // Remove the first position (the start position).

	return points;
}

/**
 * Constructs a hollow circle of a given radius about the specified origin point. See GridHelp::buildFilledCircle for constructing a filled-in circle.
 * \param origin Origin point of the circle.
 * \param radius Radius of the circle.
 * \param thickness Thickness of the circle (defaults to 1).
 * \return `std::vector` of the positions that make up the constructed circle.
 */
std::vector<sf::Vector2i> GridHelp::buildCircle(sf::Vector2i origin, int radius, int thickness) { // TODO: Potentially make this a template so the vector type can be specified.
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	std::vector<sf::Vector2i> points;

	while (x >= y) {
		for (int i = 0; i < thickness; i++) {
			points.push_back(sf::Vector2i(origin.x + x + i, origin.y + y));
			points.push_back(sf::Vector2i(origin.x + y + i, origin.y + x));
			points.push_back(sf::Vector2i(origin.x - y - i, origin.y + x));
			points.push_back(sf::Vector2i(origin.x - x - i, origin.y + y));
			points.push_back(sf::Vector2i(origin.x - x - i, origin.y - y));
			points.push_back(sf::Vector2i(origin.x - y - i, origin.y - x));
			points.push_back(sf::Vector2i(origin.x + y + i, origin.y - x));
			points.push_back(sf::Vector2i(origin.x + x + i, origin.y - y));
			if (i > 0) { // Prevent doubling up on the first time around.
				points.push_back(sf::Vector2i(origin.x + x, origin.y + y + i));
				points.push_back(sf::Vector2i(origin.x + y, origin.y + x + i));
				points.push_back(sf::Vector2i(origin.x - y, origin.y + x + i));
				points.push_back(sf::Vector2i(origin.x - x, origin.y + y + i));
				points.push_back(sf::Vector2i(origin.x - x, origin.y - y - i));
				points.push_back(sf::Vector2i(origin.x - y, origin.y - x - i));
				points.push_back(sf::Vector2i(origin.x + y, origin.y - x - i));
				points.push_back(sf::Vector2i(origin.x + x, origin.y - y - i));
			}
		}

		if (err <= 0) {
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0) {
			x--;
			dx += 2;
			err += dx - (radius << 1);
		}
	}

	return points;
}

/**
 * Builds a filled-in circle of the specified radius about the given origin point.
 * \param origin Origin point of the circle.
 * \param radius Radius of the circle.
 * \return `std::vector` of the positions that make up the constructed circle.
 */
std::vector<sf::Vector2i> GridHelp::buildFilledCircle(sf::Vector2i origin, int radius) {
	std::vector<sf::Vector2i> points;

	for (int y = -radius; y <= radius; y++) {
		for (int x = -radius; x <= radius; x++) {
			if (x * x + y * y <= radius * radius)
				points.push_back(sf::Vector2i(origin.x + x, origin.y + y));
		}
	}

	return points;
}

float lerp(float start, float end, float t) {
	return start + t * (end - start);
}

sf::Vector2f lerpPoint(const sf::Vector2f &point0, const sf::Vector2f &point1, float t) {
	return sf::Vector2f(
		lerp(point0.x, point1.x, t),
		lerp(point0.y, point1.y, t));
}

float diagonalDistance(const sf::Vector2f &point0, const sf::Vector2f &point1) {
	float dx = point1.x - point0.x;
	float dy = point1.y - point0.y;
	return std::max(std::abs(dx), std::abs(dy));
}

sf::Vector2u roundPoint(sf::Vector2f point) {
	return sf::Vector2u(static_cast<unsigned int>(std::round(point.x)), static_cast<unsigned int>(std::round(point.y)));
}