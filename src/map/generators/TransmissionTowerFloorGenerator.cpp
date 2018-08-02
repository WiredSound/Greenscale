#include "TransmissionTowerFloorGenerator.h"

TransmissionTowerFloorGenerator::TransmissionTowerFloorGenerator(unsigned int radius, unsigned int thickness,
	IDs::Tiles towerMainWallTile, sf::Color towerMainWallColour, IDs::Tiles towerMainFloorTile, sf::Color towerMainFloorColour)
	: towerRadius(radius), wallThickness(thickness),
	mainWallTile(towerMainWallTile), mainWallColour(towerMainWallColour), mainFloorTile(towerMainFloorTile), mainFloorColour(towerMainFloorColour) {}

void TransmissionTowerFloorGenerator::generateTiles(std::unique_ptr<TileLayer> &tiles) {
	const sf::Vector2u centre = tiles->getCentre();

	constructCircularRoom(tiles, centre, towerRadius, mainWallTile, mainWallColour, mainFloorTile, mainFloorColour, 5);

	unsigned int innerCircleRadius = towerRadius / 2.5f;
	unsigned int innerCircleOffset = towerRadius / 2u;
	constructCircularRoom(tiles, sf::Vector2u(centre.x, centre.y + innerCircleOffset), innerCircleRadius, mainWallTile, mainWallColour, mainFloorTile, mainFloorColour, 1);
	constructCircularRoom(tiles, sf::Vector2u(centre.x, centre.y - innerCircleOffset), innerCircleRadius, mainWallTile, mainWallColour, mainFloorTile, mainFloorColour, 1);
	constructMachineryInCircularArea(tiles, sf::Vector2u(centre.x, centre.y - innerCircleOffset), innerCircleRadius, mainFloorColour);
}

void TransmissionTowerFloorGenerator::constructCircularRoom(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centrePoint, unsigned int radius, IDs::Tiles wallTile, sf::Color wallColour,
	IDs::Tiles floorTile, sf::Color floorColour, unsigned int doorSize) {
	// Flooring:
	std::vector<sf::Vector2i> flooringPositions = GridHelp::buildFilledCircle(static_cast<sf::Vector2i>(centrePoint), radius);
	tiles->fill(floorTile, floorColour, 0, std::vector<sf::Vector2u>(flooringPositions.begin(), flooringPositions.end()));

	// Circular wall:
	std::vector<sf::Vector2i> outerWallPositions = GridHelp::buildCircle(static_cast<sf::Vector2i>(centrePoint), radius, wallThickness);
	tiles->fill(mainWallTile, mainWallColour, 0, std::vector<sf::Vector2u>(outerWallPositions.begin(), outerWallPositions.end()));

	// Door:
	unsigned int halfDoorSize = std::ceil(doorSize / 2u);
	unsigned int baseY = centrePoint.y - radius;

	for (unsigned int x = centrePoint.x - halfDoorSize; x <= centrePoint.x + halfDoorSize; x++) {
		tiles->setTileAt(sf::Vector2u(x, baseY), IDs::DOOR);

		// Clear the wall tiles in front of the door:
		for (unsigned int clearanceY = 1; clearanceY < wallThickness; clearanceY++)
			tiles->setTileAt(sf::Vector2u(x, baseY + clearanceY), floorTile, floorColour);
	}
}

void TransmissionTowerFloorGenerator::constructMachineryInCircularArea(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centrePoint, unsigned int radius, sf::Color colour) {
	// Square area of vertical lines of machinery:
	unsigned int halfRadius = radius / 2u;
	unsigned int spacing = (radius % 2 == 0) ? 2 : 3; // Machine lines are spaced every 2 or 3 tiles apart depending on which divides equally into the radius.

	for (unsigned int x = centrePoint.x - halfRadius; x <= centrePoint.x + halfRadius; x += spacing)
		constructVerticalMachineryLine(tiles, sf::Vector2u(x, centrePoint.y), halfRadius, colour);
}

void TransmissionTowerFloorGenerator::constructVerticalMachineryLine(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centre, unsigned int radius, sf::Color colour) {
	tiles->setTileAt(sf::Vector2u(centre.x, centre.y - radius), IDs::Tiles::MACHINARY_NODE, colour, 0);
	tiles->setTileAt(sf::Vector2u(centre.x, centre.y + radius), IDs::Tiles::MACHINARY_NODE, colour, 2);

	for (unsigned int y = centre.y - radius + 1; y < centre.y + radius; y++)
		tiles->setTileAt(sf::Vector2u(centre.x, y), IDs::Tiles::MACHINARY_CONNECTION, colour, 0);
}