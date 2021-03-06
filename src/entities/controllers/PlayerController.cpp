#include "entities/controllers/PlayerController.h"

#include "gui/GameGui.h"

#define PATH_IN_RANGE_COLOUR sf::Color(0, 255, 0, 255)
#define PATH_NOT_IN_RANGE_COLOUR sf::Color(255, 50, 50, 255)
#define ATTACK_PATH_COLOUR sf::Color::Magenta

PlayerController::PlayerController(GameGui &gameGui, Console &consoleRef, Camera &cameraRef) : path(sf::Vector2u(0, 0)), gui(gameGui), console(consoleRef), camera(cameraRef) {}

bool PlayerController::handle(Entity *entity, Input &input) {
	GameMap *map = entity->getMapPtr();

	sf::Vector2f mousePos = input.getMouseWorldPosition();
	sf::Vector2u mouseTilePos = map->worldPosToTilePos(mousePos); // Get the map tile that the mouse is currently over.

	if (input.isKeyJustPressed(sf::Keyboard::Key::M)) toggleMoveUseMode(entity);

	if (gui.isMouseOverChildren()) { // Remove any path colouring if the mouse moves over the GUI.
		map->resetColourTilePath(path);
	}
	else { // If the mouse is not over any GUI elements...
		if (moveMode) { // Move mode:
			// Build a path if the player has moved their mouse over a new tile but only if that position is within bounds and free.
			if (path.getTargetPosition() != mouseTilePos && map->withinBounds(mouseTilePos) && map->isPositionFree(mouseTilePos))
				path = buildMoveModePath(entity, map, mouseTilePos);

			drawMovementPath(path, entity, map);

			if (input.isMouseButtonJustPressed(sf::Mouse::Button::Left)) {
				bool success = entity->setMovementPath(path);

				if (success) {
					reset(path, mouseTilePos, map);
					return true; // Path now set so player's turn ends.
				}
			}

			if (input.isMouseButtonJustPressed(sf::Mouse::Button::Right))
				camera.moveTowardsCentre(mousePos, 0.15f); // Allow the player to right click on an area and have the camera focus on that point.
		}
		else { // Attack mode:
			if (lastMouseTilePos != mouseTilePos && map->withinBounds(mouseTilePos)) {
				path = buildAttackModePath(entity, map, mouseTilePos);
				lastMouseTilePos = mouseTilePos;
			}

			map->colourTilePath(path, ATTACK_PATH_COLOUR);

			if (input.isMouseButtonJustPressed(sf::Mouse::Button::Left)) {
				DEBUG_LOG(entity->getFullName() << " is attempting to use component...");

				bool success = entity->useEquippedComponent(path);

				if (!success) console.display({ "The equipped component can either not be used in this manner or is not enabled!", Console::MessageType::WARNING });

				return success;
			}
		}
	}

	return false;
}

bool PlayerController::isInMoveMode() {
	return moveMode;
}

void PlayerController::toggleMoveUseMode(Entity *entity) {
	moveMode = !moveMode;
	reset(path, entity->getPosition(), entity->getMapPtr());
}

void PlayerController::drawMovementPath(MovementPath &drawPath, Entity *entity, GameMap *map) {
	map->colourTilePath(drawPath, (path.isComplete() && entity->withinRange(drawPath.getLength()) ? PATH_IN_RANGE_COLOUR : PATH_NOT_IN_RANGE_COLOUR));
}

MovementPath PlayerController::buildMoveModePath(Entity *entity, GameMap *map, const sf::Vector2u &mouseTilePos) {
	map->resetColourTilePath(path); // Reset the colouring on the previous path.

	if (MovementPath::distanceFromTo(entity->getPosition(), mouseTilePos) <= entity->getMovementRange() * 1.5)
		return map->pathfinder.buildAStarPath(entity->getPosition(), mouseTilePos);

	return MovementPath(mouseTilePos); // Build an incomplete path if the target is not in range.
}

MovementPath PlayerController::buildAttackModePath(Entity *entity, GameMap *map, const sf::Vector2u &mouseTilePos) {
	map->resetColourTilePath(path);

	return entity->buildEquippedComponentPath(mouseTilePos);
}

void PlayerController::reset(MovementPath &resetPath, sf::Vector2u pos, GameMap *map) {
	map->resetColourTilePath(resetPath);
}
