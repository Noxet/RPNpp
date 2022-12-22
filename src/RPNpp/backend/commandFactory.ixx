module;

#include <memory>
#include <string>
#include <unordered_map>

export module RPNpp.commandFactory;

import RPNpp.command;

using std::unique_ptr;
using std::string;
using std::unordered_map;

namespace RPNpp
{
	export class CommandFactory
	{
	public:
		unique_ptr<Command> createCommand(const string &s) const;
		void registerCommand(const string &s, unique_ptr<Command> cmd);

	private:
		using Factory = unordered_map<string, unique_ptr<Command>>;
		Factory m_factory;
	};


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
}
