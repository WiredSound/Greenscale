#pragma once

#include <iostream>
#include "gui/ConsoleGui.h"

/**
 * Allows for messages to be displayed to the console.
 */
class Console {
public:
	/**
	 * Each of the message types have a name as well as a colour (and will likely have some sort of priority in the future).
	 */
	class MessageType {
	public:
		std::string name;
		sf::Color colour;

		static const MessageType INFO;
		static const MessageType INFO_NONESSENTIAL;
		static const MessageType WARNING;
		static const MessageType WARNING_NONESSENTIAL;
        static const MessageType FATAL;
		static const MessageType SPEECH;

	private:
		MessageType(std::string typeName, sf::Color typeColour);
	};

	struct Message {
		std::string text;
		MessageType type;
	};

	void setConsoleGui(ConsoleGui *guiPtr);
	void display(Message msg, bool guiPrependMsgType = false);

private:
	ConsoleGui *gui;
};
