#pragma once

#include <string>
#include <map>
#include <memory>
#include "../Animation.h"
#include "../IDs.h"

struct EntityInfo {
	IDs::Entities id;
	std::string name;
	std::string description;
	std::string type;
	std::map<const std::string, std::shared_ptr<Animation>> animations;
};