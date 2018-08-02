#pragma once

#include "MapGenerator.h"
#include "../GridHelp.h"
#include "../../IDs.h"

class TransmissionTowerFloorGenerator : public MapGenerator {
public:
	TransmissionTowerFloorGenerator(unsigned int radius, unsigned int thickness, IDs::Tiles towerMainWallTile, sf::Color towerMainWallColour, IDs::Tiles towerMainFloorTile, sf::Color towerMainFloorColour);
	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) override;

protected:
	void constructCircularRoom(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centre, unsigned int radius, IDs::Tiles wallTile, sf::Color wallColour, IDs::Tiles floorTile, sf::Color floorColour,
		unsigned int doorSize);
	void constructMachineryInCircularArea(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centre, unsigned int radius, sf::Color colour);
	void constructMachineryLines(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centre, unsigned int radius, sf::Color colour);
	void constructTerminalMachinery(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centre, unsigned int radius, sf::Color colour);

private:
	unsigned int towerRadius, wallThickness;
	IDs::Tiles mainWallTile, mainFloorTile;
	sf::Color mainWallColour, mainFloorColour;
};