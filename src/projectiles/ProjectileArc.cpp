#include "ProjectileArc.h"

#include "../map/GameMap.h"
#include "../entities/Entity.h"

ProjectileArc::ProjectileArc(std::shared_ptr<ProjectileManager> projectileManager, MovementPath projectilePath, IDs::Projectiles projectileId, Damage projectileDamage, unsigned int projectilePenetration)
	: manager(projectileManager), path(projectilePath), id(projectileId), damage(projectileDamage), penetration(projectilePenetration)
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

		hitBlockingEntity(map, path.currentPosition());
		destroyProjectile = hitBlockingTile(map, path.currentPosition());

		path.nextPosition();
	}

	return destroyProjectile;
}

bool ProjectileArc::hitBlockingTile(GameMap *map, sf::Vector2u pos) {
	if (map->enoughPenetrationToDestroyTileAt(pos, penetration)) {
		DEBUG_LOG("Projectile arc hit blocking tile and now has penetration value remaining: " << penetration);

		penetration = map->applyPenetrationToTileAt(pos, penetration);
		return false;
	}
	DEBUG_LOG("Projectile destroyed by tile at: " << pos.x << ", " << pos.y);
	return true; // Indicate the projectile needs to be destroyed as it does not have enough penetration value left to break the given tile.
}

void ProjectileArc::hitBlockingEntity(GameMap *map, sf::Vector2u pos) {
	for (auto &entity : map->getEntitiesAt(pos)) {
		DEBUG_LOG("Projectile arc hit entity: " << entity->name);

		entity->applyDamage(getProjectileDamage());
	}
}

const ProjectileVisual &ProjectileArc::getProjectileVisualInfo() {
	return manager->get(id);
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

sf::Vector2u ProjectileArc::getCurrentProjectilePosition() {
	return path.currentPosition();
}

sf::Time ProjectileArc::getAnimationTime() {
	return animationClock.getElapsedTime();
}