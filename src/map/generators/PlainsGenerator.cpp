#include "PlainsGenerator.h"

#include "../GradientTerrainGenerator.h"

PlainsGenerator::PlainsGenerator(IDs::Tiles tile, sf::Color colourMin, sf::Color colourMax) : MapGenerator(), groundTile(tile), minColour(colourMin), maxColour(colourMax) {}

void PlainsGenerator::generateTiles(std::unique_ptr<TileLayer> &tiles) {
	GradientTerrainGenerator terrainGen(FastNoise::NoiseType::SimplexFractal, 0.1f, groundTile, minColour, maxColour);
	terrainGen.fillGradientTerrain(tiles, sf::Vector2u(0, 0), tiles->size);
}