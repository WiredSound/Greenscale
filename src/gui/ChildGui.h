#pragma once

#include "../debugging.h"
#include "Gui.h"

class ChildGui : public Gui {
public:
	ChildGui(std::string name, Gui &guiParent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f guiOrigin);

	virtual sf::Vector2f getAbsolutePosition() override;
	virtual sf::Vector2f getAbsoluteSize() override;

protected:
	// The position and size of the element is determined as the size of the parent multiplied by the below.
	// For example, with a parent 1000x1000, an element at positionFromParent (0.25, 0.5) would be positioned
	// at (250, 500).
	sf::Vector2f positionFromParent;
	sf::Vector2f sizeFromParent;

	// The origin of the gui relative it its size.
	sf::Vector2f origin;

	Gui &parent;
};