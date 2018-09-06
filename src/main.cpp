#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include "states/StateManager.h"
#include "states/GameState.h"
#include "states/MainMenuState.h"
#include "Input.h"
#include "GameSettings.h"
#include "debugging.h"

/**
 * \mainpage Greenscale
 * \htmlonly
 * <p>Please see <a href="classes.html">Classes</a> and <a href="namespaces.html">Namespaces</a> for the project's documentation.</p>
 * <p>Visit the <a href="http://github.com/WiredSound/GreenScale">Greenscale GitHub page</a> should you wish to browse the codebase or contribute.</p>
 * \endhtmlonly
 */

int main() {
	GameSettings settings;
	settings.loadSettings("options.json");

	sf::RenderWindow window(sf::VideoMode(settings.windowWidth, settings.windowHeight),
		"Greenscale",
		settings.fullscreenEnabled ? (sf::Style::Fullscreen) : (sf::Style::Titlebar | sf::Style::Close/* | sf::Style::Resize*/));

	window.setVerticalSyncEnabled(settings.vsyncEnabled);

	sf::Font font;
	if (!font.loadFromFile("assets/fonts/aurulent-sans-mono/AurulentSansMono-Regular.otf")) {
		DEBUG_LOG_ERROR("Failed to load font!");
		return -1;
	}

	// FPS is measured by increasing fpsCounter every frame and then taking the value after one second has passed.
	int fpsCounter = 0;
	sf::Clock clock;

	Input input(window);

	StateManager manager;
	manager.changeState(std::make_unique<MainMenuState>(manager, window, font, settings));

	while (window.isOpen()) {
		if (input.update()) // Handle close window event.
			window.close();
		else
			manager.update(input); // Send input to the current state.

		window.clear(sf::Color::Black);
		manager.draw(); // Allow the current state to draw to the window.
		window.display();

		fpsCounter++;
		if (clock.getElapsedTime() > sf::milliseconds(1000)) {
			// TODO: Display FPS.

			clock.restart();
			fpsCounter = 0;
		}
	}

	return 0;
}