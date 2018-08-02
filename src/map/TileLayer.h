#pragma once

#include "TileManager.h"
#include "MapLayer.h"
#include "../debugging.h"
#include "pathfinding/MovementPath.h"

struct TileColourOrientation {
	IDs::Tiles id;
	sf::Color colour;
	char orientation;
};

class TileLayer : public MapLayer {
public:
	TileLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, std::shared_ptr<sf::Texture> layerTexture, TileManager tileManager);

	unsigned int getTileCount();

	void setTileAt(sf::Vector2u pos, IDs::Tiles id, sf::Color colour, char orientation = 0); // Colour specified.
	void setTileAt(sf::Vector2u pos, IDs::Tiles id, char orientation = 0); // Default colour for tile type.
	void setIdAt(sf::Vector2u pos, IDs::Tiles id); // Does not change the existing colour at the given position.
	void setColourAt(sf::Vector2u pos, sf::Color colour);
	void setOrientationAt(sf::Vector2u pos, char orientation);

	const Tile &getTileAt(sf::Vector2u pos);
	IDs::Tiles getIdAt(sf::Vector2u pos);
	sf::Color getColourAt(sf::Vector2u pos);
	char getOrientationAt(sf::Vector2u pos);
	int getOrientationDegreesAt(sf::Vector2u pos);

	void fillAll(IDs::Tiles id);
	void fillAll(IDs::Tiles id, sf::Color colour);
	void fill(IDs::Tiles id, std::vector<sf::Vector2u> positions);
	void fill(IDs::Tiles id, sf::Color colour, char orientation, std::vector<sf::Vector2u> positions);
	void fillRect(IDs::Tiles id, sf::Vector2u pos, sf::Vector2u rectSize);
	void fillRect(IDs::Tiles id, sf::Color colour, char orientation, sf::Vector2u pos, sf::Vector2u rectSize);

	void colourPath(MovementPath path, sf::Color colour);
	void resetColourPath(MovementPath path);
	void resetColouring();

	void updateVertices() override;

	bool save(std::string path);
	bool load(std::string path);

private:
	std::unique_ptr<TileColourOrientation[]> tiles;

	TileManager manager;

	sf::Vertex *getQuadPtr(sf::Vector2u pos);
	void setupTileQuad(sf::Vector2u pos);
	void setQuadPosition(sf::Vertex *quad, sf::Vector2u pos, char orientation);
	void setQuadTexture(sf::Vertex *quad, sf::Vector2u textureCoords);
	void setQuadColour(sf::Vertex *quad, sf::Color colour);
};