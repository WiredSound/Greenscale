#pragma once

#include "GuiWindow.h"
#include "../TurnManager.h"

class ComponentGridGui : public GuiWindow {
public:
	ComponentGridGui(Gui &parent, TurnManager &manager, std::shared_ptr<sf::Texture> texture, sf::Vector2f textureSizeComponent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness);

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::shared_ptr<sf::Texture> componentsTexture; // TODO: Set this up and finish building the vertex array.
	TurnManager &turnManager;
	ComponentGrid &currentComponentGrid;
	sf::VertexArray vertices;
	
	sf::Vector2f padding; // Space between the borders and component boxes.
	sf::Vector2f componentTextureSize;
	sf::Vector2f boxSize;

	sf::Color componentBoxColour;
	sf::Color componentBoxHoverColour;
	sf::Color componentBoxBorderColour;

	void resize();
	void setupComponentQuad(sf::Vector2u pos);
};