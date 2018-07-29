#include "GradientTerrainGenerator.h"

GradientTerrainGenerator::GradientTerrainGenerator(FastNoise::NoiseType type, float frequency, IDs::Tiles tileId, sf::Color colourMin, sf::Color colourMax)
	: tile(tileId), minColour(colourMin), maxColour(colourMax) {
	noiseGenerator.SetNoiseType(type);
	noiseGenerator.SetFrequency(frequency);
	noiseGenerator.SetFractalGain(0);

	colourDifference = sf::Color(maxColour.r - minColour.r, maxColour.g - minColour.g, maxColour.b - minColour.b);
}

void GradientTerrainGenerator::fillGradientTerrain(std::unique_ptr<TileLayer> &tiles, sf::Vector2u areaPosition, sf::Vector2u areaSize) {
	for (unsigned int x = areaPosition.x; x < areaPosition.x + areaSize.x; x++) {
		for (unsigned int y = areaPosition.y; y < areaPosition.y + areaSize.y; y++) {
			sf::Vector2u position(x, y);

			DEBUG_LOG_SPAM("Filling position (" << x << ", " << y << ") with colour percentage: " << getPercentageAt(position) * 100);

			tiles->setTileAt(position, tile, getColourAt(position), 0);
		}
	}
}

sf::Color GradientTerrainGenerator::getColourAt(sf::Vector2u position) {
	float percentage = getPercentageAt(position);

	return sf::Color(
		minColour.r + static_cast<sf::Uint8>(colourDifference.r * percentage),
		minColour.g + static_cast<sf::Uint8>(colourDifference.g * percentage),
		minColour.b + static_cast<sf::Uint8>(colourDifference.b * percentage), 255);
}

float GradientTerrainGenerator::getPercentageAt(sf::Vector2u position) {
	float noise = noiseGenerator.GetNoise(static_cast<FN_DECIMAL>(position.x), static_cast<FN_DECIMAL>(position.y));

	// By default noise values range from -1 to 1 so this lowers that range to 0 to 1.
	return (noise + 1.0f) / 2.0f;
}