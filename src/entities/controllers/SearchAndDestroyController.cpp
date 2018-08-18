#include "SearchAndDestroyController.h"

SearchAndDestroyController::SearchAndDestroyController(std::shared_ptr<Entity> target) : targetEntity(target), targetFaction(Faction::UNALIGNED), targetingIndividual(true) {}
SearchAndDestroyController::SearchAndDestroyController(Faction target) : targetFaction(target), targetingIndividual(false) {}

bool SearchAndDestroyController::handle(Entity *entity, Input &input) {
	ComponentGrid &grid = entity->getComponentGrid();

	std::vector<sf::Vector2u> positions = grid.findFunctionalPositions();

	for (sf::Vector2u position : positions) {
		Optional<Component> &component = grid.getComponentAt(position);

		if (component->atDangerousOrAboveHeatLevel() && entity->getPowerLevel() >= component->getPassivePowerConsumption()) {
			// If this hot component has cooling capabilities then use it:
			if (component->isActiveCooling()) {
				DEBUG_LOG(entity->getFullName() << " has decided to use active cooler " << component->getName() << " as it is currently at a fatal heat level.");

				grid.equipComponent(position);
				entity->useEquippedComponentOnSelf();

				return true;
			}

			// If this component generates heat on a per turn basis then disable it:
			if (component->isPassiveHeating())
				component->setManualEnable(false);
		}
		else {
			component->setManualEnable(true);

			// If the power level is less than half its max and this component is a generator then use it:
			if (entity->getPowerLevel() < (entity->getMaxPowerStorage() / 2) && component->isActivePowerGenerator()) {
				DEBUG_LOG(entity->getFullName() << " has decided to use power generator " << component->getName() << " due to low power level.");

				grid.equipComponent(position);
				entity->useEquippedComponentOnSelf();

				return true;
			}
		}
	}

	Optional<std::shared_ptr<Entity>> maybeTarget = findMostAppropriateTarget(entity);

	if (maybeTarget) {
		std::shared_ptr<Entity> targetEntity = *maybeTarget;

		DEBUG_LOG(entity->getFullName() << " has identified an appropriate target: " << targetEntity->getFullName());

		unsigned int requiredRange = MovementPath::distanceFromTo(entity->getPosition(), targetEntity->getPosition());
		unsigned int requiredPenetration = 0; // TODO: Calculate the required penetration.

		std::vector<sf::Vector2u> weaponPositions = grid.findWeaponPositions();

		// Sort the weapons based on their maximum potential damage:
		std::sort(weaponPositions.begin(), weaponPositions.end(), [&grid](sf::Vector2u pos0, sf::Vector2u pos1) {
			return grid.getComponentAt(pos0)->calculateMaxPotentialProjectileDamage() > grid.getComponentAt(pos1)->calculateMaxPotentialProjectileDamage();
		});

		for (sf::Vector2u weaponPosition : weaponPositions) {
			Optional<Component> &weapon = grid.getComponentAt(weaponPosition);
			unsigned int range = weapon->getProjectileRange();

			if (range >= requiredRange && weapon->getProjectilePenetration() >= requiredPenetration && weapon->getUsePowerConsumption() <= entity->getPowerLevel()) {
				DEBUG_LOG(entity->getFullName() << " has decided to fire weapon " << weapon->getName() << " at target.");

				grid.equipComponent(weaponPosition);
				entity->useEquippedComponent(entity->buildEquippedComponentPath(targetEntity->getPosition()));

				return true;
			}
		}

		// The method returns if a weapon is used so below is only run if no appropriate weapon is found.

		GameMap *map = entity->getMapReference();
		sf::Vector2u targetPosition = map->findNearestFreePosition(targetEntity->getPosition());

		MovementPath path = map->pathfinder.buildAStarPath(entity->getPosition(), targetPosition);
		path.restrictLength(entity->getMovementRange());

		path.recursivelyShortenBasedOn([&path, &targetEntity]() {
			return MovementPath::distanceFromTo(path.getTargetPosition(), targetEntity->getPosition()) < 3; // TODO: Find best distance to target based upon the range of the shortest weapon.
		});

		entity->setMovementPath(path);
	}

	return true;
}

Optional<std::shared_ptr<Entity>> SearchAndDestroyController::findMostAppropriateTarget(Entity *entity) {
	if (targetingIndividual) return targetEntity.lock();

	GameMap *map = entity->getMapReference();

	Optional<std::shared_ptr<Entity>> bestTarget;
	unsigned int distanceToBestTarget;

	for (auto &potentialTarget : map->getEntitiesInFaction(targetFaction)) {
		unsigned int distance = MovementPath::distanceFromTo(entity->getPosition(), potentialTarget->getPosition());

		// Check if there is either no current best target or if the considered target is closer to the entity than the current best target...
		if (!bestTarget || distance < distanceToBestTarget) {
			bestTarget.set(potentialTarget);
			distanceToBestTarget = distance;
		}
	}

	return bestTarget;
}