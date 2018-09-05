#include "MainMenuGui.h"

#include "GuiButton.h"

MainMenuGui::MainMenuGui(sf::Vector2f size) : RootGui("Main Menu", sf::Vector2f(0, 0), size) {}

void MainMenuGui::setup(sf::Font &font, unsigned int fontSize, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness) {
	destroyAllChildren();

	auto testButton = std::make_unique<GuiButton>("Test", *this, sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.25f, 0.25f), sf::Vector2f(0.5f, 0.5f),
		backgroundColour, hoverBackgroundColour, sf::Color::Blue, borderColour, 3.0f);

	addChild(std::move(testButton));
}