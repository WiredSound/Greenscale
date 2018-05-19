#include "Animation.h"

Animation::Animation(sf::Time frameTime, std::vector<Frame> animationFrames) : timeBetweenFrames(frameTime), frames(animationFrames) {
	DEBUG_LOG("Created animation with " << animationFrames.size() << " frames and " << frameTime.asMilliseconds() << "ms between each frame.");
}

const Animation::Frame &Animation::getFrameFromIndex(int index) {
	return frames.at(index);
}

const Animation::Frame &Animation::getFrame(sf::Time atTime) {
	int frameNum = (int) std::floor(atTime / timeBetweenFrames);
	
	return getFrameFromIndex(frameNum % frames.size());
}