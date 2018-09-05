#pragma once

#include "ComponentGridGuiBox.h"
#include "../TurnManager.h"

class ComponentGridGui : public GuiWindow {
public:
	ComponentGridGui(Gui &parent, TurnManager &manager, std::shared_ptr<sf::Texture> texture, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness);

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Optional<Component> &getComponentHoveredOver();
	Optional<Component> &getHeldComponent();

	unsigned int getGridIndex(sf::Vector2u pos, const ComponentGrid &grid);

	//friend ComponentGridGuiBox;
	// This use of the 'friend' keyword is probably bad practise so instead made the below public:
	void hoveringOverGridPosition(sf::Vector2u gridPosition);
	void equipGridPosition(sf::Vector2u gridPosition);
	void toggleEnableGridPosition(sf::Vector2u gridPosition);

	void mouseToggleHolding(sf::Vector2u gridPosition);
	void mousePickupPosition(sf::Vector2u gridPosition);
	void mousePutDownHeldPosition();
	void mousePutDownHeldPosition(sf::Vector2u newPosition);

private:
	sf::Vector2u hoverGridPosition;

	std::shared_ptr<sf::Texture> componentsTexture;
	TurnManager &turnManager;
	sf::VertexArray vertices;

	sf::Vector2f padding; // Space between the borders and component boxes.
	sf::Vector2f boxSize;

	sf::Color componentBoxColour;
	sf::Color componentBoxHoverColour;
	sf::Color componentBoxEquippedBorderColour;
	sf::Color componentBoxUnequippedBorderColour;

	ComponentGrid *previousComponentGrid;
	ComponentGrid &fetchCurrentGrid();

	sf::Vector2u mouseHeldGridPosition;
	bool mouseHoldingComponent;

	ComponentGridGuiBox *getGridBox(sf::Vector2u pos, ComponentGrid &grid);

	void setup(ComponentGrid &grid);
	void setupComponentQuad(sf::Vector2u pos, ComponentGrid &grid, Input &input);
};