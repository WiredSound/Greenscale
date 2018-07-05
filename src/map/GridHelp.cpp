#include "GridHelp.h"

#include <algorithm>

std::vector<sf::Vector2u> GridHelp::buildLine(sf::Vector2f start, sf::Vector2f target, float length) {
	std::vector<sf::Vector2u> points;

	float n = GridHelp::diagonalDistance(start, target);

	for (float step = 0; step <= (length == 0 ? n : length); step++) {
		float t = (n == 0) ? 0.0f : step / n;

		points.push_back(GridHelp::roundPoint(GridHelp::lerpPoint(start, target, t)));
	}

	points.erase(points.begin()); // Remove the first position (the start position).

	return points;
}

float GridHelp::lerp(float start, float end, float t) {
	return start + t * (end - start);
}

sf::Vector2f GridHelp::lerpPoint(const sf::Vector2f &point0, const sf::Vector2f &point1, float t) {
	return sf::Vector2f(
		lerp(point0.x, point1.x, t),
		lerp(point0.y, point1.y, t));
}

float GridHelp::diagonalDistance(const sf::Vector2f &point0, const sf::Vector2f &point1) {
	float dx = point1.x - point0.x;
	float dy = point1.y - point0.y;
	return std::max(std::abs(dx), std::abs(dy));
}

sf::Vector2u GridHelp::roundPoint(sf::Vector2f point) {
	return sf::Vector2u(static_cast<unsigned int>(std::round(point.x)), static_cast<unsigned int>(std::round(point.y)));
}

std::vector<sf::Vector2i> GridHelp::buildCircle(sf::Vector2i origin, int radius) {
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	std::vector<sf::Vector2i> points;

	while (x >= y) {
		points.push_back(sf::Vector2i(origin.x + x, origin.y + y));
		points.push_back(sf::Vector2i(origin.x + y, origin.y + x));
		points.push_back(sf::Vector2i(origin.x - y, origin.y + x));
		points.push_back(sf::Vector2i(origin.x - x, origin.y + y));
		points.push_back(sf::Vector2i(origin.x - x, origin.y - y));
		points.push_back(sf::Vector2i(origin.x - y, origin.y - x));
		points.push_back(sf::Vector2i(origin.x + y, origin.y - x));
		points.push_back(sf::Vector2i(origin.x + x, origin.y - y));

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