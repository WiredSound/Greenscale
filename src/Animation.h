#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include "debugging.h"

/**
 * The Animation class handles all the frames that make up an animation.
 * The nested Animation::Frame struct stores the coordinates of each frame as well as its colour (which is ignored should one not be specified). The public method ::getFrame allows the caller to fetch
 * what would be the appropriate frame at the time specified. By not having any timing take place in the Animation class itself, this means that an animation can be shared between multiple entities even
 * if each entity is at a different point in said animation.
 */
class Animation {
public:
	//! Stores the coordinates of a frame as well as its colour (which is ignored if set to the default value of sf::Color).
	struct Frame {
		unsigned int textureX;
		unsigned int textureY;
		sf::Color colour;
	};

	const sf::Time timeBetweenFrames;

	Animation(sf::Time frameTime, std::vector<Frame> animationFrames);
	const Frame &getFrameFromIndex(unsigned int index);
	const Frame &getFrame(sf::Time atTime);

private:
	std::vector<Frame> frames;
};