module;

#include <any>
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


	/**
	 * Class to act as an observer proxy for the UI
	 */
	export class UIObserver : public Observer
	{
	public:
		explicit UIObserver(UserInterface &ui) : Observer("UIObserver"), m_ui{ ui } {}

		void onEvent(const std::any &data) override { m_ui.stackChanged(); }

	private:
		UserInterface &m_ui;
	};
}
