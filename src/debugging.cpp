#include "debugging.h"

#include <iomanip>
#include <ctime>

std::string Debug::getTimestamp() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%H:%M:%S");

	return oss.str();
}
