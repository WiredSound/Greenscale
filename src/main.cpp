#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.h"
#include "GameState.h"
#include "Input.h"
#include "debugging.h"

// TODO: Load settings file instead of using these constants.

#define WINDOW_WIDTH 1728
#define WINDOW_HEIGHT 972

#define VSYNC_ENABLED false
#define FULLSCREEN_ENABLED false
#define DISPLAY_FPS true

#define CLEAR_COLOUR sf::Color(143, 143, 143, 255)

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Greenscale",
		FULLSCREEN_ENABLED ? (sf::Style::Fullscreen) : (sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize));

	window.setVerticalSyncEnabled(VSYNC_ENABLED);
	window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));

	sf::Font font;
	if (!font.loadFromFile("assets/fonts/joystix monospace.ttf")) {
		DEBUG_LOG_ERROR("Failed to load font!");
		return -1;
	}

#if DISPLAY_FPS
	int fpsCounter = 0;
	sf::Clock clock;

	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setFillColor(sf::Color::Yellow);
	fpsText.setCharacterSize(18);
#endif
	
	auto state = std::make_unique<GameState>(window, font); // Create the game state.
	Input input(window);

	while(window.isOpen()) {
		bool closeWindow = input.update();
		
		if (closeWindow) // Handle close window event.
			window.close();
		else
			state->update(input); // Send input to the current state.

		window.clear(CLEAR_COLOUR);

		state->draw(); // Allow the current state to draw to the window.

#if DISPLAY_FPS
		fpsCounter++;
		if (clock.getElapsedTime() > sf::milliseconds(500)) {
			int fps = fpsCounter * 2;
			DEBUG_LOG_SPAM("FPS: " << fps);

			fpsText.setString("FPS: " + std::to_string(fps));
			fpsText.setPosition(WINDOW_WIDTH - fpsText.getLocalBounds().width, 0);

			clock.restart();
			fpsCounter = 0;
		}

		window.draw(fpsText);
#endif

		window.display();
	}

	return 0;
}