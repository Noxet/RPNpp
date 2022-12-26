module;

#include <memory>
#include <stack>

export module RPNpp.commandManager;

import RPNpp.command;

namespace RPNpp
{
	export class CommandManager
	{
	public:
		void executeCommand(std::unique_ptr<Command> cmd);
		void undo();
		void redo();

	private:
		std::deque<std::unique_ptr<Command>> m_undo;
		std::deque<std::unique_ptr<Command>> m_redo;
	};


	void CommandManager::executeCommand(std::unique_ptr<Command> cmd)
	{
		// we should not be able to redo after a new command has executed
		m_redo.clear();
		cmd->execute();
		m_undo.emplace_back(std::move(cmd));
	}


	void CommandManager::undo()
	{
		if (m_undo.size() == 0) return;

		auto &cmd = m_undo.back();
		cmd->undo();
		m_redo.push_back(std::move(cmd));
		m_undo.pop_back();
	}


	void CommandManager::redo()
	{
		if (m_redo.size() == 0) return;

		auto &cmd = m_redo.back();
		cmd->execute();
		m_undo.push_back(std::move(cmd));
		m_redo.pop_back();
	}
}
