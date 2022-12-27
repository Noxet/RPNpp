module;

#include <memory>
#include <string>

export module RPNpp.commandDispatcher:commandInterpreter;

namespace RPNpp
{
	// TODO: remove this temp class
	export class UserInterface
	{
		
	};

	export class CommandInterpreter
	{
		class CommandInterpreterImpl;

	public:
		explicit CommandInterpreter(UserInterface &ui);
		~CommandInterpreter();
		void executeCommand(const std::string &command);

	private:
		std::unique_ptr<CommandInterpreterImpl> m_impl;
	};
}
