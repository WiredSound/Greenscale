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

	Component(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager);
	void yourTurn();
	bool use();

	const ComponentInfo &fetchInfo();
	std::string getName();
	std::string getDescription();
	int getIntegrity();
	int getMaxIntegrity();
	int getHeatLevel();
	int getDangerousHeatLevel();
	int getFatalHeatLevel();
	int getPassivePower();
	int getUsePower();
	int getPassiveHeat();
	int getUseHeat();
	int getPowerStorage();
	std::vector<IDs::ComponentUpgrades> getPossibleUpgrades();

	sf::Vector2f getIconTextureSize();

	void applyDamage(Damage damage);
	void applyKineticDamage(int damage);
	void applyThermalDamage(int heat);
	void applyDisruption(float disruption);

	void increaseHeat(int amount);
	//void increasePower(int amount);

	bool isDestroyed();
	bool isEnabled();

	sf::Color getColour();

protected:
	virtual void yourTurnEnabled();
	virtual bool useEnabled();

	void increaseIntegrity(int amount);
	void reduceIntegrity(int amount);

private:
	IDs::Components id;
	std::shared_ptr<ComponentManager> manager;
	std::vector<ComponentUpgrade> upgrades;

	bool enabled;

	int integrity;
	int heat = 0;
	int disabledForTurns = 0;

	std::default_random_engine rand;
};