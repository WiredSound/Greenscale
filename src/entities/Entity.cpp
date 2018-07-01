#include "Entity.h"

#include "EntityController.h"

PulsingColour Entity::myTurnColourPulse(0.8f, 1.0f, 0.005f);

Entity::Entity(IDs::Entities entityId, std::shared_ptr<EntityManager> entityManager, std::string entityName, sf::Vector2u pos, Faction entityFaction, std::shared_ptr<EntityController> entityController)
	: id(entityId), manager(entityManager), personalName(entityName), position(pos), faction(entityFaction), componentGrid(sf::Vector2u(2, 2) /* TODO: Load grid size. */),
	controller(entityController), currentPath(pos), visualMovementSpeed(sf::milliseconds(80)) {}

void Entity::yourTurnBegin() {
	DEBUG_LOG("Turn begins for entity: " << personalName);
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
	DEBUG_LOG("Turn ends for entity: " << personalName);
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
	return map->areAllProjectileArcsComplete();
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
	return distance <= getMovementRange();
}

const EntityInfo &Entity::fetchInfo() {
	return manager->get(id);
}

std::string Entity::getEntityName() {
	return fetchInfo().name;
}

std::string Entity::getDescription() {
	return fetchInfo().description;
}
std::string Entity::getEntityType() {
	return fetchInfo().type;
}
std::shared_ptr<Animation> Entity::getAnimation(std::string key) {
	return fetchInfo().animations.at(key);
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
	// TODO: Calculate movement range.
	return 12;
}

std::string Entity::getPersonalName() {
	return personalName;
}

std::string Entity::getFullName() {
	return getPersonalName() + " (" + getEntityName() + ")";
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

MovementPath Entity::buildEquippedComponentPath(sf::Vector2u target) {
	auto &component = componentGrid.getEquippedComponent();

	if (component) {
		return component->buildProjectilePath(getPosition(), target, map);
	}

	return MovementPath(getPosition());
}

bool Entity::useEquippedComponent(MovementPath path) {
	auto &component = componentGrid.getEquippedComponent();

	if (component && component->isEnabled()) {
		std::vector<ProjectileArc> arcs = component->use(*this, path);

		map->fireArcs(arcs);

		return true;
	}

	return false;
}

void Entity::applyDamage(Damage damage) {
	componentGrid.applyDamageToRandomComponent(damage); // TODO: Apply damage to component based on where the entity is shot from instead.
}

bool Entity::isBlocking() {
	return true; // TODO: Implement this properly.
}

sf::Color Entity::getColour() {
	return (myTurn ? myTurnColourPulse.getColour(sf::Color::White) : sf::Color::White);
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