#pragma once

#include "MapGenerator.h"

class PlainsGenerator : public MapGenerator {
public:
	PlainsGenerator(IDs::Tiles tile, sf::Color colourMin, sf::Color colourMax);

	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) override;

private:
	IDs::Tiles groundTile;
	sf::Color minColour;
	sf::Color maxColour;
};