#pragma once

#include <iostream>
#include "MapLayer.h"
#include "pathfinding/MovementPath.h"
class Entity;
class Robot;

/**
 * Stores all entities present and handles the construction of a sf::VertexArray to draw these entities.
 */
class EntityLayer : public MapLayer {
public:
	EntityLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, sf::Vector2f textureSizeTile, std::shared_ptr<sf::Texture> layerTexture);

	void addEntity(std::shared_ptr<Entity> entity);
	std::vector<std::shared_ptr<Entity>> getEntitiesAt(sf::Vector2u pos);
	std::vector<std::shared_ptr<Entity>> getEntitiesOver(sf::Vector2u pos);
	std::vector<std::shared_ptr<Entity>> getEntities();

	void update();
	void colourEntitiesInPath(MovementPath path, sf::Color colour);
	bool isPositionFree(sf::Vector2u pos);

	bool save(std::string path);

private:
	std::vector<std::shared_ptr<Entity>> entities;

	void updateVertices() override;
};