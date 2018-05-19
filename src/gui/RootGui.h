#pragma once

#include "Gui.h"

class RootGui : public Gui {
public:
	RootGui(std::string name, sf::Vector2f position, sf::Vector2f size);

	sf::Vector2f getAbsolutePosition() override;
	sf::Vector2f getAbsoluteSize() override;
	float getAspectRatio();
	void resize(sf::Vector2f size);

protected:
	sf::Vector2f absolutePosition;
	sf::Vector2f absoluteSize;
};