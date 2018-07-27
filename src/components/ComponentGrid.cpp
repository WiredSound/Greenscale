#include "ComponentGrid.h"

// This is another cryptically named macro that is similar to the one found in the Component.cpp file.
// It's purpose is to make the creation of methods like findWeaponPositions, findActiveCoolerPositions, etc. require less boilerplate code.
#define GET_COMPONENT_POSITIONS_WHERE(methodName, fromComponentsPosition)					\
	std::vector<sf::Vector2u> positions;													\
																							\
	for(sf::Vector2u componentPosition : (fromComponentsPosition)) {						\
		Optional<Component> &component = getComponentAt(componentPosition);					\
		if (component && component->methodName())											\
			positions.push_back(componentPosition);											\
	}																						\
	return positions;
// C++ really needs multiline macros...

ComponentGrid::ComponentGrid(sf::Vector2u size) : power(*this) {
	resize(size);
}

void ComponentGrid::turnPassed(Entity &entity, Console &console) {
	// TODO: Handle the transfer of heat and disruption and destroy components with 0 integrity.

	for (sf::Vector2u position : findAllGridPositions()) {
		auto &component = getComponentAt(position);

		if (component) {
			component->yourTurn(entity, power, console);

			auto adjacent = findFunctionalPositions(adjacentPositionsTo(position));
			auto heatShareTotal = static_cast<unsigned int>(component->getHeatLevel() * heatSpreadFraction); // The amount of heat to be distributed between all of the adjacent components.
			auto heatShare = adjacent.size() > 0 ? static_cast<unsigned int>(heatShareTotal / adjacent.size()) : 0u; // The amount of heat distributed for each component individually.

			for (sf::Vector2u adjacentPosition : adjacent) {
				Optional<Component> &adjacentComponent = getComponentAt(adjacentPosition);

				DEBUG_LOG_SPAM("Component at " << position.x << ", " << position.y << " spreading heat " << heatShare << " to adjacent component at: " << adjacentPosition.x << ", " << adjacentPosition.y);

				component->decreaseHeat(heatShare);
				adjacentComponent->increaseHeat(heatShare);
			}

			if (component->isDestroyed()) component.remove();
		}
	}
}

Optional<Component> &ComponentGrid::getComponentByIndex(unsigned int index) {
	if (index < components.size())
		return components[index];

	return noComponent;
}

Optional<Component> &ComponentGrid::getComponentAt(sf::Vector2u pos) {
	return getComponentByIndex(getIndex(pos));
}

Optional<Component> &ComponentGrid::getRandomComponent() {
	std::vector<sf::Vector2u> functionalPositions = findFunctionalPositions();

	if (functionalPositions.size() > 0) {
		sf::Vector2u randomFunctionalPosition = functionalPositions[rand() % functionalPositions.size()];

		return getComponentAt(randomFunctionalPosition);
	}

	return noComponent;
}

const sf::Vector2u &ComponentGrid::getGridSize() const {
	return gridSize;
}

void ComponentGrid::resize(sf::Vector2u size) {
	components.resize(size.x * size.y);
	gridSize = size;
}

unsigned int ComponentGrid::getCurrentIntegrity() {
	unsigned int integrity = 0;

	for (auto &component : components) {
		if (component) integrity += component->getIntegrity();
	}

	return integrity;
}

unsigned int ComponentGrid::getMaxIntegrity() {
	unsigned int maxIntegrity = 0;

	for (auto &component : components)
		if (component) maxIntegrity += component->getMaxIntegrity();

	return maxIntegrity;
}

unsigned int ComponentGrid::getPowerStored() {
	return power.getPowerLevel();
}

unsigned int ComponentGrid::getMaxPowerStorage() {
	unsigned int powerStorage = 0;

	for (auto &component : components)
		if (component && component->isEnabled()) powerStorage += component->getPowerStorage();

	return powerStorage;
}

unsigned int ComponentGrid::getMovementRange() {
	unsigned int movementRange = 0;

	for (auto &component : components)
		if (component && component->isEnabled()) movementRange += component->getMovementRange();

	return std::max(movementRange, 1u);
}

Optional<Component> &ComponentGrid::getEquippedComponent() {
	if (componentEquipped)
		return getComponentAt(equippedPosition);

	return noComponent;
}

sf::Vector2u ComponentGrid::getEquippedComponentGridPosition() {
	return equippedPosition;
}

void ComponentGrid::equipComponent(sf::Vector2u pos) {
	componentEquipped = true;
	equippedPosition = pos;
}

void ComponentGrid::unequipComponent() {
	componentEquipped = false;
}

bool ComponentGrid::isComponentEquipped() {
	return componentEquipped;
}

void ComponentGrid::swapPositions(sf::Vector2u firstPos, sf::Vector2u secondPos) {
	std::iter_swap(components.begin() + getIndex(firstPos), components.begin() + getIndex(secondPos)); // TODO: Add checks to ensure that both positions are within bounds.
}

std::vector<ProjectileArc> ComponentGrid::use(Optional<Component> &component, Entity &user, MovementPath path, Console &console) {
	return component->use(user, path, power, console);
}

std::vector<ProjectileArc> ComponentGrid::use(sf::Vector2u position, Entity &user, MovementPath path, Console &console) {
	auto &component = getComponentAt(position);

	if (component)
		return component->use(user, path, power, console);

	return std::vector<ProjectileArc>();
}

std::vector<sf::Vector2u> ComponentGrid::findAllGridPositions() {
	std::vector<sf::Vector2u> positions;

	for (unsigned int x = 0; x < gridSize.x; x++) {
		for (unsigned int y = 0; y < gridSize.y; y++) {
			positions.push_back(sf::Vector2u(x, y));
		}
	}

	return positions;
}
std::vector<sf::Vector2u> ComponentGrid::findFunctionalPositions() { GET_COMPONENT_POSITIONS_WHERE(isFunctional, findAllGridPositions()) }
std::vector<sf::Vector2u> ComponentGrid::findFunctionalPositions(std::vector<sf::Vector2u> from) { GET_COMPONENT_POSITIONS_WHERE(isFunctional, from) }
std::vector<sf::Vector2u> ComponentGrid::findWeaponPositions() { GET_COMPONENT_POSITIONS_WHERE(isWeapon, findAllGridPositions()) }
std::vector<sf::Vector2u> ComponentGrid::findActiveCoolingPositions() { GET_COMPONENT_POSITIONS_WHERE(isActiveCooling, findAllGridPositions()) }
std::vector<sf::Vector2u> ComponentGrid::findPassiveCoolingPositions() { GET_COMPONENT_POSITIONS_WHERE(isPassiveCooling, findAllGridPositions()) }
std::vector<sf::Vector2u> ComponentGrid::findFatalHeatPositions() { GET_COMPONENT_POSITIONS_WHERE(atFatalHeatLevel, findAllGridPositions()) }
std::vector<sf::Vector2u> ComponentGrid::findDangerousHeatPositions() { GET_COMPONENT_POSITIONS_WHERE(atDangerousHeatLevel, findAllGridPositions()) }
std::vector<sf::Vector2u> ComponentGrid::findHotPositions() { GET_COMPONENT_POSITIONS_WHERE(atDangerousOrAboveHeatLevel, findAllGridPositions()) }

std::vector<sf::Vector2u> ComponentGrid::adjacentPositionsTo(sf::Vector2u pos) {
	std::vector<sf::Vector2u> adjacent;

	if (pos.x > 0) adjacent.push_back(sf::Vector2u(pos.x - 1, pos.y)); // LEFT
	if (pos.y > 0) adjacent.push_back(sf::Vector2u(pos.x, pos.y - 1)); // ABOVE
	if (pos.x < gridSize.x) adjacent.push_back(sf::Vector2u(pos.x + 1, pos.y)); // RIGHT
	if (pos.y < gridSize.y) adjacent.push_back(sf::Vector2u(pos.x, pos.y + 1)); // BELOW
	if (pos.x > 0 && pos.y > 0) adjacent.push_back(sf::Vector2u(pos.x - 1, pos.y - 1)); // LEFT ABOVE
	if (pos.x > 0 && pos.y < gridSize.y) adjacent.push_back(sf::Vector2u(pos.x - 1, pos.y + 1)); // LEFT BELOW
	if (pos.x < gridSize.x && pos.y > 0) adjacent.push_back(sf::Vector2u(pos.x + 1, pos.y - 1)); // RIGHT ABOVE
	if (pos.x < gridSize.x && pos.y < gridSize.y) adjacent.push_back(sf::Vector2u(pos.x + 1, pos.y + 1)); // RIGHT BELOW

	return adjacent;
}

unsigned int ComponentGrid::getIndex(const sf::Vector2u &pos) {
	return pos.y * gridSize.x + pos.x;
}