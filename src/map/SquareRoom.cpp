#include "SquareRoom.h"

SquareRoom::SquareRoom(std::string roomName, sf::Vector2u roomPosition, sf::Vector2u roomSize, IDs::Tiles flooring, IDs::Tiles walls)
	: MapRoom(roomName, roomPosition, roomSize), flooringTile(flooring), wallTile(walls) {}

void SquareRoom::build(std::unique_ptr<TileLayer> &tiles) {
	tiles->fillRect(flooringTile, position.x, position.y, size.x, size.y);
	tiles->fillRect(wallTile, position.x, position.y, size.x, 1); // Top wall.
	tiles->fillRect(wallTile, position.x, position.y + size.y - 1, size.x, 1); // Bottom wall.
	tiles->fillRect(wallTile, position.x, position.y, 1, size.y); // Left wall.
	tiles->fillRect(wallTile, position.x + size.x - 1, position.y, 1, size.y); // Left wall.
	tiles->setTileAt(sf::Vector2u(position.x + (size.x / 2), position.y + size.y - 1), flooringTile); // Temporary door.
}