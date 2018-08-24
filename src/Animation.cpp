#include "Animation.h"

Animation::Animation(sf::Time frameTime, std::vector<Frame> animationFrames) : timeBetweenFrames(frameTime), frames(animationFrames) {}

/**
 * Fetch a frame from the animation based on its index.
 * \param index The index of the desired frame.
 * \return The animation frame.
 */
const Animation::Frame &Animation::getFrameFromIndex(unsigned int index) {
	return frames.at(index);
}

/**
 * Fetches the correct frame based on the point in time specified.
 * \param atTime The point in time.
 * \return The animation frame.
 */
const Animation::Frame &Animation::getFrame(sf::Time atTime) {
	auto frameNum = static_cast<unsigned int>(std::floor(atTime / timeBetweenFrames));

	return getFrameFromIndex(frameNum % frames.size());
}