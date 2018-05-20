#include "debugging.h"

#include <iomanip>
#include <time.h>

std::string Debug::getTimestamp() {
	struct tm newtime;
	time_t now = time(nullptr);
	localtime_s(&newtime, &now);

	std::ostringstream oss;
	oss << std::put_time(&newtime, "%H:%M:%S");

	return oss.str();
}