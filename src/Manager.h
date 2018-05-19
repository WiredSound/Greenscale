#pragma once

#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include "debugging.h"

template<typename Key, typename Managed>
class Manager {
protected:
	const std::string managedName;
	std::map<Key, const Managed> map;

	virtual std::pair<Key, const Managed> parseJson(nlohmann::json json) = 0;

public:
	Manager(std::string name) : managedName(name) {}

	bool loadFromJsonFile(std::string filename) {
		nlohmann::json json;
		std::ifstream file(filename);

		if (file.is_open()) {
			try {
				file >> json;

				for (nlohmann::json managedJson : json) {
					auto managed = parseJson(managedJson);

					map.insert(managed);
				}

				file.close();

				return true; // Success.
			}
			catch (nlohmann::json::type_error &e) {
				DEBUG_LOG_ERROR("Failed to load " << managedName << " due to type error: " << e.what() << "\nException ID: " << e.id);
			}
			catch (nlohmann::json::parse_error &e) {
				DEBUG_LOG_ERROR("Failed to load " << managedName << " due to parse error: " << e.what() << "\nException ID: " << e.id << "\nAt byte: " << e.byte);
			}
		}

		return false;
	}

	const Managed &get(Key key) {
		return map[key];
	}
};