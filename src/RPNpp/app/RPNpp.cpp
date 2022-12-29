#include <iostream>

import RPNpp.stack;
import RPNpp.utilities;
import RPNpp.command;
import RPNpp.commandDispatcher;
import RPNpp.userInterfaces;

using namespace RPNpp;
using std::string;
using std::cout;
using std::endl;


int main()
{
	registerCoreCommands();

	try
	{
		auto &cf = CommandFactory::Instance();
		CLI ui{ std::cin, std::cout };

		// attach Command Interpreter to UI events
		ui.uiEvent.attach(UserInterface::commandEntered(), std::move(std::make_unique<CommandInterpreter>(ui)));

		// attach UI to stack events
		Stack::Instance().stackEvent.attach(Stack::stackChanged(), std::make_unique<UIObserver>(ui));

		ui.run();
	}
	catch (Exception &e)
	{
		cout << e.what() << endl;
	}
}
