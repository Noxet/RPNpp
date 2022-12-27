module;

#include <string>
#include <memory>

module RPNpp.commandDispatcher:commandInterpreter;

import RPNpp.command;
import RPNpp.stack;
import RPNpp.utils;
import :commandManager;
import :commandFactory;


namespace RPNpp
{
	class CommandInterpreter::CommandInterpreterImpl
	{
		//class UserInterface;

	public:
		explicit CommandInterpreterImpl(UserInterface &ui);

		void executeCommand(const std::string &command);

	private:
		CommandManager m_commandManager;
		UserInterface &m_ui;
	};


	CommandInterpreter::CommandInterpreterImpl::CommandInterpreterImpl(UserInterface &ui) : m_ui{ ui } {}


	void CommandInterpreter::CommandInterpreterImpl::executeCommand(const std::string &command)
	{
		if (Utils::isNum(command))
		{
			m_commandManager.executeCommand(std::make_unique<EnterCommand>(std::stod(command)));
		}
		else if (command == "undo")
		{
			m_commandManager.undo();
		}
		else if (command == "redo")
		{
			m_commandManager.redo();
		}
		else
		{
			auto cmd = CommandFactory::Instance().createCommand(command);
			m_commandManager.executeCommand(std::move(cmd));
		}
	}


	CommandInterpreter::CommandInterpreter(UserInterface &ui) : m_impl{
		std::make_unique<CommandInterpreterImpl>(ui)
	} { }


	CommandInterpreter::~CommandInterpreter() { }


	void RPNpp::CommandInterpreter::executeCommand(const std::string &command)
	{
		m_impl->executeCommand(command);
	}
}
