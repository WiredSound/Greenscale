#include "PlayerController.h"

#define PATH_IN_RANGE_COLOUR sf::Color(130, 255, 80, 255)
#define PATH_NOT_IN_RANGE_COLOUR sf::Color(255, 50, 50, 255)

PlayerController::PlayerController(sf::RenderWindow &renderWindow, GameGui &gameGui) : window(renderWindow), path(sf::Vector2u(0, 0)), gui(gameGui) {}

bool PlayerController::handleMovement(Entity *entity, Input &input) {
	GameMap *map = entity->getMapReference();

	if (targetSelected) {
		bool finishedMoving = entity->updateMovement();

		if (finishedMoving) {
			targetSelected = false;
			path = MovementPath(path.getStartPosition()); // This will make the attack path be immediately rebuilt.
		}

		return finishedMoving;
	}
	else if (entity->reachedPathTarget()) {
		if (gui.isMouseOverChildren()) {
			map->resetColourTilePath(path);
		}
		else { // If the mouse is not currently over the gui...
			drawCurrentPath(entity, map);

			sf::Vector2u tilePos = mouseCoordinatesInTiles(map);

			// Build a path if the player has moved their mouse over a new tile but only if that position is within bounds and free.
			if (path.getTargetPosition() != tilePos && map->withinBounds(tilePos) && map->isPositionFree(tilePos)) {
				map->resetColourTilePath(path); // Reset the colouring on the previous path.

				if (MovementPath::distanceFromTo(entity->getPosition(), tilePos) <= entity->getMovementRange() * 1.5)
					path = map->pathfinder.buildAStarPath(entity->getPosition(), tilePos);
				else
					path = MovementPath(tilePos);
			}

			if (input.isMouseButtonJustPressed(sf::Mouse::Button::Left)) {
				targetSelected = entity->setMovementPath(path);
			}
		}
	}

	return false;
}

bool PlayerController::handleAttacking(Entity *entity, Input &input) {
	GameMap *map = entity->getMapReference();

	if (targetSelected) {
		DEBUG_LOG(entity->name << " is firing!");

		path = MovementPath(path.getStartPosition()); // Reset the movement path.
		targetSelected = false;

		return true;
	}
	else {
		if (gui.isMouseOverChildren()) {
			map->resetColourTilePath(path);
		}
		else { // If the mouse is not currently over the gui...
			map->colourTilePath(path, sf::Color::Magenta);

			sf::Vector2u tilePos = mouseCoordinatesInTiles(map);

			if (path.getTargetPosition() != tilePos && map->withinBounds(tilePos)) {
				map->resetColourTilePath(path);

				path = MovementPath::buildLinePath(entity->getPosition(), tilePos);
			}

			if (input.isMouseButtonJustPressed(sf::Mouse::Button::Left)) {
				targetSelected = true;
			}
		}
	}

	return false;
}

void PlayerController::drawCurrentPath(Entity *entity, GameMap *map) {
	map->colourTilePath(path, (path.isComplete() && entity->withinRange(path.getLength()) ? PATH_IN_RANGE_COLOUR : PATH_NOT_IN_RANGE_COLOUR));
}

// Covert the mouse coordinates to the correct tile coordinates.
sf::Vector2u PlayerController::mouseCoordinatesInTiles(GameMap *map) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	return map->worldPosToTilePos(worldPos);
}