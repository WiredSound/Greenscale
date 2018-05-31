#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.h"
#include "GameState.h"
#include "Input.h"
#include "GameSettings.h"
#include "debugging.h"
#include <FastNoise.h>

int main() {
	FastNoise noise;

	GameSettings settings;
	settings.loadSettings("options.json");

	sf::RenderWindow window(sf::VideoMode(settings.windowWidth, settings.windowHeight),
		"Greenscale",
		settings.fullscreenEnabled ? (sf::Style::Fullscreen) : (sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize));

	window.setVerticalSyncEnabled(settings.vsyncEnabled);
	//window.setView(sf::View(sf::FloatRect(0, 0, settings.windowWidth, settings.windowHeight)));

	sf::Font font;
	if (!font.loadFromFile("assets/fonts/joystix monospace.ttf")) {
		DEBUG_LOG_ERROR("Failed to load font!");
		return -1;
	}

	int fpsCounter = 0;
	sf::Clock clock;

	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setFillColor(sf::Color::Yellow);
	fpsText.setCharacterSize(18);

	auto state = std::make_unique<GameState>(window, font); // Create the game state.
	Input input(window);

	while (window.isOpen()) {
		bool closeWindow = input.update();

		if (closeWindow) // Handle close window event.
			window.close();
		else
			state->update(input); // Send input to the current state.

		window.clear(sf::Color::Black);

		state->draw(); // Allow the current state to draw to the window.

		fpsCounter++;
		if (clock.getElapsedTime() > sf::milliseconds(500)) {
			int fps = fpsCounter * 2;
			DEBUG_LOG_SPAM("FPS: " << fps);

			if (settings.displayFps) {
				fpsText.setString("FPS: " + std::to_string(fps));
				fpsText.setPosition(settings.windowWidth - fpsText.getLocalBounds().width, 0);
			}

			clock.restart();
			fpsCounter = 0;
		}

		window.draw(fpsText);

		window.display();
	}

	return 0;
}

GameSettings loadSettings(std::string filename) {
	GameSettings settings;
	nlohmann::json json;
	std::ifstream file(filename);

	if (file.is_open()) {
		try {
			file >> json;

			settings.windowWidth = json["window width"].get<unsigned int>();
			settings.windowHeight = json["window height"].get<unsigned int>();
			settings.vsyncEnabled = json["vsync enabled"].get<bool>();
			settings.fullscreenEnabled = json["fullscreen enabled"].get<bool>();
			settings.fullscreenEnabled = json["display fps"].get<bool>();

			file.close();
		}
		catch (nlohmann::json::type_error &e) {
			DEBUG_LOG_ERROR("Failed to load settings file due to type error: " << e.what() << "\nException ID: " << e.id);
		}
		catch (nlohmann::json::parse_error &e) {
			DEBUG_LOG_ERROR("Failed to load settings file due to parse error: " << e.what() << "\nException ID: " << e.id << "\nAt byte: " << e.byte);
		}
	}

	return settings;
}