#include "TileLayer.h"

#include <fstream>

TileLayer::TileLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, std::shared_ptr<sf::Texture> layerTexture, TileManager tileManager)
	: MapLayer(layerSize, sizeTile, tileManager.getSingleTileTextureSize(), layerTexture), manager(tileManager), tiles(new std::pair<IDs::Tiles, sf::Color>[getTileCount()]) {
	updateVertices();
}

void TileLayer::resetColouring() {
	for (unsigned int y = 0; y < size.x; y++) {
		for (unsigned int x = 0; x < size.y; x++) {
			sf::Vector2u pos(x, y);

			setupTileQuad(pos);
		}
	}
}

void TileLayer::updateVertices() {
	MapLayer::updateVertices();

	for (unsigned int y = 0; y < size.x; y++) {
		for (unsigned int x = 0; x < size.y; x++) {
			setupTileQuad(sf::Vector2u(x, y));
		}
	}
}

bool TileLayer::save(std::string path) {
	std::ofstream file;
	file.open(path, std::ios::out | std::ios::trunc | std::ios::binary);

	if (file.is_open()) {
		DEBUG_LOG("Writing tile layer to file: " << path);

		file.write(reinterpret_cast<char*>(tiles.get()), sizeof(TileColourPair) * getTileCount());

		file.close();
		return true;
	}

	DEBUG_LOG_ERROR("Failed to write tile layer to file: " << path);
	return false;
}

bool TileLayer::load(std::string path) {
	std::ifstream file;
	file.open(path, std::ios::in | std::ios::binary | std::ios::ate);

	if (file.is_open()) {
		DEBUG_LOG("Loading tile layer from file: " << path);

		unsigned long bufferSize = sizeof(TileColourPair) * getTileCount();
		unsigned long fileSize = static_cast<unsigned long>(file.tellg());

		assert(fileSize == bufferSize); // TODO: Check the actual size of the layer being loaded rather than just assuming its size.

		file.seekg(0, std::ios::beg);
		file.read(reinterpret_cast<char*>(tiles.get()), bufferSize);

		file.close();

		updateVertices();

		return true;
	}

	DEBUG_LOG_ERROR("Failed to load tile layer from file: " << path);
	return false;
}

void TileLayer::setupTileQuad(sf::Vector2u pos) {
	sf::Vertex *quad = getQuadPtr(pos); // Get a pointer to the current quad in the vertex array.

	const Tile &tile = getTileAt(pos);
	sf::Color colour = getColourAt(pos);

	setQuadPosition(quad, pos);
	setQuadTexture(quad, sf::Vector2u(tile.textureX, tile.textureY));
	setQuadColour(quad, colour);
}

sf::Vertex *TileLayer::getQuadPtr(sf::Vector2u pos) {
	return &vertices[(pos.y * size.x + pos.x) * 4];
}

// Define the four corners of the quad.
void TileLayer::setQuadPosition(sf::Vertex *quad, sf::Vector2u pos) {
	quad[0].position = sf::Vector2f(pos.x * tileSize.x, pos.y * tileSize.y);
	quad[1].position = sf::Vector2f((pos.x + 1) * tileSize.x, pos.y * tileSize.y);
	quad[2].position = sf::Vector2f((pos.x + 1) * tileSize.x, (pos.y + 1) * tileSize.y);
	quad[3].position = sf::Vector2f(pos.x * tileSize.x, (pos.y + 1) * tileSize.y);
}

// Define the four texture coordinate pairs.
void TileLayer::setQuadTexture(sf::Vertex *quad, sf::Vector2u textureCoords) {
	quad[0].texCoords = sf::Vector2f(textureCoords.x * tileTextureSize.x, textureCoords.y * tileTextureSize.y);
	quad[1].texCoords = sf::Vector2f((textureCoords.x + 1) * tileTextureSize.x, textureCoords.y * tileTextureSize.y);
	quad[2].texCoords = sf::Vector2f((textureCoords.x + 1) * tileTextureSize.x, (textureCoords.y + 1) * tileTextureSize.y);
	quad[3].texCoords = sf::Vector2f(textureCoords.x * tileTextureSize.x, (textureCoords.y + 1) * tileTextureSize.y);
}

// Set the tile colour.
void TileLayer::setQuadColour(sf::Vertex *quad, sf::Color colour) {
	quad[0].color = colour;
	quad[1].color = colour;
	quad[2].color = colour;
	quad[3].color = colour;
}

const Tile &TileLayer::getTileAt(sf::Vector2u pos) {
	if (withinBounds(pos.x, pos.y)) {
		IDs::Tiles id = tiles[pos.y * size.x + pos.x].first;
		return manager.get(id);
	}
	return manager.get(IDs::Tiles::NOTHING);
}

sf::Color TileLayer::getColourAt(sf::Vector2u pos) {
	if (withinBounds(pos.x, pos.y)) {
		return tiles[pos.y * size.x + pos.x].second;
	}

	return getTileAt(pos).defaultColour;
}

unsigned int TileLayer::getTileCount() {
	return size.x * size.y;
}

void TileLayer::setTileAt(sf::Vector2u pos, IDs::Tiles id, bool useDefaultColour) {
	if (withinBounds(pos.x, pos.y)) {
		DEBUG_LOG_SPAM("Set tile " << id << " at " << pos.x << ", " << pos.y);

		tiles[pos.y * size.x + pos.x].first = id;
		if (useDefaultColour) tiles[pos.y * size.x + pos.x].second = getTileAt(pos).defaultColour;
		setupTileQuad(pos);
	}
}

void TileLayer::setTileAt(sf::Vector2u pos, IDs::Tiles id, sf::Color colour) {
	if (withinBounds(pos.x, pos.y)) {
		DEBUG_LOG_SPAM("Set tile colour " << id << " at " << pos.x << ", " << pos.y << " to: " << colour);

		tiles[pos.y * size.x + pos.x].first = id;
		tiles[pos.y * size.x + pos.x].second = colour;
		setupTileQuad(pos);
	}
}

void TileLayer::setColourAt(sf::Vector2u pos, sf::Color colour) {
	if (withinBounds(pos.x, pos.y)) {
		DEBUG_LOG_SPAM("Set tile colour " << id << " at " << pos.x << ", " << pos.y << " to: " << colour);

		tiles[pos.y * size.x + pos.x].second = colour;
		setupTileQuad(pos);
	}
}

void TileLayer::fill(IDs::Tiles id) {
	fillRect(id, sf::Vector2u(0, 0), size);
}

void TileLayer::fillRect(IDs::Tiles id, sf::Vector2u pos, sf::Vector2u rectSize) {
	for (unsigned int x = pos.x; x < pos.x + rectSize.x; x++) {
		for (unsigned int y = pos.y; y < pos.y + rectSize.y; y++) {
			setTileAt(sf::Vector2u(x, y), id);
		}
	}
}

void TileLayer::fillRect(IDs::Tiles id, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height) {
	fillRect(id, sf::Vector2u(posX, posY), sf::Vector2u(width, height));
}

void TileLayer::colourPath(MovementPath path, sf::Color colour) {
	for (sf::Vector2u pos : path.getPathTiles()) {
		if (withinBounds(pos.x, pos.y))
			setQuadColour(getQuadPtr(pos), colour);
	}
}

void TileLayer::resetColourPath(MovementPath path) {
	for (sf::Vector2u pos : path.getPathTiles()) {
		if (withinBounds(pos.x, pos.y))
			setupTileQuad(pos);
	}
}