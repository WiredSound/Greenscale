#include "PlayerController.h"

#define PATH_IN_RANGE_COLOUR sf::Color(0, 255, 0, 255)
#define PATH_NOT_IN_RANGE_COLOUR sf::Color(255, 50, 50, 255)

PlayerController::PlayerController(sf::RenderWindow &renderWindow, GameGui &gameGui) : window(renderWindow), path(sf::Vector2u(0, 0)), gui(gameGui) {}

bool PlayerController::handle(Entity * entity, Input &input) {
	GameMap *map = entity->getMapReference();

	if (gui.isMouseOverChildren()) { // Remove any path colouring if the mouse moves over the GUI.
		map->resetColourTilePath(path);
	}
	else { // If the mouse is not over any GUI elements...
		sf::Vector2u mouseTilePos = map->mousePosToTilePos(window); // Get the map tile that the mouse is currently over.

		if (moveMode) {
			drawCurrentMovementPath(entity, map);

			// Build a path if the player has moved their mouse over a new tile but only if that position is within bounds and free.
			if (path.getTargetPosition() != mouseTilePos && map->withinBounds(mouseTilePos) && map->isPositionFree(mouseTilePos)) {
				map->resetColourTilePath(path); // Reset the colouring on the previous path.

				if (MovementPath::distanceFromTo(entity->getPosition(), mouseTilePos) <= entity->getMovementRange() * 1.5)
					path = map->pathfinder.buildAStarPath(entity->getPosition(), mouseTilePos);
				else
					path = MovementPath(mouseTilePos); // Build an incomplete path if the target is not in range.
			}

			if (input.isMouseButtonJustPressed(sf::Mouse::Button::Left)) {
				bool success = entity->setMovementPath(path);

				if (success) return true; // Path now set so player's turn ends.
			}
		}
		else { // Attack mode:
			map->colourTilePath(path, sf::Color::Magenta);

			if (path.getTargetPosition() != mouseTilePos && map->withinBounds(mouseTilePos)) {
				map->resetColourTilePath(path);

				path = MovementPath::buildLinePath(entity->getPosition(), mouseTilePos);
			}

			if (input.isMouseButtonJustPressed(sf::Mouse::Button::Left)) {
				DEBUG_LOG(entity->name << " is firing!");

				// TODO: Properly set up weapon firing.

				return true;
			}
		}
	}

	return false;
}

void PlayerController::drawCurrentMovementPath(Entity *entity, GameMap *map) {
	map->colourTilePath(path, (path.isComplete() && entity->withinRange(path.getLength()) ? PATH_IN_RANGE_COLOUR : PATH_NOT_IN_RANGE_COLOUR));
}