#pragma once

#include <string>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>
#include "debugging.h"

/**
 * Manager is a class template that is designed to make the loading of tiles, projectiles, entities, components and component upgrades from JSON files easier.
 * \tparam Key The key that points to a managed item. Typically an enum stored in the IDs namespace.
 * \tparam Managed An object/struct storing all the data relevant to what is being managed.
 */
template<typename Key, typename Managed>
class Manager {
protected:
	const std::string managedName;
	const std::string managedKey;
	std::map<Key, const Managed> map;

	/**
	 * This method is where all information stored in the root of the JSON object can be parsed.
	 * \param json The root JSON object.
	 */
	virtual void parseJson(nlohmann::json json) = 0;
	/**
	 * Where all managed objects can be created from the JSON object.
	 * \param json The JSON object representing the managed item.
	 * \return A `std::pair` of the key and its associated managed object.
	 */
	virtual std::pair<Key, const Managed> parseJsonManaged(nlohmann::json json) = 0;

public:
	Manager(std::string name, std::string keyManaged) : managedName(name), managedKey(keyManaged) {}

	/**
	 * Loads all the relevant information from the specified JSON file.
	 * \param filename The path to the JSON file.
	 * \return Returns `true` if the JSON file was successfully read and parsed.
	 */
	bool loadFromJsonFile(std::string filename) {
		nlohmann::json json;
		std::ifstream file(filename);

		if (file.is_open()) {
			try {
				file >> json;

				parseJson(json); // Parse any root values in the json file (such as tile width and height).

				for (nlohmann::json managedJson : json[managedKey]) {
					auto managed = parseJsonManaged(managedJson); // Parse the list of managed items.

					DEBUG_LOG("Loaded " << managedName << " with ID: " << managed.first);

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