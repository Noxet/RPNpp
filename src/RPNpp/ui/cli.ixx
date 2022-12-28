module;

#include <string_view>

export module RPNpp.userInterfaces:CLI;

import :UserInterface;

namespace RPNpp
{
	export class CLI : public UserInterface
	{
	public:
		void postMessage(std::string_view strView) override;
		void stackChanged() override;
	};
}
