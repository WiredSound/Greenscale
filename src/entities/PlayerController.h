#pragma once

#include <thread>
#include "EntityController.h"
#include "../gui/GameGui.h"

class PlayerController : public EntityController {
public:
	PlayerController(sf::RenderWindow &renderWindow, GameGui &gameGui);
	virtual bool handle(Entity *entity, Input &input) override;
	//virtual bool handleMovement(Entity *entity, Input &input) override;
	//virtual bool handleAttacking(Entity *entity, Input &input) override;

private:
	GameGui &gui; // Reference to the game gui so movement/attack paths are not drawn when the mouse is over the gui.
	MovementPath path;
	sf::RenderWindow &window;
	bool moveMode = true; // Whether currently in moving or attacking mode.

	void drawMovementPath(MovementPath &path, Entity *entity, GameMap *map);
	MovementPath buildMoveModePath(Entity *entity, GameMap *map, const sf::Vector2u &mouseTilePos);
	MovementPath buildAttackModePath(Entity *entity, GameMap *map, const sf::Vector2u &mouseTilePos);
};