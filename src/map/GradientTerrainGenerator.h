#pragma once

#include <memory>
#include <FastNoise.h>
#include "TileLayer.h"

class GradientTerrainGenerator {
public:
	GradientTerrainGenerator(FastNoise::NoiseType type, float frequency, IDs::Tiles tileId, sf::Color colourMin, sf::Color colourMax);
	void fillGradientTerrain(std::unique_ptr<TileLayer> &tiles, sf::Vector2u areaPosition, sf::Vector2u areaSize);
	sf::Color getColourAt(sf::Vector2u position);
	float getPercentageAt(sf::Vector2u position);

	FastNoise noiseGenerator;
	IDs::Tiles tile;
	sf::Color minColour;
	sf::Color maxColour;
	sf::Color colourDifference;
};