#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

class TextLine : public sf::Drawable {
public:
	struct ColourText {
		std::string text;
		sf::Color colour;
	};

	TextLine(sf::Font &textFont, unsigned int size);
	TextLine(sf::Font &textFont, unsigned int size, ColourText text);
	void setPosition(sf::Vector2f basePosition);
	void add();
	void add(ColourText colourText);
	void set(unsigned int index, ColourText colourText);
	void clear();

	float getLineHeight();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	std::vector<sf::Text> texts;
	sf::Font &font;
	sf::Vector2f currentPosition;
	unsigned int fontSize;
};