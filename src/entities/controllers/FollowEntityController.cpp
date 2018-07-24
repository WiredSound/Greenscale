#include "FollowEntityController.h"

FollowEntityController::FollowEntityController(std::shared_ptr<Entity> target, unsigned int idealDistance, Console &consoleRef)
	: targetEntity(target), idealDistanceFromTarget(idealDistance), console(consoleRef) {}

bool FollowEntityController::handle(Entity *entity, Input &input) {
	GameMap *map = entity->getMapReference();

	if (auto target = targetEntity.lock()) {
		sf::Vector2u targetPosition = map->findNearestFreePosition(target->getPosition());

		MovementPath path = map->pathfinder.buildAStarPath(entity->getPosition(), targetPosition);
		path.restrictLength(entity->getMovementRange());

		// This loop shortens the path so that the entity stays around the ideal distance from the target:
		while (MovementPath::distanceFromTo(path.getTargetPosition(), targetPosition) < idealDistanceFromTarget && path.getLength() > 1)
			path.restrictLength(path.getLength() - 1);

		if (path.getLength() > 0)
			console.display({ entity->getFullName() + " obediently follows " + target->getFullName() + "...", Console::MessageType::INFO_NONESSENTIAL });

		entity->setMovementPath(path);
	}

	return true;
}