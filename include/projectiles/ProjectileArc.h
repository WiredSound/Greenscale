#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>
#include "../map/pathfinding/MovementPath.h"
#include "../IDs.h"
#include "../components/Damage.h"
#include "ProjectileManager.h"
class Entity;

/**
 * A projectile arc handles the movement of a projectile and how said projectile interacts with tiles and entities on the map.
 * Typically when an entity uses a ranged component or weapon (see RangedComponent), the component and entity may build a number of projectile arcs which are passed to the GameMap. The GameMap
 * handles the drawing of these projectiles to the screen based on the infomation sorted in each projectile arc (primarily by fetching a ProjectileVisual from the projectile manager based on the
 * ID stored in the arc). The projectile arc is also tasked with inflicting damage or effects on any entities it may hit as well as destroying tiles based upon the projectile's penetration value.
 */
class ProjectileArc {
public:
	ProjectileArc(std::shared_ptr<ProjectileManager> projectileManager, Entity *arcUser, MovementPath projectilePath, IDs::Projectiles projectileId,
		Damage projectileDamage, unsigned int projectilePenetration, sf::Color projectileColour);

	bool reachedTarget();
	bool update(GameMap *map); // Returns true if the arc should be destroyed.

	const ProjectileVisual &getProjectileVisualInfo();
	sf::Vector2f getSingleProjectileTextureSize();
	Damage getProjectileDamage();
	unsigned int getProjectilePenetration();
	sf::Color getProjectileColour();

	sf::Vector2u getCurrentProjectilePosition();
	sf::Time getAnimationTime();

	Entity *getUser();
	unsigned int getTileHitCount();
	unsigned int getEntityHitCount();

private:
	// This is a raw pointer and not reference as this object would become non-copyable if it is a reference.
	Entity *user; // The entity that created/fired this projectile arc.

	MovementPath path;
	IDs::Projectiles id;

	sf::Color colour;

	sf::Clock movementClock;
	sf::Time timeBetweenMoves;

	sf::Clock animationClock;

	Damage damage;
	unsigned int penetration;

	unsigned int tileHitCount{ 0 };
	unsigned int entityHitCount{ 0 };

	std::shared_ptr<ProjectileManager> manager;

	sf::Time getTimeBetweenMoves();

	bool hitTile(GameMap *map, sf::Vector2u pos); // Returns true if the arc cannot penetrate the tile (meaning the arc should end).
	bool hitEntity(GameMap *map, sf::Vector2u pos); // Returns true if any entity/entities are hit at the given position (meaning the arc should end).
};