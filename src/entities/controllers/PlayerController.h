#pragma once

#include "EntityController.h"
class GameGui;

class PlayerController : public EntityController {
public:
	PlayerController(GameGui &gameGui, Console &consoleRef, Camera &cameraRef);
	virtual bool handle(Entity *entity, Input &input) override;

	bool isInMoveMode();
	void toggleMoveUseMode(Entity *entity);

private:
	GameGui &gui; // Reference to the game gui so movement/attack paths are not drawn when the mouse is over the gui.
	Console &console;
	Camera &camera;

	MovementPath path;
	bool moveMode{ true }; // Whether currently in moving or attacking mode.
	sf::Vector2u lastMouseTilePos;

	void drawMovementPath(MovementPath &drawPath, Entity *entity, GameMap *map);
	MovementPath buildMoveModePath(Entity *entity, GameMap *map, const sf::Vector2u &mouseTilePos);
	MovementPath buildAttackModePath(Entity *entity, GameMap *map, const sf::Vector2u &mouseTilePos);
	void reset(MovementPath &path, sf::Vector2u pos, GameMap *map);
};