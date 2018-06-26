#include "PulsingColour.h"

#include <algorithm>

PulsingColour::PulsingColour(float minFraction, float maxFraction, float amount)
	: min(minFraction), max(maxFraction), fraction(minFraction), increasing(true), changeAmount(amount) {}

sf::Color PulsingColour::getColour(sf::Color colour) {
	if (clock.getElapsedTime() >= sf::milliseconds(10)) {
		clock.restart();

		if (increasing)
			fraction += changeAmount;
		else
			fraction -= changeAmount;

		if (fraction > max || fraction < min) increasing = !increasing;
	}

	return sf::Color(
		static_cast<sf::Uint8>(std::min(colour.r * fraction, 255.0f)),	// RED
		static_cast<sf::Uint8>(std::min(colour.g * fraction, 255.0f)),	// GREEN
		static_cast<sf::Uint8>(std::min(colour.b * fraction, 255.0f)),	// BLUE
		colour.a														// ALPHA
	);
}