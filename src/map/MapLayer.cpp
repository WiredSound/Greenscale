#include "MapLayer.h"

MapLayer::MapLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, sf::Vector2f textureSizeTile, std::shared_ptr<sf::Texture> layerTexture)
	: size(layerSize), tileSize(sizeTile), tileTextureSize(textureSizeTile), texture(layerTexture) {}

void MapLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.texture = texture.get();
	target.draw(vertices, states);
}

bool MapLayer::withinBounds(int x, int y) {
	return x < (int) size.x && y < (int) size.y && x >= 0 && y >= 0;
}

void MapLayer::updateVertices() {
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(size.x * size.y * 4);
}