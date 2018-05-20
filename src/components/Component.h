#pragma once

#include <random>
#include <SFML/Graphics/Texture.hpp>
#include "ComponentManager.h"

class Component {
public:
	struct Damage {
		int kinetic; // Applies a direct reduction of the component's integrity.
		int thermal; // Adds heat to the component. Some heat can disable the component temporarily while larger amounts can disable it permanently or cause it to explode.
		float disruption; // Liklihood that the component will become disabled temporarily or malfunction.
	};

	Component(IDs::Components componentId, ComponentManager &componentManager);
	void yourTurn();

	const ComponentInfo &fetchInfo();

	void applyDamage(Damage damage);
	void applyKineticDamage(int damage);
	void applyThermalDamage(int heat);
	void applyDisruption(float disruption);

	void increaseHeat(int amount);
	void reduceHeat(int amount);
	int reduceHeatByPercentage(float percentage);

	bool isDestroyed();

	sf::Color getColour();

protected:
	void increaseIntegrity(int amount);
	void reduceIntegrity(int amount);

private:
	IDs::Components id;
	int integrity;
	int heat = 0;
	int disabledForTurns = 0; // TODO: Take this into account.

	std::default_random_engine rand;

	ComponentManager &manager;
};