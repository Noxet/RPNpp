module;

#include <format>
#include <memory>
#include <unordered_map>

export module RPNpp.utilities:Publisher;

import :Observer;
import :Exception;

using std::string;
using std::unique_ptr;
using std::unordered_map;


//class Observer;

namespace RPNpp
{
	class Publisher
	{
		using ObserverList = unordered_map<string, unique_ptr<Observer>>;
		using Events = unordered_map<string, ObserverList>;

	public:
		void attach(const string &eventName, unique_ptr<Observer> observer);
		unique_ptr<Observer> detach(const string &eventName, const string &observerName);

	private:
		Events::const_iterator findCheckedEvent(const string &eventName) const;

		Events m_events;
	};

	void Publisher::attach(const string &eventName, unique_ptr<Observer> observer) {}
	unique_ptr<Observer> Publisher::detach(const string &eventName, const string &observerName) {}


	Publisher::Events::const_iterator Publisher::findCheckedEvent(const string &eventName) const
	{
		auto ev = m_events.find(eventName);
		if (ev == m_events.end())
		{
			throw Exception(std::format("Publisher does not support event '{}'", eventName));
		}

		return ev;
	}
}
