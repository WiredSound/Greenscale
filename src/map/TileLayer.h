#pragma once

#include "TileManager.h"
#include "MapLayer.h"
#include "../debugging.h"
#include "pathfinding/MovementPath.h"

#define NO_COLOUR sf::Color(0, 0, 0, 255)

class TileLayer : public MapLayer {
public:
	TileLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, std::shared_ptr<sf::Texture> layerTexture, TileManager tileManager);
	const Tile &getTileAt(sf::Vector2u pos);
	sf::Color getColourAt(sf::Vector2u pos);
	void setTileAt(sf::Vector2u pos, IDs::Tiles id);
	void setColourAt(sf::Vector2u, sf::Color colour);
	void fill(IDs::Tiles id);
	void fillRect(IDs::Tiles id, sf::Vector2u pos, sf::Vector2u rectSize);
	void fillRect(IDs::Tiles id, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);
	void colourPath(MovementPath path, sf::Color colour);
	void resetColourPath(MovementPath path);
	void resetColouring();
	void updateVertices() override;

private:
	std::unique_ptr<std::pair<IDs::Tiles, sf::Color>[]> tiles;

	TileManager manager;

	sf::Vertex *getQuadPtr(sf::Vector2u pos);
	void setupTileQuad(sf::Vector2u pos);
	void setQuadPosition(sf::Vertex *quad, sf::Vector2u pos);
	void setQuadTexture(sf::Vertex *quad, sf::Vector2u textureCoords);
	void setQuadColour(sf::Vertex *quad, sf::Color colour);
};