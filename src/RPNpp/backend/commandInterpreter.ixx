module;

#include <any>
#include <memory>
#include <string>

export module RPNpp.commandDispatcher:commandInterpreter;

import RPNpp.userInterfaces;
import RPNpp.utilities;

namespace RPNpp
{
	export class CommandInterpreter : public Observer
	{
		class CommandInterpreterImpl;

	public:
		explicit CommandInterpreter(UserInterface &ui);
		~CommandInterpreter() override;

		void executeCommand(const std::string &command);

		void onEvent(const ::std::any &data) override;

	private:
		std::unique_ptr<CommandInterpreterImpl> m_impl;
	};
}
