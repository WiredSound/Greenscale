#include "ComponentGridGui.h"

ComponentGridGui::ComponentGridGui(Gui &parent, TurnManager &manager, std::shared_ptr<sf::Texture> texture, sf::Vector2f textureSizeComponent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Component Grid", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	turnManager(manager), componentsTexture(texture),
	padding(0.05f, 0.05f), componentBoxColour(40, 40, 40, 255), componentBoxHoverColour(25, 25, 25, 255), componentBoxBorderColour(borderColour), componentTextureSize(textureSizeComponent)
{
	vertices.setPrimitiveType(sf::Quads);
}

void ComponentGridGui::update(Input &input) {
	GuiWindow::update(input);

	ComponentGrid &currentGrid = fetchCurrentGrid();

	if (currentGrid.getGridSize() != currentGridSize) {
		resize(currentGrid.getGridSize());
	}

	for (unsigned int x = 0; x < currentGrid.getGridSize().x; x++) {
		for (unsigned int y = 0; y < currentGrid.getGridSize().y; y++) {
			setupComponentQuad(sf::Vector2u(x, y), currentGrid);
		}
	}
}

void ComponentGridGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiWindow::draw(target, states);

	states.texture = componentsTexture.get();
	target.draw(vertices, states);
}

Optional<Component> &ComponentGridGui::getComponentHoveredOver() {
	return fetchCurrentGrid().getComponentAt(hoverGridPosition);
}

// Creates component boxes and resizes window.
void ComponentGridGui::resize(const sf::Vector2u &gridSize) {
	vertices.resize(gridSize.x * gridSize.y * 4);

	destroyAllChildren();

	boxSize = sf::Vector2f((1.0f - padding.x) / gridSize.x - padding.x, (1.0f - padding.y) / gridSize.y - padding.y);

	for (unsigned int x = 0; x < gridSize.x; x++) {
		for (unsigned int y = 0; y < gridSize.y; y++) {
			addChild(std::make_unique<ComponentGridGuiBox>(*this, sf::Vector2u(x, y),
				sf::Vector2f(padding.x + (padding.x + boxSize.x) * x,
					padding.y + (padding.y + boxSize.y) * y), boxSize,
				sf::Color(40, 40, 40, 255), componentBoxHoverColour, componentBoxBorderColour));
		}
	}

	currentGridSize = gridSize;
}

void ComponentGridGui::setupComponentQuad(sf::Vector2u pos, ComponentGrid &grid) {
	auto &component = grid.getComponentAt(pos);

	int index = pos.y * grid.getGridSize().x + pos.x;
	sf::Vertex *quad = &vertices[index * 4];

	if (component) {
		const ComponentInfo info = component->fetchInfo();

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
	else {
		// Remove any textures applied from previous component grid draws.
		quad[0].texCoords = quad[1].texCoords = quad[2].texCoords = quad[3].texCoords = sf::Vector2f(0, 0);
	}
}

ComponentGrid &ComponentGridGui::fetchCurrentGrid() {
	return turnManager.getCurrentEntity()->getComponentGrid();
}