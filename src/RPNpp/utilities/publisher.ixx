module;

#include <any>
#include <format>
#include <memory>
#include <ranges>
#include <unordered_map>

export module RPNpp.utilities:Publisher;

import :Observer;
import :Exception;

using std::string;
using std::unique_ptr;
using std::unordered_map;


namespace RPNpp
{
	class Publisher
	{
		using ObserverList = unordered_map<string, unique_ptr<Observer>>;
		using Events = unordered_map<string, ObserverList>;

	public:
		void attach(const string &eventName, unique_ptr<Observer> observer);
		unique_ptr<Observer> detach(const string &eventName, const string &observerName);
		void notify(const string &eventName, std::any d) const;

	private:
		Events::const_iterator findCheckedEvent(const string &eventName) const;
		Events::iterator findCheckedEvent(const string &eventName);

		Events m_events;
	};


	void Publisher::attach(const string &eventName, unique_ptr<Observer> observer)
	{
		auto &observerList = findCheckedEvent(eventName)->second;
		if (observerList.contains(observer->name()))
		{
			throw Exception("Observer already attached to publisher");
		}
		
		observerList.insert({ observer->name(), std::move(observer) });
	}


	unique_ptr<Observer> Publisher::detach(const string &eventName, const string &observerName)
	{
		auto &observerList = findCheckedEvent(eventName)->second;
		if (observerList.contains(observerName))
		{
			auto observer = std::move(observerList.at(observerName));
			observerList.erase(observerName);
			return observer;
		}

		throw Exception("Observer not found");
	}


	void Publisher::notify(const string &eventName, const std::any data) const
	{
		auto &observerList = findCheckedEvent(eventName)->second;
		for (const auto &observer : std::views::values(observerList))
		{
			observer->onEvent(data);
		}
	}


	Publisher::Events::const_iterator Publisher::findCheckedEvent(const string &eventName) const
	{
		auto ev = m_events.find(eventName);
		if (ev == m_events.end())
		{
			throw Exception(std::format("Publisher does not support event '{}'", eventName));
		}

		return ev;
	}


	Publisher::Events::iterator Publisher::findCheckedEvent(const string &eventName)
	{
		auto ev = m_events.find(eventName);
		if (ev == m_events.end())
		{
			throw Exception(std::format("Publisher does not support event '{}'", eventName));
		}

		return ev;
	}
}
