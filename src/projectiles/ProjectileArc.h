#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>
#include "../map/pathfinding/MovementPath.h"
#include "../IDs.h"
#include "../components/Damage.h"
#include "ProjectileManager.h"

class ProjectileArc {
public:
	ProjectileArc(std::shared_ptr<ProjectileManager> projectileManager, MovementPath projectilePath, IDs::Projectiles projectileId, Damage projectileDamage, unsigned int projectilePenetration);

	bool reachedTarget();
	bool update(GameMap *map);

	const ProjectileVisual &getProjectileVisualInfo();
	Damage getProjectileDamage();
	unsigned int getProjectilePenetration();

	sf::Vector2u getCurrentProjectilePosition();
	sf::Time getAnimationTime();

private:
	MovementPath path;
	IDs::Projectiles id;

	sf::Clock movementClock;
	sf::Time timeBetweenMoves;

	sf::Clock animationClock;

	Damage damage;
	unsigned int penetration;

	std::shared_ptr<ProjectileManager> manager;

	sf::Time getTimeBetweenMoves();
	void hit(GameMap *map, sf::Vector2u pos);
};