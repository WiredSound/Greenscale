#include "entities/controllers/SpawnerController.h"

bool SpawnerController::handle(Entity *entity, Input &input) {
	ComponentGrid &grid = entity->getComponentGrid();

	// Enable all passive power generating components if they're at safe heat levels:
	for (sf::Vector2u passivePowerPos : grid.findPassivePowerGenPositions()) {
		auto &component = grid.getComponentAt(passivePowerPos);

		component->setManualEnable(!component->atDangerousOrAboveHeatLevel());
	}

	// Attempt to use a spawner component and return if successful:
	for (sf::Vector2u spawnerPos : grid.findSpawnerPositions()) {
		auto &component = grid.getComponentAt(spawnerPos);

		if (entity->getPowerLevel() >= static_cast<int>(component->getUsePowerConsumption())) {
			grid.equipComponent(spawnerPos);
			entity->useEquippedComponentOnSelf();

			return true;
		}
	}

	for (sf::Vector2u activePowerPos : grid.findActivePowerGenPositions()) {
	}
}
