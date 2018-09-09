#include "ProjectileLayer.h"

void ProjectileLayer::update(GameMap *map) {
	if (!areAllArcsComplete()) {
		ProjectileArc &arc = arcs[0];
		sf::Vector2u position = arc.getCurrentProjectilePosition();

		const ProjectileVisual &visual = arc.getProjectileVisualInfo();
		const Animation::Frame &frame = visual.animation->getFrame(arc.getAnimationTime());
		sf::Vector2f singleProjectileTextureSize = arc.getSingleProjectileTextureSize();

		bool destroyArc = arc.update(map);

		if (arc.reachedTarget() || destroyArc) { // Arc has reached its target or has been marked for destruction...
			/*
			Entity *arcUser = arc.getUser();
			assert(arcUser != nullptr);

			unsigned int tilesHit = arc.getTileHitCount();
			unsigned int entitiesHit = arc.getEntityHitCount();

			console.display({
			arcUser->getFullName() + " fired a projectile destroying a total of " + std::to_string(tilesHit) + (tilesHit == 1 ? " tile" : " tiles")
			+ " and hitting " + std::to_string(entitiesHit) + (entitiesHit == 1 ? " entity." : " entities."),
			isFactionPlayerFriendly(arcUser->getFaction()) ? Console::MessageType::INFO : Console::MessageType::WARNING
			});
			*/

			arcs.erase(arcs.begin()); // Remove the projectile arc.
		}
		else { // Arc is not ready for destruction and should instead be drawn...
			vertices.setPrimitiveType(sf::Quads);
			vertices.resize(4); // Currently only a single projectile can be visible on screen at any one time.

			sf::Vertex *quad = &vertices[0];

			quad[0].position = sf::Vector2f(position.x * tileSize.x, position.y * tileSize.y);
			quad[1].position = sf::Vector2f((position.x + 1) * tileSize.x, position.y * tileSize.y);
			quad[2].position = sf::Vector2f((position.x + 1) * tileSize.x, (position.y + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(position.x * tileSize.x, (position.y + 1) * tileSize.y);

			quad[0].texCoords = sf::Vector2f(frame.textureX * singleProjectileTextureSize.x, frame.textureY * singleProjectileTextureSize.y);
			quad[1].texCoords = sf::Vector2f((frame.textureX + 1) * singleProjectileTextureSize.x, frame.textureY * singleProjectileTextureSize.y);
			quad[2].texCoords = sf::Vector2f((frame.textureX + 1) * singleProjectileTextureSize.x, (frame.textureY + 1) * singleProjectileTextureSize.y);
			quad[3].texCoords = sf::Vector2f(frame.textureX * singleProjectileTextureSize.x, (frame.textureY + 1) * singleProjectileTextureSize.y);

			quad[0].color = quad[1].color = quad[2].color = quad[3].color = arc.getProjectileColour();
		}
	}
}

bool ProjectileLayer::areAllArcsComplete() const {
	return arcs.size() == 0;
}

void ProjectileLayer::fireArcs(std::vector<ProjectileArc> addArcs) {
	arcs.insert(arcs.end(), addArcs.begin(), addArcs.end());
}

void ProjectileLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!areAllArcsComplete()) // Only draw if there are projectile arcs that have not yet reached their targets...
		MapLayer::draw(target, states);
}