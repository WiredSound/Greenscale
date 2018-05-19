#include "ComponentGrid.h"

ComponentGrid::ComponentGrid(sf::Vector2u size) {
	resize(size);
}

void ComponentGrid::turnPassed() {
	// TODO: Handle the transfer of heat and destroy components with 0 integrity.

	for (unsigned int x = 0; x < gridSize.x; x++) {
		for (unsigned int y = 0; y < gridSize.y; y++) {
			sf::Vector2u position(x, y);
			std::shared_ptr<Component> &component = getComponentAt(position);

			if (component != nullptr) {
				std::vector<int> adjacentIndexes = getAdjacentComponentIndexes(position);

				// TODO: This does not work correctly if there are no adjacent components!

				int heat = component->reduceHeatByPercentage(heatSpreadFraction);
				int heatPerComponent = heat / adjacentIndexes.size();

				for (int index : adjacentIndexes) {
					components[index]->increaseHeat(heatPerComponent);
				}
			}
		}
	}
}

std::shared_ptr<Component> ComponentGrid::getComponentAt(sf::Vector2u pos) {
	return components[getIndex(pos)];
}

void ComponentGrid::setComponentAt(sf::Vector2u pos, std::shared_ptr<Component> component) {
	components[getIndex(pos)] = component;
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

int ComponentGrid::getIndex(const sf::Vector2u &pos) {
	return pos.y * gridSize.x + pos.x;
}