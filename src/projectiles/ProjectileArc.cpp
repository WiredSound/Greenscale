#include "ProjectileArc.h"

#include "../map/GameMap.h"
#include "../entities/Entity.h"

ProjectileArc::ProjectileArc(std::shared_ptr<ProjectileManager> projectileManager, Entity *arcUser, MovementPath projectilePath, IDs::Projectiles projectileId,
	Damage projectileDamage, unsigned int projectilePenetration, sf::Color projectileColour)
	: manager(projectileManager), path(projectilePath), id(projectileId), damage(projectileDamage), penetration(projectilePenetration), colour(projectileColour), user(arcUser)
{
	path.resetPosition();
}

bool ProjectileArc::reachedTarget() {
	return path.reachedTarget();
}

bool ProjectileArc::update(GameMap *map) {
	bool destroyProjectile = false;

	if (!reachedTarget() && movementClock.getElapsedTime() >= getTimeBetweenMoves()) {
		movementClock.restart();

		auto pos = path.currentPosition();

		if (!destroyProjectile && (hitEntity(map, pos) || hitTile(map, pos)))
			destroyProjectile = true;

		path.nextPosition();
	}

	return destroyProjectile;
}

bool ProjectileArc::hitTile(GameMap *map, sf::Vector2u pos) {
	if (!map->isTilePositionFree(pos)) {
		if (map->enoughPenetrationToDestroyTileAt(pos, penetration)) {
			DEBUG_LOG("Projectile arc hit blocking tile and now has penetration value remaining: " << penetration);

			penetration = map->applyPenetrationToTileAt(pos, penetration);
			tileHitCount++;

			return false;
		}
		DEBUG_LOG("Projectile destroyed by tile at: " << pos.x << ", " << pos.y);
		return true; // Indicate the projectile needs to be destroyed as it does not have enough penetration value left to break the given tile.
	}

	return false;
}

bool ProjectileArc::hitEntity(GameMap *map, sf::Vector2u pos) {
	bool entitiesHit = false;

	for (auto &entity : map->getEntitiesAt(pos)) {
		if (entity->isBlocking()) {
			DEBUG_LOG("Projectile arc hit entity: " << entity->getFullName());

			entity->applyDamage(getProjectileDamage());
			entityHitCount++;

			entitiesHit = true;
		}
	}

	return entitiesHit;
}

const ProjectileVisual &ProjectileArc::getProjectileVisualInfo() {
	return manager->get(id);
}

sf::Vector2f ProjectileArc::getSingleProjectileTextureSize() {
	return manager->getSingleProjectileTextureSize();
}

sf::Time ProjectileArc::getTimeBetweenMoves() {
	return getProjectileVisualInfo().timeBetweenMoves;
}

Damage ProjectileArc::getProjectileDamage() {
	return damage;
}

unsigned int ProjectileArc::getProjectilePenetration() {
	return penetration;
}

sf::Color ProjectileArc::getProjectileColour() {
	return colour;
}

sf::Vector2u ProjectileArc::getCurrentProjectilePosition() {
	return path.currentPosition();
}

sf::Time ProjectileArc::getAnimationTime() {
	return animationClock.getElapsedTime();
}

Entity *ProjectileArc::getUser() {
	return user;
}

unsigned int ProjectileArc::getTileHitCount() {
	return tileHitCount;
}

unsigned int ProjectileArc::getEntityHitCount() {
	return entityHitCount;
}