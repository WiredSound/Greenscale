#include "Gui.h"

Gui::Gui(std::string guiName) : name(guiName) {}

void Gui::update(Input &input) {
	updateChildren(input);

	sf::Vector2i pos = input.getMousePosition();

	mouseOverChildren = false;

	for (std::unique_ptr<Gui> &child : children) {
		if (child->withinBounds((sf::Vector2f) input.getMousePosition())) {
			mouseOverChild(child, input);
		}
		else child->mouseNotHovering(input.getMousePosition());
	}
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	drawChildren(target, states);
}

void Gui::mouseOverChild(std::unique_ptr<Gui> &child, Input &input) {
	child->mouseHover(input.getMousePosition(), input.getMouseButtonsJustPressed());
	mouseOverChildren = true;
}

bool Gui::isMouseOverChildren() {
	return mouseOverChildren;
}

void Gui::updateChildren(Input &input) {
	for (std::unique_ptr<Gui> &child : children) {
		child->update(input);
	}
}

void Gui::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const std::unique_ptr<Gui> &child : children) {
		child->draw(target, states);
	}
}

void Gui::destroyAllChildren() { // RIP...
	children.clear();
}

std::unique_ptr<Gui> &Gui::getChild(int index) {
	return children[index];
}

int Gui::addChild(std::unique_ptr<Gui> child) {
	children.push_back(std::move(child));
	return children.size() - 1;
}

void Gui::removeChild(std::unique_ptr<Gui> child) {
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

bool Gui::withinBounds(sf::Vector2f pos) {
	sf::Vector2f absPos = getAbsolutePosition();
	sf::Vector2f absSize = getAbsoluteSize();

	return pos.x >= absPos.x && pos.y >= absPos.y &&
		pos.x <= absPos.x + absSize.x && pos.y <= absPos.y + absSize.y;
}