#pragma once

#include "TileManager.h"
#include "MapLayer.h"
#include "../debugging.h"
#include "pathfinding/MovementPath.h"

class TileLayer : public MapLayer {
public:
	TileLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, sf::Vector2f textureSizeTile, std::shared_ptr<sf::Texture> layerTexture, TileManager tileManager);
	const Tile &getTileAt(sf::Vector2u pos);
	void setTileAt(sf::Vector2u pos, IDs::Tiles id);
	void fill(IDs::Tiles id);
	void fillRect(IDs::Tiles id, sf::Vector2u pos, sf::Vector2u rectSize);
	void fillRect(IDs::Tiles id, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);
	void colourPath(MovementPath path, sf::Color colour);
	void resetColourPath(MovementPath path);
	void resetColouring();
	void updateVertices() override;

private:
	std::unique_ptr<IDs::Tiles[]> tiles;

	TileManager manager;

	sf::Vertex *getQuadPtr(sf::Vector2u pos);
	void setupTileQuad(sf::Vector2u pos);
	void setQuadPosition(sf::Vertex *quad, sf::Vector2u pos);
	void setQuadTexture(sf::Vertex *quad, sf::Vector2u textureCoords);
	void setQuadColour(sf::Vertex *quad, sf::Color colour);
};