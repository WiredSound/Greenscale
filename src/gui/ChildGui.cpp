#include "ChildGui.h"

ChildGui::ChildGui(std::string name, Gui &guiParent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f guiOrigin) : Gui(name),
positionFromParent(position), sizeFromParent(size), origin(guiOrigin), parent(guiParent) {}

sf::Vector2f ChildGui::getAbsolutePosition() {
	return sf::Vector2f(
		parent.getAbsolutePosition().x + (parent.getAbsoluteSize().x * positionFromParent.x) - (getAbsoluteSize().x * origin.x),
		parent.getAbsolutePosition().y + (parent.getAbsoluteSize().y * positionFromParent.y) - (getAbsoluteSize().y * origin.y)
	);
}

sf::Vector2f ChildGui::getAbsoluteSize() {
	return sf::Vector2f(parent.getAbsoluteSize().x * sizeFromParent.x, parent.getAbsoluteSize().y * sizeFromParent.y);
}

sf::Vector2f ChildGui::absoluteSizeToRelative(sf::Vector2f absoluteSize) {
	return sf::Vector2f(absoluteSize.x / parent.getAbsoluteSize().x, absoluteSize.y / parent.getAbsoluteSize().y);
}