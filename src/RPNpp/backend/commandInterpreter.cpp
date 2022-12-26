module;

#include <regex>
#include <string>

module RPNpp.commandDispatcher:commandInterpreter;

import RPNpp.command;
import RPNpp.stack;
import :commandManager;
import :commandFactory;


namespace RPNpp
{
	class CommandInterpreter::CommandInterpreterImpl
	{
		class UserInterface;

	public:
		explicit CommandInterpreterImpl(UserInterface &ui);
		void executeCommand(const std::string &command);

	private:
		bool isNum(const std::string &str);

		CommandManager m_commandManager;
		UserInterface &m_ui;
	};


	bool CommandInterpreter::CommandInterpreterImpl::isNum(const std::string &str)
	{
		const std::regex numExpr("^[-]*\\d+[\\.]*\\d+$");
		return std::regex_match(str, numExpr);
	}


	CommandInterpreter::CommandInterpreterImpl::CommandInterpreterImpl(UserInterface &ui) : m_ui{ ui } {}


	void CommandInterpreter::CommandInterpreterImpl::executeCommand(const std::string &command)
	{
		if (isNum(command))
		{
			Stack::Instance().push(std::stod(command));
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
}
