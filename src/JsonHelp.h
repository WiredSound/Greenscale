#include <nlohmann/json.hpp>
#include <SFML/Graphics/Color.hpp>

namespace JsonHelp {
	sf::Color parseColour(nlohmann::json colourJson);
}