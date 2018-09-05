#pragma once

#include <iostream>
#include <sstream>

namespace Debug {
	std::string getTimestamp();
	// TODO: Log to file.
}

#define DEBUG_LOG_ERROR(msg) std::cerr << Debug::getTimestamp() << " (ERROR) - " << msg << std::endl;

#ifdef DEBUG
#define DEBUG_LOG(msg) std::cout << Debug::getTimestamp() << " - " << msg << std::endl;
#else
#define DEBUG_LOG(msg)
#endif

#ifdef DEBUG_SPAM
#define DEBUG_LOG_SPAM(msg)  std::cout << msg << "\n";
#else
#define DEBUG_LOG_SPAM(msg)
#endif