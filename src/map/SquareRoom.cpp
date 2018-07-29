#include "SquareRoom.h"

SquareRoom::SquareRoom(std::string roomName, sf::Vector2u roomPosition, sf::Vector2u roomSize, IDs::Tiles flooring, IDs::Tiles walls)
	: MapRoom(roomName, roomPosition, roomSize), flooringTile(flooring), wallTile(walls) {}

void SquareRoom::build(std::unique_ptr<TileLayer> &tiles) {
	tiles->fillRect(flooringTile, position, size);
	tiles->fillRect(wallTile, position, sf::Vector2u(size.x, 1)); // Top wall.
	tiles->fillRect(wallTile, sf::Vector2u(position.x, position.y + size.y - 1), sf::Vector2u(size.x, 1)); // Bottom wall.
	tiles->fillRect(wallTile, position, sf::Vector2u(1, size.y)); // Left wall.
	tiles->fillRect(wallTile, sf::Vector2u(position.x + size.x - 1, position.y), sf::Vector2u(1, size.y)); // Left wall.
	tiles->setIdAt(sf::Vector2u(position.x + (size.x / 2), position.y + size.y - 1), flooringTile); // Temporary door.
}