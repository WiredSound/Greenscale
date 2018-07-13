#include "RangedComponent.h"

#include "../entities/Entity.h"

RangedComponent::RangedComponent(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<ProjectileManager> manager)
	: Component(componentId, componentManager), projectileManager(manager) {}

std::vector<ProjectileArc> RangedComponent::useEnabled(Entity &user, MovementPath path, Console &console) {
	std::vector<ProjectileArc> arcs;

	auto count = getProjectileCount();
	auto damage = getProjectileDamage();
	auto penetration = getProjectilePenetration();

	arcs.resize(count, ProjectileArc(projectileManager, &user, path, getProjectileId(), damage, penetration, user.getFaction().colour));

	console.display({ user.getFullName() + " fired " + std::to_string(count) + (count == 1 ? " projectile with " : " projectiles each with ") + std::to_string(penetration) + " penetration and damage: "
		+ std::to_string(damage.kinetic) + " kinetic, " + std::to_string(damage.thermal) + " thermal, " + std::to_string(static_cast<int>(damage.disruption * 100)) + "% disruption.",
		Console::MessageType::INFO });

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