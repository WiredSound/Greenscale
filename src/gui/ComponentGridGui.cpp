#include "gui/ComponentGridGui.h"

ComponentGridGui::ComponentGridGui(Gui &parent, TurnManager &manager, std::shared_ptr<sf::Texture> texture, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness)
	: GuiWindow("Component Grid", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	turnManager(manager), componentsTexture(texture),
	padding(0.05f, 0.05f), componentBoxColour(75, 75, 75, 255), componentBoxHoverColour(60, 60, 60, 255), componentBoxUnequippedBorderColour(borderColour), componentBoxEquippedBorderColour(sf::Color::Blue)
{
	vertices.setPrimitiveType(sf::Quads);
}

void ComponentGridGui::update(Input &input) {
	GuiWindow::update(input);

	ComponentGrid &currentGrid = fetchCurrentGrid();

	if (previousComponentGrid != &currentGrid) { // Check if the grid being displayed has changed.
		setup(currentGrid);
		previousComponentGrid = &currentGrid;
		mouseHoldingComponent = false;
	}

	for (unsigned int x = 0; x < currentGrid.getGridSize().x; x++) {
		for (unsigned int y = 0; y < currentGrid.getGridSize().y; y++) {
			sf::Vector2u position(x, y);

			setupComponentQuad(position, currentGrid, input);
		}
	}
}

void ComponentGridGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiWindow::draw(target, states);

	states.texture = componentsTexture.get();
	target.draw(vertices, states);
}

unsigned int ComponentGridGui::getGridIndex(sf::Vector2u pos, const ComponentGrid &grid) {
	return pos.y * grid.getGridSize().x + pos.x;
}

Optional<Component> &ComponentGridGui::getComponentHoveredOver() {
	return fetchCurrentGrid().getComponentAt(hoverGridPosition);
}

Optional<Component> &ComponentGridGui::getHeldComponent() {
	if (mouseHoldingComponent)
		return fetchCurrentGrid().getComponentAt(mouseHeldGridPosition);

	//return Optional<Component>();
}

void ComponentGridGui::hoveringOverGridPosition(sf::Vector2u gridPosition) {
	// Put in checks to ensure this is pointing to a valid grid position?
	hoverGridPosition = gridPosition;
}

void ComponentGridGui::equipGridPosition(sf::Vector2u gridPosition) {
	auto &grid = fetchCurrentGrid();

	// Handle the changes to the GUI:
	if (grid.isComponentEquipped())
		getGridBox(grid.getEquippedComponentGridPosition(), grid)->unequip();
	getGridBox(gridPosition, grid)->equip();

	// Equip and enable specified gird position:
	grid.equipComponent(gridPosition);
	grid.getComponentAt(gridPosition)->setManualEnable(true);
}

void ComponentGridGui::toggleEnableGridPosition(sf::Vector2u gridPosition) {
	fetchCurrentGrid().getComponentAt(gridPosition)->toggleManualEnable();
}

void ComponentGridGui::mouseToggleHolding(sf::Vector2u gridPosition) {
	if (mouseHoldingComponent)
		mousePutDownHeldPosition(gridPosition);
	else
		mousePickupPosition(gridPosition);
}

void ComponentGridGui::mousePickupPosition(sf::Vector2u gridPosition) {
	if (fetchCurrentGrid().getComponentAt(gridPosition)) { // Only hold the grid position if there actually is a component there.
		mouseHeldGridPosition = gridPosition;
		mouseHoldingComponent = true;
	}
}

void ComponentGridGui::mousePutDownHeldPosition() {
	mouseHoldingComponent = false;
}

void ComponentGridGui::mousePutDownHeldPosition(sf::Vector2u newPosition) {
	if (mouseHoldingComponent) {
		fetchCurrentGrid().swapPositions(mouseHeldGridPosition, newPosition);
		mouseHoldingComponent = false;
	}
}

/**
 * Handles the resizing of the sf::VertexArray as well as the creation and positioning of the child ComponentGridGuiBox instances.
 * \param grid The component grid to setup the GUI for.
 */
void ComponentGridGui::setup(ComponentGrid &grid) {
	const sf::Vector2u &gridSize = grid.getGridSize();

	vertices.resize(gridSize.x * gridSize.y * 4);

	destroyAllChildren();

	boxSize = sf::Vector2f((1.0f - padding.x) / gridSize.x - padding.x, (1.0f - padding.y) / gridSize.y - padding.y);

	for (unsigned int y = 0; y < gridSize.y; y++) {
		for (unsigned int x = 0; x < gridSize.x; x++) {
			sf::Vector2u gridPos(x, y);

			addChild(std::make_unique<ComponentGridGuiBox>(*this, gridPos,
				sf::Vector2f(padding.x + (padding.x + boxSize.x) * x,
					padding.y + (padding.y + boxSize.y) * y), boxSize,
				componentBoxColour, componentBoxHoverColour, componentBoxEquippedBorderColour, componentBoxUnequippedBorderColour, 1.0f));

			if (grid.getEquippedComponentGridPosition() == gridPos && grid.isComponentEquipped())
				getGridBox(gridPos, grid)->equip();
		}
	}
}

/**
 * Sets up the icon for the component at the specified position within the given component grid.
 * The Input reference is required so that, should there be a component held by the mouse, it can be drawn at the mouse's position.
 */
void ComponentGridGui::setupComponentQuad(sf::Vector2u pos, ComponentGrid &grid, Input &input) {
	auto &component = grid.getComponentAt(pos);

	int index = getGridIndex(pos, grid);
	sf::Vertex *quad = &vertices[index * 4];

	if (component) {
		const ComponentInfo &info = component->fetchInfo();
		sf::Vector2f componentTextureSize = component->getIconTextureSize();

		auto &child = getChild(index);

		sf::Vector2f quadSize = child->getAbsoluteSize();

		sf::Vector2f drawPosForHeldComponent(input.getMousePosition().x - (quadSize.x / 2), input.getMousePosition().y - (quadSize.y / 2));
		// If the component is the one held by the mouse then draw it at the mouse coordinates instead of in the grid:
		sf::Vector2f quadPosition = (mouseHoldingComponent && pos == mouseHeldGridPosition) ? drawPosForHeldComponent : child->getAbsolutePosition();

		quad[0].position = quadPosition;
		quad[1].position = sf::Vector2f(quadPosition.x + quadSize.x, quadPosition.y);
		quad[2].position = sf::Vector2f(quadPosition.x + quadSize.x, quadPosition.y + quadSize.y);
		quad[3].position = sf::Vector2f(quadPosition.x, quadPosition.y + quadSize.y);

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

/**
 * Fetches a reference to the ComponentGrid of the Entity who's turn it currently is (as determined by the TurnManager).
 */
ComponentGrid &ComponentGridGui::fetchCurrentGrid() {
	return turnManager.getCurrentEntity()->getComponentGrid();
}

ComponentGridGuiBox *ComponentGridGui::getGridBox(sf::Vector2u pos, ComponentGrid &grid) {
	return getChild<ComponentGridGuiBox>(getGridIndex(pos, grid));
}
