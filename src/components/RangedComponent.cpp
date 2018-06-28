#include "RangedComponent.h"

RangedComponent::RangedComponent(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<ProjectileManager> manager)
	: Component(componentId, componentManager), projectileManager(manager) {}

std::vector<ProjectileArc> RangedComponent::use(MovementPath path) {
	std::vector<ProjectileArc> arcs;

	arcs.resize(getProjectileCount(), ProjectileArc(projectileManager, path, getProjectileId(), getProjectileDamage(), getProjectilePenetration()));

	return arcs;
}

MovementPath RangedComponent::buildProjectilePath(sf::Vector2u source, sf::Vector2u target, GameMap *map) {
	return MovementPath::buildLinePath(source, target, getProjectileRange());
}

IDs::Projectiles RangedComponent::getProjectileId() {
	return fetchInfo().projectileId;
}

unsigned int RangedComponent::getProjectileCount() {
	return fetchInfo().projectileCount;
}

Damage RangedComponent::getProjectileDamage() {
	return fetchInfo().projectileDamage; // TODO: Apply upgrades.
}

unsigned int RangedComponent::getProjectileRange() {
	unsigned int baseRange = fetchInfo().projectileRange;
	unsigned int range = baseRange;

	for (ComponentUpgrade &upgrade : upgrades) {
		range += static_cast<unsigned int>(ceil(baseRange * upgrade.projectileModifier));
	}

	return range;
}

unsigned int RangedComponent::getProjectilePenetration() {
	unsigned int basePenetration = fetchInfo().projectilePenetration;
	unsigned int penetration = basePenetration;

	for (ComponentUpgrade &upgrade : upgrades) {
		penetration += static_cast<unsigned int>(ceil(basePenetration * upgrade.projectileModifier));
	}

	return penetration;
}