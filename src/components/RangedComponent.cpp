#include "RangedComponent.h"

RangedComponent::RangedComponent(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<ProjectileManager> manager)
	: Component(componentId, componentManager), projectileManager(manager) {}

Optional<ProjectileArc> RangedComponent::use(MovementPath path) {
	auto arc = std::make_unique<ProjectileArc>(projectileManager, path, getProjectileId(), getProjectileDamage(), getProjectilePenetration());

	return Optional<ProjectileArc>(std::move(arc));
}

MovementPath RangedComponent::buildProjectilePath(sf::Vector2u source, sf::Vector2u target, GameMap *map) {
	return MovementPath::buildLinePath(source, target/*, getProjectileRange()*/); // TODO: Take range into account.
}

IDs::Projectiles RangedComponent::getProjectileId() {
	return fetchInfo().projectileId;
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