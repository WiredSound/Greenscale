#include "components/RangedComponent.h"

#include "entities/Entity.h"

RangedComponent::RangedComponent(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<ProjectileManager> manager)
	: Component(componentId, componentManager), projectileManager(manager) {
}

std::vector<ProjectileArc> RangedComponent::useEnabled(Entity &user, MovementPath path, PowerPool &pool, Console &console) {
	Component::useEnabled(user, path, pool, console);

	auto count = getProjectileCount();
	auto damage = getProjectileDamage();
	auto penetration = getProjectilePenetration();

	std::vector<ProjectileArc> arcs;
	ProjectileArc defaultArc(projectileManager, &user, path, getProjectileId(), damage, penetration, user.getFaction().colour);
	arcs.resize(count, defaultArc);

	console.display({ user.getFullName() + " fired " + std::to_string(count) + (count == 1 ? " projectile with " : " projectiles each with ") + std::to_string(penetration) + " penetration and damage: "
		+ std::to_string(damage.kinetic) + " kinetic, " + std::to_string(damage.thermal) + " thermal, " + std::to_string(static_cast<int>(damage.disruption * 100)) + "% disruption.",
		(user.isMemberOfPlayerFaction() ? Console::MessageType::INFO_NONESSENTIAL : Console::MessageType::WARNING_NONESSENTIAL) });

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

Component::ModifierFunc projectileModifier = [](auto &upgrade) {return upgrade.projectileModifier; };
unsigned int RangedComponent::getProjectileRange() { return statWithUpgradesApplied<unsigned int>(fetchInfo().projectileRange, projectileModifier); }
unsigned int RangedComponent::getProjectilePenetration() { return statWithUpgradesApplied<unsigned int>(fetchInfo().projectilePenetration, projectileModifier); }
