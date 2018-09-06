#include "ChildGui.h"

ChildGui::ChildGui(std::string name, Gui &guiParent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f guiOrigin) : Gui(name),
positionFromParent(position), sizeFromParent(size), origin(guiOrigin), parent(guiParent) {}

/**
 * The position of a ChildGui element is calculated based on the absolute position of the parent Gui element multiplied by the `positionFromParent` field.
 * \return The absolute position of this element.
 */
sf::Vector2f ChildGui::getAbsolutePosition() const {
	return sf::Vector2f(
		parent.getAbsolutePosition().x + (parent.getAbsoluteSize().x * positionFromParent.x) - (getAbsoluteSize().x * origin.x),
		parent.getAbsolutePosition().y + (parent.getAbsoluteSize().y * positionFromParent.y) - (getAbsoluteSize().y * origin.y)
	);
}

/**
 * The size of a ChildGui element is expressed as a fraction of the absolute size of the parent Gui element.
 * \return The absolute size of this element.
 */
sf::Vector2f ChildGui::getAbsoluteSize() const {
	return sf::Vector2f(parent.getAbsoluteSize().x * sizeFromParent.x, parent.getAbsoluteSize().y * sizeFromParent.y);
}

sf::Vector2f ChildGui::absoluteSizeToRelative(sf::Vector2f absoluteSize) {
	return sf::Vector2f(absoluteSize.x / parent.getAbsoluteSize().x, absoluteSize.y / parent.getAbsoluteSize().y);
}