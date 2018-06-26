#include "Animation.h"

Animation::Animation(sf::Time frameTime, std::vector<Frame> animationFrames) : timeBetweenFrames(frameTime), frames(animationFrames) {}

const Animation::Frame &Animation::getFrameFromIndex(int index) {
	return frames.at(index);
}

const Animation::Frame &Animation::getFrame(sf::Time atTime) {
	auto frameNum = static_cast<unsigned int>(std::floor(atTime / timeBetweenFrames));

	return getFrameFromIndex(frameNum % frames.size());
}