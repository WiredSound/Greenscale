#pragma once

#include "MapGenerator.h"
#include "../GridHelp.h"
#include "../../IDs.h"

class TransmissionTowerFloorGenerator : public MapGenerator {
public:
	TransmissionTowerFloorGenerator(unsigned int radius, unsigned int thickness, IDs::Tiles towerMainWallTile, sf::Color towerMainWallColour, IDs::Tiles towerMainFloorTile, sf::Color towerMainFloorColour);
	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) override;

protected:
	void constructCircularRoom(std::unique_ptr<TileLayer> &tiles, sf::Vector2i centrePoint, unsigned int radius, IDs::Tiles wallTile, sf::Color wallColour, IDs::Tiles floorTile, sf::Color floorColour,
		unsigned int doorSize);
	void buildDoor(std::unique_ptr<TileLayer> &tiles, unsigned int width, const sf::Vector2i &centre);
	void buildMachineLine(std::unique_ptr<TileLayer> &tiles, int length, sf::Vector2u middlePoint);

private:
	unsigned int towerRadius, wallThickness;
	IDs::Tiles mainWallTile;
	sf::Color mainWallColour;
	IDs::Tiles mainFloorTile;
	sf::Color mainFloorColour;
};