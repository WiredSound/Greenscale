#include "TransmissionTowerFloorGenerator.h"

TransmissionTowerFloorGenerator::TransmissionTowerFloorGenerator(unsigned int towerRadius, unsigned int towerThickness,
	IDs::Tiles towerMainWallTile, sf::Color towerMainWallColour, IDs::Tiles towerMainFloorTile, sf::Color towerMainFloorColour)
	: radius(towerRadius), thickness(towerThickness),
	mainWallTile(towerMainWallTile), mainWallColour(towerMainWallColour), mainFloorTile(towerMainFloorTile), mainFloorColour(towerMainFloorColour) {}

void TransmissionTowerFloorGenerator::generateTiles(std::unique_ptr<TileLayer> &tiles) {
	sf::Vector2i centre = getCentre(tiles);

	fillTiles<sf::Vector2i>(tiles, GridHelp::buildFilledCircle(centre, radius), mainFloorTile, mainFloorColour);
	fillTiles<sf::Vector2i>(tiles, GridHelp::buildCircle(centre, radius, thickness), mainWallTile, mainWallColour);

	buildDoor(tiles, static_cast<int>(std::ceil(static_cast<float>(radius) / 10)), centre);
}

sf::Vector2i TransmissionTowerFloorGenerator::getCentre(std::unique_ptr<TileLayer> &tiles) {
	return sf::Vector2i(std::round(tiles->size.x / 2), std::round(tiles->size.y / 2));
}

void TransmissionTowerFloorGenerator::buildDoor(std::unique_ptr<TileLayer> &tiles, int width, const sf::Vector2i &centre) {
	int y = centre.y - radius - thickness + 2;

	int xStart = centre.x - static_cast<int>(std::floor(width / 2));
	int xEnd = xStart + width;

	for (int x = xStart; x < xEnd; x++)
		tiles->setTileAt(sf::Vector2u(x, y), IDs::DOOR); // Place the door tiles.

	int clearance = static_cast<int>(std::ceil(width / 2));

	for (int x = xStart - clearance; x < xEnd + clearance; x++) {
		for (int i = 1; i < thickness; i++)
			tiles->setTileAt(sf::Vector2u(x, y + i), mainFloorTile, mainFloorColour); // Clear any wall tiles that may obstruct the door.
	}
}