#include "TransmissionTowerFloorGenerator.h"

TransmissionTowerFloorGenerator::TransmissionTowerFloorGenerator(unsigned int radius, unsigned int thickness,
	IDs::Tiles towerMainWallTile, sf::Color towerMainWallColour, IDs::Tiles towerMainFloorTile, sf::Color towerMainFloorColour)
	: towerRadius(radius), wallThickness(thickness),
	mainWallTile(towerMainWallTile), mainWallColour(towerMainWallColour), mainFloorTile(towerMainFloorTile), mainFloorColour(towerMainFloorColour) {}

void TransmissionTowerFloorGenerator::generateTiles(std::unique_ptr<TileLayer> &tiles) {
	const auto centre = static_cast<sf::Vector2i>(tiles->getCentre());

	constructCircularRoom(tiles, centre, towerRadius, mainWallTile, mainWallColour, mainFloorTile, mainFloorColour, 3);

	int innerCircleRadius = towerRadius / 2.5f;
	int innerCircleOffset = towerRadius / 2;
	constructCircularRoom(tiles, sf::Vector2i(centre.x, centre.y + innerCircleOffset), innerCircleRadius, mainWallTile, mainWallColour, mainFloorTile, mainFloorColour, 3);
	constructCircularRoom(tiles, sf::Vector2i(centre.x, centre.y - innerCircleOffset), innerCircleRadius, mainWallTile, mainWallColour, mainFloorTile, mainFloorColour, 3);
}

void TransmissionTowerFloorGenerator::constructCircularRoom(std::unique_ptr<TileLayer> &tiles, sf::Vector2i centrePoint, unsigned int radius, IDs::Tiles wallTile, sf::Color wallColour,
	IDs::Tiles floorTile, sf::Color floorColour, unsigned int doorSize) {
	// Flooring:
	std::vector<sf::Vector2i> flooringPositions = GridHelp::buildFilledCircle(centrePoint, radius);
	tiles->fill(floorTile, floorColour, 0, std::vector<sf::Vector2u>(flooringPositions.begin(), flooringPositions.end()));

	// Circular wall:
	std::vector<sf::Vector2i> outerWallPositions = GridHelp::buildCircle(centrePoint, radius, wallThickness);
	tiles->fill(mainWallTile, mainWallColour, 0, std::vector<sf::Vector2u>(outerWallPositions.begin(), outerWallPositions.end()));

	// Door:
	int y = centrePoint.y - radius - wallThickness + 2;

	int xStart = centrePoint.x - static_cast<int>(std::floor(doorSize / 2));
	int xEnd = xStart + doorSize;

	for (int x = xStart; x < xEnd; x++)
		tiles->setIdAt(sf::Vector2u(x, y), IDs::DOOR); // Place the door tiles.

	int clearance = static_cast<int>(std::ceil(doorSize / 2));

	for (int x = xStart - clearance; x < xEnd + clearance; x++) {
		for (int i = 1; i < static_cast<int>(doorSize); i++)
			tiles->setTileAt(sf::Vector2u(x, y + i), mainFloorTile, mainFloorColour, 0); // Clear any wall tiles that may obstruct the door.
	}
}

void TransmissionTowerFloorGenerator::buildMachineLine(std::unique_ptr<TileLayer> &tiles, int length, sf::Vector2u middlePoint) {
}