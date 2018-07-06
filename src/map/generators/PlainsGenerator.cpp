#include "PlainsGenerator.h"

#include "../../Random.h"
#include "../GradientTerrainGenerator.h"

PlainsGenerator::PlainsGenerator(IDs::Tiles ground, sf::Color colourMin, sf::Color colourMax) : groundTile(ground), minColour(colourMin), maxColour(colourMax), shrubFrequency(0) {}

PlainsGenerator::PlainsGenerator(IDs::Tiles ground, sf::Color colourMin, sf::Color colourMax, std::vector<IDs::Tiles> shrubs, float frequency)
	: groundTile(ground), minColour(colourMin), maxColour(colourMax), shrubFrequency(frequency), shrubTiles(shrubs) {}

void PlainsGenerator::generateTiles(std::unique_ptr<TileLayer> &tiles) {
	GradientTerrainGenerator terrainGen(FastNoise::NoiseType::SimplexFractal, 0.1f, groundTile, minColour, maxColour);
	terrainGen.fillGradientTerrain(tiles, sf::Vector2u(0, 0), tiles->size);

	DEBUG_LOG(std::rand());

	for (unsigned int x = 0; x < tiles->size.x; x++) {
		for (unsigned int y = 0; y < tiles->size.y; y++) {
			if (Random::percentageChange(shrubFrequency))
				tiles->setTileAt(sf::Vector2u(x, y), shrubTiles[rand() % shrubTiles.size()], false);
		}
	}
}