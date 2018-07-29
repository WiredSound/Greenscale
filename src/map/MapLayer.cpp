#include "MapLayer.h"

MapLayer::MapLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, sf::Vector2f textureSizeTile, std::shared_ptr<sf::Texture> layerTexture)
	: size(layerSize), tileSize(sizeTile), tileTextureSize(textureSizeTile), texture(layerTexture) {}

void MapLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.texture = texture.get();
	target.draw(vertices, states);
}

bool MapLayer::withinBounds(sf::Vector2u pos) {
	return pos.x < size.x && pos.y < size.y;
}

unsigned int MapLayer::getIndex(sf::Vector2u pos) {
	return pos.y * size.x + pos.x;
}

void MapLayer::updateVertices() {
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(size.x * size.y * 4);
}