#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include "debugging.h"

class Animation {
public:
	struct Frame {
		unsigned int textureX;
		unsigned int textureY;
		sf::Color colour;
	};
	
	const sf::Time timeBetweenFrames;

	Animation(sf::Time frameTime, std::vector<Frame> animationFrames);
	const Frame &getFrameFromIndex(int index);
	const Frame &getFrame(sf::Time atTime);

private:
	std::vector<Frame> frames;
};