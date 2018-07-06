#pragma once

#include "MapGenerator.h"
#include "../GridHelp.h"
#include "../../IDs.h"

class TransmissionTowerFloorGenerator : public MapGenerator {
public:
	TransmissionTowerFloorGenerator(unsigned int towerRadius, IDs::Tiles towerMainWallTile, sf::Color towerMainWallColour, IDs::Tiles towerMainFloorTile, sf::Color towerMainFloorColour);
	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) override;

protected:
	sf::Vector2i getCentre(std::unique_ptr<TileLayer> &tiles);

private:
	unsigned int radius;
	IDs::Tiles mainWallTile;
	sf::Color mainWallColour;
	IDs::Tiles mainFloorTile;
	sf::Color mainFloorColour;
};