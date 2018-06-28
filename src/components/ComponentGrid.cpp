#include "ComponentGrid.h"

ComponentGrid::ComponentGrid(sf::Vector2u size) {
	resize(size);
}

void ComponentGrid::turnPassed() {
	// TODO: Handle the transfer of heat and destroy components with 0 integrity.

	for (unsigned int x = 0; x < gridSize.x; x++) {
		for (unsigned int y = 0; y < gridSize.y; y++) {
			sf::Vector2u position(x, y);
			auto &component = getComponentAt(position);

			if (component) {
				component->yourTurn();

				if (component->isDestroyed())
					component.remove();
			}
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

const sf::Vector2u &ComponentGrid::getGridSize() const {
	return gridSize;
}

// Gets the index of the components vector of components adjacent to pos (assuming they are within bounds).
// TODO: Handle when a position on the edge of the grid is given.
std::vector<unsigned int> ComponentGrid::getAdjacentComponentIndexes(sf::Vector2u pos) {
	std::vector<unsigned int> indexes;

	if (pos.x < gridSize.x)
		indexes.push_back(getIndex(sf::Vector2u(pos.x + 1, pos.y)));
	if (pos.x > 0)
		indexes.push_back(getIndex(sf::Vector2u(pos.x - 1, pos.y)));
	if (pos.y < gridSize.y)
		indexes.push_back(getIndex(sf::Vector2u(pos.x, pos.y + 1)));
	if (pos.y > 0)
		indexes.push_back(getIndex(sf::Vector2u(pos.x, pos.y - 1)));

	return indexes;
}

std::vector<unsigned int> ComponentGrid::getFunctionalComponentIndexes() {
	std::vector<unsigned int> indexes;

	for (unsigned int i = 0; i < components.size(); i++) {
		if (getComponentByIndex(i) && getComponentByIndex(i)->getIntegrity() > 0)
			indexes.push_back(i);
	}

	return indexes;
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

	for (auto &component : components) {
		if (component) maxIntegrity += component->getMaxIntegrity();
	}

	return maxIntegrity;
}

unsigned int ComponentGrid::getMaxPowerStorage() {
	unsigned int powerStorage = 0;

	for (auto &component : components) {
		if (component) powerStorage += component->getPowerStorage();
	}

	return powerStorage;
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

void ComponentGrid::applyDamageToRandomComponent(Damage damage) {
	std::vector<unsigned int> functionalIndexes = getFunctionalComponentIndexes();

	if (functionalIndexes.size() > 0) {
		unsigned int randomFunctionalComponentIndex = functionalIndexes[rand() % functionalIndexes.size()];

		auto &randomComponent = getComponentByIndex(randomFunctionalComponentIndex);
		assert(randomComponent);

		DEBUG_LOG("Applying damage to random component: " << randomComponent->getName());

		randomComponent->applyDamage(damage);
	}
	else {
		DEBUG_LOG("The entity hit has no functional components to apply damage to!");
	}
}

unsigned int ComponentGrid::getIndex(const sf::Vector2u &pos) {
	return pos.y * gridSize.x + pos.x;
}