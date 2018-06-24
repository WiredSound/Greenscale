#include "ProjectileArc.h"

#include "../map/GameMap.h"
#include "../entities/Entity.h"

ProjectileArc::ProjectileArc(std::shared_ptr<ProjectileManager> projectileManager, MovementPath projectilePath, IDs::Projectiles projectileId, Damage projectileDamage, unsigned int projectilePenetration)
	: manager(projectileManager), path(projectilePath), id(projectileId), damage(projectileDamage), penetration(projectilePenetration)
{
	path.resetPosition();
}

bool ProjectileArc::isComplete() {
	return path.isComplete();
}

bool ProjectileArc::update(GameMap *map) {
	if (!isComplete() && movementClock.getElapsedTime() >= getTimeBetweenMoves()) {
		movementClock.restart();

		hit(map, path.currentPosition());

		path.nextPosition();
	}

	return isComplete();
}

void ProjectileArc::hit(GameMap *map, sf::Vector2u pos) {
	if (!map->isTilePositionFree(pos)) {
		penetration = map->applyPenetrationToTileAt(pos, penetration);

		DEBUG_LOG("Projectile arc hit blocking tile and now has penetration value remaining: " << penetration);
	}
	else if (!map->isEntityPositionFree(pos)) {
		for (auto &entity : map->getEntitiesAt(pos)) {
			entity->applyDamage(getProjectileDamage());

			DEBUG_LOG("Projectile arc hit entity: " << entity);
		}
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