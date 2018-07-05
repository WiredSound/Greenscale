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
	for (sf::Vector2u pos : path.getPathTiles()) {
		auto entities = getEntitiesAt(pos);

		for (std::shared_ptr<Entity> &entity : entities) {
			// ...
		}
	}
}

bool EntityLayer::isPositionFree(sf::Vector2u pos) {
	for (std::shared_ptr<Entity> &entity : getEntitiesAt(pos)) {
		if (entity->isBlocking())
			return false;
	}

	return true;
}

std::vector<std::shared_ptr<Entity>> EntityLayer::getEntitiesAt(sf::Vector2u pos) {
	std::vector<std::shared_ptr<Entity>> entitiesHere;

	for (std::shared_ptr<Entity> &entity : entities) {
		if (entity->getPosition() == pos)
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

// WARNING: This function does not set the map reference within the entity - only the GameMap addEntity function does that.
void EntityLayer::addEntity(std::shared_ptr<Entity> entity) {
	entities.push_back(entity);

	vertices.resize(entities.size() * 4);
}

void EntityLayer::updateVertices() {
	for (int i = 0; i < entities.size(); i++) {
		std::shared_ptr<Entity> &entity = entities[i];
		const Animation::Frame &frame = entity->fetchFrame();

		DEBUG_LOG_SPAM("Adding to vertex array entity " << entity->name << " at: " << entity->getX() << ", " << entity->getY());

		sf::Vertex *quad = &vertices[i * 4];

		// Define the four corners of the Entity's quad.
		quad[0].position = sf::Vector2f(entity->getX() * tileSize.x, entity->getY() * tileSize.y);
		quad[1].position = sf::Vector2f((entity->getX() + 1) * tileSize.x, entity->getY() * tileSize.y);
		quad[2].position = sf::Vector2f((entity->getX() + 1) * tileSize.x, (entity->getY() + 1) * tileSize.y);
		quad[3].position = sf::Vector2f(entity->getX() * tileSize.x, (entity->getY() + 1) * tileSize.y);

		// Define the texture coordinates.
		quad[0].texCoords = sf::Vector2f(frame.textureX * tileTextureSize.x, frame.textureY * tileTextureSize.y);
		quad[1].texCoords = sf::Vector2f((frame.textureX + 1) * tileTextureSize.x, frame.textureY * tileTextureSize.y);
		quad[2].texCoords = sf::Vector2f((frame.textureX + 1) * tileTextureSize.x, (frame.textureY + 1) * tileTextureSize.y);
		quad[3].texCoords = sf::Vector2f(frame.textureX * tileTextureSize.x, (frame.textureY + 1) * tileTextureSize.y);

		// Set the colour.
		quad[0].color = quad[1].color = quad[2].color = quad[3].color = ((frame.colour == sf::Color(0, 0, 0, 0)) ? entity->getColour() : frame.colour); // Use the default entity colour unless the frame overrides that colour.
	}
}