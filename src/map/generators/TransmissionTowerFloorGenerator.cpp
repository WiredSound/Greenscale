#include "TransmissionTowerFloorGenerator.h"

TransmissionTowerFloorGenerator::TransmissionTowerFloorGenerator(unsigned int radius, unsigned int thickness,
	IDs::Tiles towerMainWallTile, sf::Color towerMainWallColour, IDs::Tiles towerMainFloorTile, sf::Color towerMainFloorColour)
	: towerRadius(radius), wallThickness(thickness),
	mainWallTile(towerMainWallTile), mainWallColour(towerMainWallColour), mainFloorTile(towerMainFloorTile), mainFloorColour(towerMainFloorColour) {}

void TransmissionTowerFloorGenerator::generateTiles(std::unique_ptr<TileLayer> &tiles) {
	const sf::Vector2u centre = tiles->getCentre();

	constructCircularRoom(tiles, centre, towerRadius, mainWallTile, mainWallColour, mainFloorTile, mainFloorColour, 5);

	unsigned int innerCircleRadius = towerRadius / 3;
	unsigned int innerCircleOffset = towerRadius / 1.8f;
	auto innerCirclePositions = { sf::Vector2u(centre.x + innerCircleOffset, centre.y), sf::Vector2u(centre.x - innerCircleOffset, centre.y),
		sf::Vector2u(centre.x, centre.y + innerCircleOffset), sf::Vector2u(centre.x, centre.y - innerCircleOffset) };

	for (sf::Vector2u position : innerCirclePositions) {
		constructCircularRoom(tiles, position, innerCircleRadius, mainWallTile, mainWallColour, mainFloorTile, mainFloorColour, 1);
		constructMachineryInCircularArea(tiles, position, innerCircleRadius, mainFloorColour);
	}
}

void TransmissionTowerFloorGenerator::constructCircularRoom(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centre, unsigned int radius, IDs::Tiles wallTile, sf::Color wallColour,
	IDs::Tiles floorTile, sf::Color floorColour, unsigned int doorSize) {
	// Flooring:
	std::vector<sf::Vector2i> flooringPositions = GridHelp::buildFilledCircle(static_cast<sf::Vector2i>(centre), radius);
	tiles->fill(floorTile, floorColour, 0, std::vector<sf::Vector2u>(flooringPositions.begin(), flooringPositions.end()));

	// Circular wall:
	std::vector<sf::Vector2i> outerWallPositions = GridHelp::buildCircle(static_cast<sf::Vector2i>(centre), radius, wallThickness);
	tiles->fill(mainWallTile, mainWallColour, 0, std::vector<sf::Vector2u>(outerWallPositions.begin(), outerWallPositions.end()));

	// Door:
	unsigned int halfDoorSize = std::ceil(doorSize / 2u);
	unsigned int baseY = centre.y - radius;

	for (unsigned int x = centre.x - halfDoorSize; x <= centre.x + halfDoorSize; x++) {
		tiles->setTileAt(sf::Vector2u(x, baseY), IDs::DOOR);

		// Clear the wall tiles in front of the door:
		for (unsigned int clearanceY = 1; clearanceY < wallThickness; clearanceY++)
			tiles->setTileAt(sf::Vector2u(x, baseY + clearanceY), floorTile, floorColour);
	}
}

void TransmissionTowerFloorGenerator::constructMachineryInCircularArea(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centre, unsigned int radius, sf::Color colour) {
	switch (random.integerRange(0, 1)) {
	case 0: constructTerminalMachinery(tiles, centre, radius, colour); break;
	case 1: constructMachineryLines(tiles, centre, radius, colour); break;
	}
}

void TransmissionTowerFloorGenerator::constructMachineryLines(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centre, unsigned int radius, sf::Color colour) {
	unsigned int halfRadius = radius / 2u;
	unsigned int spacing = (radius % 2 == 0) ? 2 : 3; // Machine lines are spaced either 2 or 3 tiles apart from one another depending on which divides equally into the radius.

	for (unsigned int x = centre.x - halfRadius; x <= centre.x + halfRadius; x += spacing) {
		tiles->setTileAt(sf::Vector2u(x, centre.y - halfRadius), IDs::Tiles::MACHINERY_NODE, colour, 0);
		tiles->setTileAt(sf::Vector2u(x, centre.y + halfRadius), IDs::Tiles::MACHINERY_NODE, colour, 2);

		for (unsigned int y = centre.y - halfRadius + 1; y < centre.y + halfRadius; y++)
			tiles->setTileAt(sf::Vector2u(x, y), IDs::Tiles::MACHINERY_CONNECTION, colour, 0);
	}
}

void TransmissionTowerFloorGenerator::constructTerminalMachinery(std::unique_ptr<TileLayer> &tiles, sf::Vector2u centre, unsigned int radius, sf::Color colour) {
	tiles->setTileAt(centre, IDs::MACHINERY_TERMINAL, colour);
}