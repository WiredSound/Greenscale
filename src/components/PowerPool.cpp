#include "PowerPool.h"

#include "ComponentGrid.h"

PowerPool::PowerPool(ComponentGrid &componentGrid) : grid(componentGrid) {}

unsigned int PowerPool::getPowerLevel() {
	return power;
}

bool PowerPool::hasSufficientPower(unsigned int amount) {
	return power >= amount;
}

void PowerPool::increasePower(unsigned int amount) {
	power += amount;
	if (power > grid.getMaxPowerStorage()) power = grid.getMaxPowerStorage();
}

void PowerPool::decreasePower(unsigned int amount) {
	power = hasSufficientPower(amount) ? (power - amount) : 0;
}