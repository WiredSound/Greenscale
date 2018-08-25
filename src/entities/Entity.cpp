#include "Entity.h"

#include "controllers/EntityController.h"

PulsingColour Entity::myTurnColourPulse(0.8f, 1.0f, 0.005f);

Entity::Entity(IDs::Entities entityId, std::shared_ptr<EntityManager> entityManager, std::string entityName, sf::Vector2u entityPosition, Faction entityFaction, sf::Vector2u gridSize,
	std::shared_ptr<EntityController> entityController, Console &consoleRef, EntityBuilder &entityBuilder)
	: id(entityId), manager(entityManager), personalName(entityName), position(entityPosition), faction(entityFaction), componentGrid(gridSize),
	controller(entityController), console(consoleRef), builder(entityBuilder), currentPath(entityPosition), visualMovementSpeed(sf::milliseconds(150)) {}

/**
 * Called once by TurnManager when it first becomes this entity's turn.
 */
void Entity::yourTurnBegin() {
	DEBUG_LOG("Turn begins for entity: " << personalName);
	myTurn = true;
}

/**
 * Where the Entity call upon its EntityController in order to decide what action it will take this turn.
 * TurnManager will continually call this method until `true` is returned.
 */
bool Entity::yourTurnDecision(Input &input) {
	return controller->handle(this, input); // Controller, can you handle this? I don't think they can handle this!
}

/**
 * Once it is decided what the entity will do this turn, this method is called to allow that action to take place.
 * TurnManager will continually call this method until `true` is returned.
 */
bool Entity::yourTurnCurrently() {
	return updateMovement() && updateAttacking();
}

/**
 * Called once by TurnManager when this entity's turn has ended.
 */
void Entity::yourTurnEnd() {
	componentGrid.turnPassed(*this, console);
	DEBUG_LOG("Turn ends for entity: " << personalName);
	myTurn = false;
}

bool Entity::isMyTurn() {
	return myTurn;
}

/**
 * Moves the entity along its current movement path.
 * \return Whether the entity has reached ther target position of its current movement path.
 */
bool Entity::updateMovement() {
	if (!currentPath.reachedTarget() && movementClock.getElapsedTime() >= visualMovementSpeed) {
		movementClock.restart();

		moveDirectlyToPosition(currentPath.currentPosition());
		currentPath.nextPosition();
	}

	return currentPath.reachedTarget();
}

/**
 * Checks whether the GameMap has finished showing all ProjectileArcs.
 */
bool Entity::updateAttacking() {
	return map->areAllProjectileArcsComplete();
}

sf::Vector2u Entity::getPosition() const {
	return position;
}

sf::Vector2u Entity::getSize() {
	return fetchInfo().size;
}

sf::Vector2f Entity::getAbsoluteCentrePosition() const {
	auto pos = map->tilePosToWorldPos(position);
	return sf::Vector2f(pos.x + map->tileSize.x / 2, pos.y + map->tileSize.y / 2);
}

Faction Entity::getFaction() {
	return faction;
}

bool Entity::reachedPathTarget() {
	return currentPath.reachedTarget();
}

bool Entity::withinRange(unsigned int distance) {
	return distance <= getMovementRange();
}

bool Entity::overPosition(sf::Vector2u pos) {
	return pos.x >= position.x && pos.x < position.x + getSize().x
		&& pos.y >= position.y && pos.y < position.y + getSize().y;
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

unsigned int Entity::getMovementRange() {
	return componentGrid.getMovementRange();
}

std::string Entity::getPersonalName() {
	return personalName;
}

std::string Entity::getFullName() {
	return getPersonalName() + " (" + getEntityName() + ")";
}

/**
 * The integrity of an entity is the sum of the integrity of every component in its component grid. See ComponentGrid::getCurrentIntegrity.
 */
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

/**
 * Attempts to build a use path for the currently equipped component.
 * If the equipped component is a weapon for example, the returned path will be the path that the projectile will follow. Most regular components meant to be self-used just return an incomplete path
 * initialised with the entity's position.
 * \return Whether using the component was successful.
 */
MovementPath Entity::buildEquippedComponentPath(sf::Vector2u target) {
	auto &component = componentGrid.getEquippedComponent();

	if (component) {
		return component->buildProjectilePath(getPosition(), target, map);
	}

	return MovementPath(getPosition());
}

/**
 * Use the equipped component on this entity.
 * \return Whether using the component was successful.
 */
bool Entity::useEquippedComponentOnSelf() {
	return useEquippedComponent(buildEquippedComponentPath(getPosition()));
}

/**
 * Use the equipped component along the specified movement path. Should the component produce any projectile arcs, they will be passed to the map via GameMap::fireArcs.
 * \return Whether using the component was successful.
 */
bool Entity::useEquippedComponent(MovementPath path) {
	auto &component = componentGrid.getEquippedComponent();

	if (component) {
		std::vector<ProjectileArc> arcs = componentGrid.use(component, *this, path, console);

		map->fireArcs(arcs);
		return true;
	}

	return false;
}

/**
 * Applies damage to the entity. Since entities have no health of their own, all damage is applied to a random component in the entity's ComponentGrid.
 */
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

/**
 * Makes the camera move towards the centre of this entity.
 */
void Entity::focusCameraOn(Camera &camera) {
	camera.moveTowardsCentre(getAbsoluteCentrePosition(), 0.1f);
}

bool Entity::isBlocking() {
	return true; // TODO: Implement this properly.
}

sf::Color Entity::getColour() {
	return (myTurn ? myTurnColourPulse.getColour(sf::Color::White) : sf::Color::White);
}

bool Entity::moveDirectlyBy(sf::Vector2u movement) {
	if (map != nullptr) {
		if (map->isPositionFree(position + movement, getSize())) {
			position = position + movement;
			return true;
		}
	}
	return false;
}

bool Entity::moveDirectlyToPosition(sf::Vector2u newPos) {
	if (map != nullptr) {
		if (map->isPositionFree(newPos, getSize())) {
			position = newPos;
			return true;
		}
	}
	return false;
}

void Entity::setMap(GameMap *gameMap) {
	map = gameMap;
}

GameMap *Entity::getMapPtr() {
	return map;
}

std::shared_ptr<EntityController> Entity::getController() {
	return controller;
}

char Entity::getPriority() {
	return faction.priority;
}

ComponentGrid &Entity::getComponentGrid() {
	return componentGrid;
}