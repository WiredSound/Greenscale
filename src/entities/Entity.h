#pragma once

#include <memory>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include "Faction.h"
#include "../Animation.h"
#include "../Input.h"
#include "../map/GameMap.h"
#include "../components/ComponentGrid.h"
class EntityController;

#define MY_TURN_COLOUR sf::Color(0, 255, 0, 255)

class Entity {
public:
	Entity(std::string entityName, sf::Vector2u pos, Faction entityFaction, sf::Vector2u componentGridSize, std::shared_ptr<EntityController> entityController);

	bool yourMovementTurn(Input &input);
	bool yourAttackTurn(Input &input);
	void yourTurnEnded();
	bool isMyTurn();

	bool updateMovement();
	virtual bool updateAttacking();

	sf::Vector2u getPosition() const;
	unsigned int getX() const;
	unsigned int getY() const;
	bool moveTo(sf::Vector2u movePos);
	bool setMovementPath(MovementPath path);
	bool reachedPathTarget();
	bool withinRange(int distance);

	bool isBlocking();
	virtual sf::Color getColour();
	virtual char getPriority();
	Faction getFaction();
	virtual Animation::Frame fetchFrame() = 0;
	ComponentGrid &getComponentGrid();
	int getMovementRange();

	unsigned int getIntegrity();
	unsigned int getMaxIntegrity();

	int getPowerLevel();
	int getMaxPowerStorage();

	void setMap(GameMap *gameMap);
	GameMap *getMapReference();

	const std::string name;

protected:
	bool moveDirectlyBy(sf::Vector2u movement);
	bool moveDirectlyToPosition(sf::Vector2u newPos);

	sf::Clock animationClock;
	sf::Clock movementClock;

	Faction faction;

	MovementPath currentPath;
	int movementRange = 10;
	sf::Time visualMovementSpeed; // Time between each tile movement when moving along a path.

private:
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