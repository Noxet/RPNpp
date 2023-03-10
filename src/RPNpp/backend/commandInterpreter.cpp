module;

#include <any>
#include <format>
#include <iostream>
#include <string>
#include <memory>

module RPNpp.commandDispatcher:commandInterpreter;

import RPNpp.command;
import RPNpp.stack;
import RPNpp.utils;
import RPNpp.utilities;
import RPNpp.userInterfaces;
import :commandManager;
import :commandFactory;


namespace RPNpp
{
	class CommandInterpreter::CommandInterpreterImpl
	{
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
			if (auto cmd = CommandFactory::Instance().createCommand(command))
			{
				try
				{
					m_commandManager.executeCommand(std::move(cmd));
				}
				catch (Exception e)
				{
					// TODO: post message to UI
				}
			}
			else
			{
				// TODO: post message to UI
			}
		}
	}


	CommandInterpreter::CommandInterpreter(UserInterface &ui) :
		Observer{ "commandInterpreter" },
		m_impl{ std::make_unique<CommandInterpreterImpl>(ui) } { }


	CommandInterpreter::~CommandInterpreter() { }


	void RPNpp::CommandInterpreter::handleCommand(const std::string &command)
	{
		m_impl->executeCommand(command);
	}


	void RPNpp::CommandInterpreter::onEvent(const std::any &data)
	{
		try
		{
			const auto &command = std::any_cast<std::string>(data);
			handleCommand(command);
		}
		catch (const std::bad_any_cast &e)
		{
			std::cout << std::format("[CommandInterpreter.onEvent] - {}", e.what()) << std::endl;
			// TODO: Let UI know about the error
		}
	}
}
