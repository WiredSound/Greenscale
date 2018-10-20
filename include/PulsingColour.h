#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>

class PulsingColour {
public:
	PulsingColour(float minFraction, float maxFraction, float amount);
	sf::Color getColour(sf::Color colour);

private:
	float fraction;
	float min;
	float max;
	float changeAmount;
	bool increasing;
	sf::Clock clock;
};