#include "Console.h"

Console::MessageType::MessageType(std::string typeName, sf::Color typeColour) : name(typeName), colour(typeColour) {}

const Console::MessageType Console::MessageType::INFO("INFO", sf::Color(0, 255, 0, 255));
const Console::MessageType Console::MessageType::INFO_NONESSENTIAL("NONESSENTIAL INFO", sf::Color(0, 255, 0, 160));
const Console::MessageType Console::MessageType::WARNING("WARNING", sf::Color(255, 255, 0, 255));
const Console::MessageType Console::MessageType::FATAL("FATAL", sf::Color(255, 0, 0, 255));
const Console::MessageType Console::MessageType::SPEECH("SPEECH", sf::Color(0, 0, 255, 255));

void Console::setConsoleGui(ConsoleGui *guiPtr) {
	gui = guiPtr;
}

void Console::display(Message msg, bool guiPrependMsgType) {
	std::string msgTextWithType = "(" + msg.type.name + ") " + msg.text;

	if (gui != nullptr) {
		// Display via the GUI:
		gui->display((guiPrependMsgType ? msgTextWithType : msg.text), msg.type.colour);
	}
	else {
		// Display via standard console output:
		std::cout << msgTextWithType << std::endl;
	}
}