#pragma once

#include <iostream>
#include "gui/ConsoleGui.h"

/*
 * The Console class is set up to display a Message (containing a string of text and a MessageType) using the ConsoleGui or, should no pointer to a ConsoleGui instance by provided,
 * to standard console output as a fallback.
 */

class Console {
public:
	class MessageType {
	public:
		std::string name;
		sf::Color colour;

		static const MessageType INFO;
		static const MessageType INFO_NONESSENTIAL;
		static const MessageType WARNING;
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