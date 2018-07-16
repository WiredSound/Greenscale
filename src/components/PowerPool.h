#pragma once

class ComponentGrid;

class PowerPool {
public:
	PowerPool(ComponentGrid &componentGrid);
	unsigned int getPowerLevel();

	bool hasSufficientPower(unsigned int amount);
	void increasePower(unsigned int amount);
	void decreasePower(unsigned int amount);

private:
	ComponentGrid &grid;
	unsigned int power = 0;
};