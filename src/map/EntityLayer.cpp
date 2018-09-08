#include "EntityLayer.h"

#include <iostream>
#include "../entities/Entity.h"
#include "../entities/Robot.h"

EntityLayer::EntityLayer(sf::Vector2u layerSize, sf::Vector2f sizeTile, sf::Vector2f textureSizeTile, std::shared_ptr<sf::Texture> layerTexture)
	: MapLayer(layerSize, sizeTile, textureSizeTile, layerTexture) {
	vertices.setPrimitiveType(sf::Quads);
}

void EntityLayer::update() {
	updateVertices(); // Entity vertices are updated every frame so colour and texture changes are easily handled.
}

void EntityLayer::colourEntitiesInPath(MovementPath path, sf::Color colour) {
	throw std::exception("EntityLayer::colourEntitiesInPath is unimplemented!");

	for (sf::Vector2u pos : path.getPathTiles()) {
		auto entitiesAt = getEntitiesAt(pos);

		for (std::shared_ptr<Entity> &entity : entitiesAt) {
			// ...
		}
	}
}

bool EntityLayer::isPositionFree(sf::Vector2u pos) {
	for (std::shared_ptr<Entity> &entity : getEntitiesOver(pos)) {
		if (entity->isBlocking())
			return false;
	}

	return true;
}

/**
 * Finds entities exactly at a given position - ignores large entities that overlap with the given position.
 */
std::vector<std::shared_ptr<Entity>> EntityLayer::getEntitiesAt(sf::Vector2u pos) {
	std::vector<std::shared_ptr<Entity>> entitiesHere;

	for (std::shared_ptr<Entity> &entity : entities) {
		if (entity->getPosition() == pos)
			entitiesHere.push_back(entity);
	}

	return entitiesHere;
}

/**
 * Finds all the entities at given position - this does take into account entities that are larger than a single tile.
 */
std::vector<std::shared_ptr<Entity>> EntityLayer::getEntitiesOver(sf::Vector2u pos) {
	std::vector<std::shared_ptr<Entity>> entitiesHere;

	for (std::shared_ptr<Entity> &entity : entities) {
		if (entity->overPosition(pos))
			entitiesHere.push_back(entity);
	}

	return entitiesHere;
}

std::vector<std::shared_ptr<Entity>> EntityLayer::getEntities() {
	return entities;
}

bool EntityLayer::save(std::string path) {
	std::ofstream file;
	file.open(path, std::ios::out | std::ios::trunc | std::ios::binary);

	if (file.is_open()) {
		DEBUG_LOG("Writing entity layer to file: " << path);

		// TODO: ...

		file.close();
		return true;
	}

	DEBUG_LOG_ERROR("Failed to write entity layer to file: " << path);
	return false;
}

/**
 * Adds an entity to the EntityLayer and resizes the sf::VertexArray accordingly. Note that this function does not set the map pointer member of the entity - only GameMap::addEntity does that.
 */
void EntityLayer::addEntity(std::shared_ptr<Entity> entity) {
	entities.push_back(entity);

	vertices.resize(entities.size() * 4);
}

void EntityLayer::updateVertices() {
	for (int i = 0; i < entities.size(); i++) {
		std::shared_ptr<Entity> &entity = entities[i];
		sf::Vector2u position = entity->getPosition();
		sf::Vector2u entitySize = entity->getSize();
		const Animation::Frame &frame = entity->fetchFrame();

		DEBUG_LOG_SPAM("Adding to vertex array entity " << entity->name << " at: " << entity->getX() << ", " << entity->getY());

		sf::Vertex *quad = &vertices[i * 4];

		// Define the four corners of the Entity's quad.
		quad[0].position = sf::Vector2f(position.x * tileSize.x, position.y * tileSize.y);
		quad[1].position = sf::Vector2f((position.x + entitySize.x) * tileSize.x, position.y * tileSize.y);
		quad[2].position = sf::Vector2f((position.x + entitySize.x) * tileSize.x, (position.y + entitySize.y) * tileSize.y);
		quad[3].position = sf::Vector2f(position.x * tileSize.x, (position.y + entitySize.y) * tileSize.y);

		// Define the texture coordinates.
		quad[0].texCoords = sf::Vector2f(frame.textureX * tileTextureSize.x, frame.textureY * tileTextureSize.y);
		quad[1].texCoords = sf::Vector2f((frame.textureX + entitySize.x) * tileTextureSize.x, frame.textureY * tileTextureSize.y);
		quad[2].texCoords = sf::Vector2f((frame.textureX + entitySize.x) * tileTextureSize.x, (frame.textureY + entitySize.y) * tileTextureSize.y);
		quad[3].texCoords = sf::Vector2f(frame.textureX * tileTextureSize.x, (frame.textureY + entitySize.y) * tileTextureSize.y);

		// Set the colour.
		quad[0].color = quad[1].color = quad[2].color = quad[3].color = ((frame.colour == sf::Color(0, 0, 0, 0)) ? entity->getColour() : frame.colour); // Use the default entity colour unless the frame overrides that colour.
	}
}