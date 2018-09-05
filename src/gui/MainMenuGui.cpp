#include "MainMenuGui.h"

#include "GuiButton.h"

MainMenuGui::MainMenuGui(sf::Vector2f size) : RootGui("Main Menu", sf::Vector2f(0, 0), size) {}

void MainMenuGui::setup(sf::Font &font, unsigned int fontSize) {
	destroyAllChildren();

	auto testButton = std::make_unique<GuiButton>("Test", *this, sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.25f, 0.25f), sf::Vector2f(0.5f, 0.5f),
		sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, 3.0f);

	addChild(std::move(testButton));
	//addChild(std::make_unique<GuiWindow>("", *this, sf::Vector2f(0.01f, 0.01f), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0, 0), sf::Color::Blue, sf::Color::Blue, sf::Color::Blue, 1.0f));
}