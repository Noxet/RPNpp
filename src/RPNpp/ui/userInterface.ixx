module;

#include <string>
#include <string_view>

export module RPNpp.userInterfaces:UserInterface;

import RPNpp.utilities;

namespace RPNpp
{
	export class UserInterface
	{
	public:
		UserInterface() { uiEvent.registerEvent(commandEntered()); };
		virtual ~UserInterface() = default;

		Publisher uiEvent;

		/* event name when a command has been entered */
		static std::string commandEntered() { return "commandEntered"; }

		virtual void postMessage(std::string_view strView) = 0;
		virtual void stackChanged() = 0;

	protected:
		void notify(const std::string &cmd) const { uiEvent.notify(commandEntered(), cmd); };
	};
}
