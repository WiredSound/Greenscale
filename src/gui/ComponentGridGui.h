#pragma once

#include "ComponentGridGuiBox.h"
#include "../TurnManager.h"

class ComponentGridGui : public GuiWindow {
public:
	ComponentGridGui(Gui &parent, TurnManager &manager, std::shared_ptr<sf::Texture> texture, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness);

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Optional<Component> &getComponentHoveredOver();

	unsigned int getGridIndex(sf::Vector2u pos, const ComponentGrid &grid);

	//friend ComponentGridGuiBox;
	// This use of the 'friend' keyword is probably bad practise so instead made the below public:
	void hoveringOverGridPosition(sf::Vector2u gridPosition);
	void equipGridPosition(sf::Vector2u gridPosition);

private:
	sf::Vector2u hoverGridPosition;
	sf::Vector2u equippedGridPosition;

	std::shared_ptr<sf::Texture> componentsTexture;
	TurnManager &turnManager;
	sf::Vector2u currentGridSize;
	sf::VertexArray vertices;

	sf::Vector2f padding; // Space between the borders and component boxes.
	sf::Vector2f boxSize;

	sf::Color componentBoxColour;
	sf::Color componentBoxHoverColour;
	sf::Color componentBoxBorderColour;

	ComponentGrid &fetchCurrentGrid();

	void resize(const sf::Vector2u &gridSize);
	void setupComponentQuad(sf::Vector2u pos, ComponentGrid &grid);
};