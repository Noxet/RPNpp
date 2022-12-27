module;

#include <string_view>

export module userInterface;

import RPNpp.utilities;

namespace RPNpp
{
	export class UserInterface
	{
	public:
		UserInterface();
		virtual ~UserInterface();

		Publisher uiEvent;

		virtual void postMessage(std::string_view strView) = 0;
		virtual void stackChanged() = 0;
	};
}
