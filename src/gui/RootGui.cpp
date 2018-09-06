#include "RootGui.h"

RootGui::RootGui(std::string name, sf::Vector2f position, sf::Vector2f size) : Gui(name), absolutePosition(position), absoluteSize(size) {}

sf::Vector2f RootGui::getAbsolutePosition() const {
	return absolutePosition;
}

sf::Vector2f RootGui::getAbsoluteSize() const {
	return absoluteSize;
}

float RootGui::getAspectRatio() {
	return absoluteSize.x / absoluteSize.y;
}

void RootGui::resize(sf::Vector2f size) {
	absoluteSize = size;
}