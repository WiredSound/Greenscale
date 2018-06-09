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

Optional<Component> &ComponentGrid::getComponentAt(sf::Vector2u pos) {
	return components[getIndex(pos)];
}

const sf::Vector2u &ComponentGrid::getGridSize() const {
	return gridSize;
}

// Gets the index of the components vector of components adjacent to pos (assuming they are within bounds).
std::vector<int> ComponentGrid::getAdjacentComponentIndexes(sf::Vector2u pos) {
	std::vector<int> indexes;

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

int ComponentGrid::getIndex(const sf::Vector2u &pos) {
	return pos.y * gridSize.x + pos.x;
}