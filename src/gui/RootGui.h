#pragma once

#include "Gui.h"

/**
 * The parent GUI element meant to represent the entire window/GUI area.
 */
class RootGui : public Gui {
public:
	RootGui(std::string name, sf::Vector2f position, sf::Vector2f size);

	sf::Vector2f getAbsolutePosition() const override;
	sf::Vector2f getAbsoluteSize() const override;
	float getAspectRatio();
	void resize(sf::Vector2f size);

protected:
	sf::Vector2f absolutePosition;
	sf::Vector2f absoluteSize;
};