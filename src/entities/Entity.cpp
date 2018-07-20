#include "Entity.h"

#include "controllers/EntityController.h"

PulsingColour Entity::myTurnColourPulse(0.8f, 1.0f, 0.005f);

Entity::Entity(IDs::Entities entityId, std::shared_ptr<EntityManager> entityManager, std::string entityName, sf::Vector2u pos, Faction entityFaction, std::shared_ptr<EntityController> entityController,
	Console &consoleRef) : id(entityId), manager(entityManager), personalName(entityName), position(pos), faction(entityFaction), componentGrid(sf::Vector2u(2, 2) /* TODO: Load grid size. */),
	controller(entityController), console(consoleRef), currentPath(pos), visualMovementSpeed(sf::milliseconds(150)) {}

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

sf::Vector2f Entity::getAbsoluteCentrePosition() const {
	auto pos = map->tilePosToWorldPos(position);
	return sf::Vector2f(pos.x + map->tileSize.x / 2, pos.y + map->tileSize.y / 2);
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

bool Entity::isDestroyed() {
	return getIntegrity() <= 0;
}

int Entity::getPowerLevel() {
	return componentGrid.getPowerStored();
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

	if (component) {
		std::vector<ProjectileArc> arcs = componentGrid.use(component, *this, path, console);

		map->fireArcs(arcs);

		return true;
	}

	return false;
}

Optional<Component> &Entity::applyDamage(Damage damage, bool displayConsoleMsg) {
	Optional<Component> &component = componentGrid.getRandomComponent(); // TODO: Apply damage to component based on where the entity is shot from instead.

	if (component) {
		DEBUG_LOG("Applying damage to random component...");

		int turnsDisabledFor = component->applyDamage(damage);

		if (displayConsoleMsg) {
			std::string disabledText = (turnsDisabledFor > 0 ? " Disabled for turns: " + std::to_string(turnsDisabledFor) : "");

			if (component->isDestroyed()) {
				console.display({ getFullName() + " had component " + component->getName() + " destroyed!",
					isMemberOfPlayerFaction() ? Console::MessageType::FATAL : Console::MessageType::INFO });
			}
			else {
				console.display({ getFullName() + " recieved damage to component " + component->getName() + " - New integrity: " + std::to_string(component->getIntegrity()) + "/" +
					std::to_string(component->getMaxIntegrity()) + " Heat level: " + std::to_string(component->getHeatLevel()) + disabledText,
					isMemberOfPlayerFaction() ? Console::MessageType::WARNING : Console::MessageType::INFO }); // TODO: Take into account whether the entity is player controlled as well.
			}
		}
	}

	return component;
}

void Entity::say(std::string text, std::string speechManner) {
	console.display({ getFullName() + " " + speechManner + ": \"" + text + "\"", Console::MessageType::SPEECH });
}

bool Entity::isMemberOfPlayerFaction() {
	return map->isFactionPlayerFriendly(faction);
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