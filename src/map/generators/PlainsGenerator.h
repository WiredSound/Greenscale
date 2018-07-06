#pragma once

#include "MapGenerator.h"

class PlainsGenerator : public MapGenerator {
public:
	PlainsGenerator(IDs::Tiles ground, sf::Color colourMin, sf::Color colourMax);
	PlainsGenerator(IDs::Tiles ground, sf::Color colourMin, sf::Color colourMax, std::vector<IDs::Tiles> shrubs, float frequency);

	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) override;

private:
	IDs::Tiles groundTile;
	sf::Color minColour;
	sf::Color maxColour;
	std::vector<IDs::Tiles> shrubTiles;
	float shrubFrequency;
};