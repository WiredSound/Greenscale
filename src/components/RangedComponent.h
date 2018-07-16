#pragma once

#include "Component.h"

class RangedComponent : public Component {
public:
	RangedComponent(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager, std::shared_ptr<ProjectileManager> manager);
	virtual std::vector<ProjectileArc> useEnabled(Entity &user, MovementPath path, PowerPool &pool, Console &console) override;
	virtual MovementPath buildProjectilePath(sf::Vector2u source, sf::Vector2u target, GameMap *map) override;

	IDs::Projectiles getProjectileId();
	unsigned int getProjectileCount();
	Damage getProjectileDamage();
	unsigned int getProjectileRange();
	unsigned int getProjectilePenetration();

private:
	std::shared_ptr<ProjectileManager> projectileManager;
};