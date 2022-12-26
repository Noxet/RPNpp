module;

#include <memory>
#include <string>

export module RPNpp.commandDispatcher:commandInterpreter;

namespace RPNpp
{
	export class CommandInterpreter
	{
		class CommandInterpreterImpl;
		class UserInterface;

	public:
		explicit CommandInterpreter(UserInterface &ui);
		void executeCommand(const std::string &command);

	private:
		std::unique_ptr<CommandInterpreterImpl> m_impl;
	};
}
