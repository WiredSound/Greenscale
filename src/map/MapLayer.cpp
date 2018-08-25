#include "MapLayer.h"

MapLayer::MapLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, sf::Vector2f textureSizeTile, std::shared_ptr<sf::Texture> layerTexture)
	: size(layerSize), tileSize(sizeTile), tileTextureSize(textureSizeTile), texture(layerTexture) {}

/**
 * Sets the `texture` member as the texture used by the sf::RenderStates and then draws the sf::VertexArray `vertices` member.
 */
void MapLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.texture = texture.get();
	target.draw(vertices, states);
}

bool MapLayer::withinBounds(sf::Vector2u pos) {
	return pos.x < size.x && pos.y < size.y;
}

/**
 * Turns a map position into an array index.
 */
unsigned int MapLayer::getIndex(sf::Vector2u pos) {
	return pos.y * size.x + pos.x;
}

sf::Vector2u MapLayer::getCentre() {
	return sf::Vector2u(static_cast<unsigned int>(std::round(size.x / 2)), static_cast<unsigned int>(std::round(size.y / 2)));
}

void MapLayer::updateVertices() {
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(size.x * size.y * 4);
}