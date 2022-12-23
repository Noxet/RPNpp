module;

#include <memory>
#include <string>
#include <unordered_map>

export module RPNpp.commandDispatcher:commandFactory;

import RPNpp.command;

using std::unique_ptr;
using std::string;
using std::unordered_map;

namespace RPNpp
{
	export class CommandFactory
	{
	public:
		static CommandFactory& Instance();
		unique_ptr<Command> createCommand(const string &s) const;
		void registerCommand(const string &s, unique_ptr<Command> cmd);


		CommandFactory(const CommandFactory &) = delete;
		CommandFactory &operator=(CommandFactory &) = delete;
		CommandFactory(const CommandFactory &&) = delete;
		CommandFactory &operator=(CommandFactory &&) = delete;

	private:
		CommandFactory() = default;
		~CommandFactory() = default;

		using Factory = unordered_map<string, unique_ptr<Command>>;
		Factory m_factory;
	};


	CommandFactory& CommandFactory::Instance()
	{
		static CommandFactory instance;
		return instance;
	}


	unique_ptr<Command> CommandFactory::createCommand(const std::string &s) const
	{
		if (m_factory.contains(s))
		{
			const auto &cmd = m_factory.find(s)->second;
			return unique_ptr<Command>(cmd->clone());
		}

		return nullptr;
	}


	void CommandFactory::registerCommand(const string &s, unique_ptr<Command> cmd)
	{
		if (m_factory.contains(s))
		{
			// duplicate
		}
		else
		{
			m_factory.emplace(s, std::move(cmd));
		}
	}

	/**
	 * Global function to register all basic core commands.
	 * This is not a member function to avoid coupling between the factory
	 * and all the commands.
	 */
	export void registerCoreCommands()
	{
		// TODO: How to override checkPreconditionsImpl?
		auto &cmdf = CommandFactory::Instance();

		cmdf.registerCommand("+", std::make_unique<BinaryCommand>([](const double a, const double b) {return a + b; }));
		cmdf.registerCommand("-", std::make_unique<BinaryCommand>([](const double a, const double b) {return a - b; }));
		cmdf.registerCommand("*", std::make_unique<BinaryCommand>([](const double a, const double b) {return a * b; }));
		cmdf.registerCommand("/", std::make_unique<BinaryCommand>([](const double a, const double b) {return a / b; }));
	}
}
