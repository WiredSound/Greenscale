#include "Entity.h"

#include "EntityController.h"

Entity::Entity(std::string entityName, sf::Vector2u pos, Faction entityFaction, sf::Vector2u componentGridSize, std::shared_ptr<EntityController> entityController)
	: name(entityName), position(pos), faction(entityFaction), componentGrid(componentGridSize), controller(entityController),
	currentPath(pos), visualMovementSpeed(sf::milliseconds(80)) {}

void Entity::yourTurnBegin() {
	myTurn = true;
}

bool Entity::yourTurnDecision(Input &input) {
	return controller->handle(this, input); // Controller, can you handle this? I don't think they can handle this!
}

bool Entity::yourTurnCurrently() {
	return updateMovement() && updateAttacking();
}

void Entity::yourTurnEnd() {
	componentGrid.turnPassed();
	myTurn = false;
}

bool Entity::isMyTurn() {
	return myTurn;
}

bool Entity::updateMovement() {
	if (!currentPath.reachedTarget() && movementClock.getElapsedTime() >= visualMovementSpeed) {
		movementClock.restart();

		moveDirectlyToPosition(currentPath.currentPosition());
		currentPath.nextPosition();
	}

	return currentPath.reachedTarget();
}

bool Entity::updateAttacking() {
	// This is overloaded by robots which can actually have weapons.
	return true;
}

sf::Vector2u Entity::getPosition() const {
	return position;
}

unsigned int Entity::getX() const {
	return position.x;
}
unsigned int Entity::getY() const {
	return position.y;
}

Faction Entity::getFaction() {
	return faction;
}

bool Entity::reachedPathTarget() {
	return currentPath.reachedTarget();
}

bool Entity::withinRange(int distance) {
	return distance <= movementRange;
}

bool Entity::moveTo(sf::Vector2u movePos) {
	MovementPath path = map->pathfinder.buildAStarPath(position, movePos);

	return setMovementPath(path);
}

bool Entity::setMovementPath(MovementPath path) {
	if (path.isComplete() && withinRange(path.getLength())) {
		currentPath = path;

		return true; // Return true if the path is within range.
	}

	DEBUG_LOG("Path is too long: " << path.getLength());
	return false;
}

int Entity::getMovementRange() {
	return movementRange;
}

unsigned int Entity::getIntegrity() {
	return componentGrid.getCurrentIntegrity();
}

unsigned int Entity::getMaxIntegrity() {
	return componentGrid.getMaxIntegrity();
}

int Entity::getPowerLevel() {
	return powerLevel;
}

int Entity::getMaxPowerStorage() {
	return componentGrid.getMaxPowerStorage();
}

bool Entity::isBlocking() {
	return true; // TODO: Implement this properly.
}

sf::Color Entity::getColour() {
	return (myTurn ? MY_TURN_COLOUR : sf::Color(255, 255, 255, 255));
}

bool Entity::moveDirectlyBy(sf::Vector2u movement) {
	if (map != nullptr) {
		if (map->isPositionFree(position + movement)) {
			position = position + movement;
			return true;
		}
	}
	return false;
}

bool Entity::moveDirectlyToPosition(sf::Vector2u newPos) {
	if (map != nullptr) {
		if (map->isPositionFree(newPos)) {
			position = newPos;
			return true;
		}
	}
	return false;
}

void Entity::setMap(GameMap *gameMap) {
	map = gameMap;
}

GameMap *Entity::getMapReference() {
	return map;
}

char Entity::getPriority() {
	return faction.priority;
}

ComponentGrid &Entity::getComponentGrid() {
	return componentGrid;
}