#include "ComponentGridGui.h"

ComponentGridGui::ComponentGridGui(Gui &parent, TurnManager &manager, std::shared_ptr<sf::Texture> texture, sf::Vector2f textureSizeComponent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Component Grid", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	currentComponentGrid(turnManager.getCurrentEntity()->getComponentGrid()), turnManager(manager), componentsTexture(texture),
	padding(0.05, 0.05), componentBoxColour(40, 40, 40, 255), componentBoxHoverColour(25, 25, 25, 255), componentBoxBorderColour(borderColour), componentTextureSize(textureSizeComponent)
{
	vertices.setPrimitiveType(sf::Quads);
	resize();
}

void ComponentGridGui::update(Input &input) {
	GuiWindow::update(input);

	if (turnManager.getCurrentEntity()->getComponentGrid().getGridSize() != currentComponentGrid.getGridSize()) {
		currentComponentGrid = turnManager.getCurrentEntity()->getComponentGrid();
		
		resize();
	}

	for (unsigned int x = 0; x < currentComponentGrid.getGridSize().x; x++) {
		for (unsigned int y = 0; y < currentComponentGrid.getGridSize().y; y++) {
			setupComponentQuad(sf::Vector2u(x, y));
		}
	}
}

void ComponentGridGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiWindow::draw(target, states);

	states.texture = componentsTexture.get();
	target.draw(vertices, states);
}

// Creates component boxes and resizes window.
void ComponentGridGui::resize() {
	const sf::Vector2u &gridSize = currentComponentGrid.getGridSize();

	vertices.resize(gridSize.x * gridSize.y * 4);
	
	destroyAllChildren();

	boxSize = sf::Vector2f((1.0 - padding.x) / gridSize.x - padding.x, (1.0 - padding.y) / gridSize.y - padding.y);

	for (unsigned int x = 0; x < currentComponentGrid.getGridSize().x; x++) {
		for (unsigned int y = 0; y < currentComponentGrid.getGridSize().y; y++) {

			addChild(std::make_unique<GuiWindow>("Component Box", *this,
				sf::Vector2f(padding.x + (padding.x + boxSize.x) * x,
					padding.y + (padding.y + boxSize.y) * y), boxSize, sf::Vector2f(0, 0),
				sf::Color(40, 40, 40, 255), componentBoxHoverColour, componentBoxBorderColour, 1));
		}
	}
}

void ComponentGridGui::setupComponentQuad(sf::Vector2u pos) {
	auto component = currentComponentGrid.getComponentAt(pos);

	if(component != nullptr) {
		const ComponentInfo info = component->fetchInfo();

		int index = pos.y * currentComponentGrid.getGridSize().x + pos.x;
		sf::Vertex *quad = &vertices[index * 4];
		auto &child = getChild(index);

		quad[0].position = child->getAbsolutePosition();
		quad[1].position = sf::Vector2f(child->getAbsolutePosition().x + child->getAbsoluteSize().x, child->getAbsolutePosition().y);
		quad[2].position = sf::Vector2f(child->getAbsolutePosition().x + child->getAbsoluteSize().x, child->getAbsolutePosition().y + child->getAbsoluteSize().y);
		quad[3].position = sf::Vector2f(child->getAbsolutePosition().x, child->getAbsolutePosition().y + child->getAbsoluteSize().y);

		quad[0].texCoords = sf::Vector2f(info.textureX * componentTextureSize.x, info.textureY * componentTextureSize.y);
		quad[1].texCoords = sf::Vector2f((info.textureX + 1) * componentTextureSize.x, info.textureY * componentTextureSize.y);
		quad[2].texCoords = sf::Vector2f((info.textureX + 1) * componentTextureSize.x, (info.textureY + 1) * componentTextureSize.y);
		quad[3].texCoords = sf::Vector2f(info.textureX * componentTextureSize.x, (info.textureY + 1) * componentTextureSize.y);

		quad[0].color = quad[1].color = quad[2].color = quad[3].color = component->getColour();
	}
}