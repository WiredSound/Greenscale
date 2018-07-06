#pragma once

#include "TileManager.h"
#include "MapLayer.h"
#include "../debugging.h"
#include "pathfinding/MovementPath.h"

using TileColourPair = std::pair<IDs::Tiles, sf::Color>;

class TileLayer : public MapLayer {
public:
	TileLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, std::shared_ptr<sf::Texture> layerTexture, TileManager tileManager);
	const Tile &getTileAt(sf::Vector2u pos);
	sf::Color getColourAt(sf::Vector2u pos);
	unsigned int getTileCount();
	void setTileAt(sf::Vector2u pos, IDs::Tiles id, bool useDefaultColour = true);
	void setTileAt(sf::Vector2u pos, IDs::Tiles id, sf::Color colour);
	void setColourAt(sf::Vector2u, sf::Color colour);
	void fill(IDs::Tiles id);
	void fillRect(IDs::Tiles id, sf::Vector2u pos, sf::Vector2u rectSize);
	void fillRect(IDs::Tiles id, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);
	void colourPath(MovementPath path, sf::Color colour);
	void resetColourPath(MovementPath path);
	void resetColouring();
	void updateVertices() override;

	bool save(std::string path);
	bool load(std::string path);

private:
	std::unique_ptr<TileColourPair[]> tiles;

	TileManager manager;

	sf::Vertex *getQuadPtr(sf::Vector2u pos);
	void setupTileQuad(sf::Vector2u pos);
	void setQuadPosition(sf::Vertex *quad, sf::Vector2u pos);
	void setQuadTexture(sf::Vertex *quad, sf::Vector2u textureCoords);
	void setQuadColour(sf::Vertex *quad, sf::Color colour);
};