#include "TransmissionTowerFloorGenerator.h"

TransmissionTowerFloorGenerator::TransmissionTowerFloorGenerator(unsigned int towerRadius, IDs::Tiles towerMainWallTile, sf::Color towerMainWallColour, IDs::Tiles towerMainFloorTile, sf::Color towerMainFloorColour)
	: radius(towerRadius), mainWallTile(towerMainWallTile), mainWallColour(towerMainWallColour), mainFloorTile(towerMainFloorTile), mainFloorColour(towerMainFloorColour) {}

void TransmissionTowerFloorGenerator::generateTiles(std::unique_ptr<TileLayer> &tiles) {
	sf::Vector2i centre = getCentre(tiles);

	fillTiles<sf::Vector2i>(tiles, GridHelp::buildFilledCircle(centre, radius), mainFloorTile, mainFloorColour);
	fillTiles<sf::Vector2i>(tiles, GridHelp::buildCircle(centre, radius), mainWallTile, mainWallColour);
}

sf::Vector2i TransmissionTowerFloorGenerator::getCentre(std::unique_ptr<TileLayer> &tiles) {
	return sf::Vector2i(std::round(tiles->size.x / 2), std::round(tiles->size.y / 2));
}