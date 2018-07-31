#pragma once

#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Tile.h"

class MapLayer : public sf::Drawable {
public:
	MapLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, sf::Vector2f textureSizeTile, std::shared_ptr<sf::Texture> layerTexture);
	bool withinBounds(sf::Vector2u pos);
	unsigned int getIndex(sf::Vector2u pos);
	sf::Vector2u getCentre();

	const sf::Vector2u size; // Size of the layer in tiles (not pixels).

protected:
	sf::VertexArray vertices;
	std::shared_ptr<sf::Texture> texture;

	sf::Vector2f tileSize; // The size that each tile is drawn.
	sf::Vector2f tileTextureSize; // The size of each tile in the tileset texture.

	virtual void updateVertices();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};