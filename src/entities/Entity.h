#pragma once

#include <memory>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include "Faction.h"
#include "../map/GameMap.h"
#include "../components/ComponentGrid.h"
#include "../projectiles/ProjectileArc.h"
#include "../entities/EntityManager.h"
#include "../PulsingColour.h"
#include "../Input.h"
class EntityController;

/*
 * The Entity class handles all the actions an entity makes and how it interacts with the GameMap it is located in. The ID of the entity determines the animation, default components, name,
 * description and other such static values held in the relevant EntityInfo struct contained in the EntityManager. Values that vary between entities, such as the current equipped commponents,
 * aligned factions, position as well as the behaviour (primarily via the held EntityController pointer) are stored in the Entity class itself.
 */

class Entity {
public:
	Entity(IDs::Entities entityId, std::shared_ptr<EntityManager> entityManager, std::string entityName, sf::Vector2u pos, Faction entityFaction, std::shared_ptr<EntityController> entityController);

	virtual void yourTurnBegin(); // When it first becomes this entity's turn.
	virtual bool yourTurnDecision(Input &input); // Where the entity calls upon its controller in order to decide what to do.
	virtual bool yourTurnCurrently(); // Where the entity can performs things that take multiple frames to complete such as movement before the turn manager can move onto the next entity.
	virtual void yourTurnEnd(); // When the entity has finished moving, animating, etc.
	bool isMyTurn();

	bool updateMovement();
	virtual bool updateAttacking();

	sf::Vector2u getPosition() const;
	sf::Vector2f getAbsoluteCentrePosition() const;
	unsigned int getX() const;
	unsigned int getY() const;
	bool moveTo(sf::Vector2u movePos);
	bool setMovementPath(MovementPath path);
	bool reachedPathTarget();
	bool withinRange(int distance);

	const EntityInfo &fetchInfo();
	std::string getEntityName();
	std::string getDescription();
	std::string getEntityType();
	std::shared_ptr<Animation> getAnimation(std::string key);

	bool isBlocking();
	virtual sf::Color getColour();
	virtual char getPriority();
	Faction getFaction();
	virtual Animation::Frame fetchFrame() = 0;
	ComponentGrid &getComponentGrid();
	int getMovementRange();
	std::string getPersonalName();
	std::string getFullName();

	unsigned int getIntegrity();
	unsigned int getMaxIntegrity();
	bool isDestroyed();

	int getPowerLevel();
	int getMaxPowerStorage();

	MovementPath buildEquippedComponentPath(sf::Vector2u target);
	bool useEquippedComponent(MovementPath path);
	void applyDamage(Damage damage);

	void setMap(GameMap *gameMap);
	GameMap *getMapReference();

protected:
	bool moveDirectlyBy(sf::Vector2u movement);
	bool moveDirectlyToPosition(sf::Vector2u newPos);

	sf::Clock animationClock;
	sf::Clock movementClock;

	std::string personalName;
	Faction faction;

	MovementPath currentPath;
	sf::Time visualMovementSpeed; // Time between each tile movement when moving along a path.

	static PulsingColour myTurnColourPulse;

private:
	IDs::Entities id;
	std::shared_ptr<EntityManager> manager;

	GameMap *map;

	ComponentGrid componentGrid;

	sf::Vector2u position;
	sf::Vector2u size;

	unsigned int powerLevel = 0;

	// Removed as integrity is now based entirely upon the components equipped.
	//int integrity;
	//int maxIntegrity;

	std::shared_ptr<EntityController> controller;
	bool myTurn = false;
};