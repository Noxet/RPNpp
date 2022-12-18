module;


#include <deque>
#include <vector>
#include <string>

export module RPNpp.stack;

import RPNpp.utilities;

using std::string;

namespace RPNpp
{
	/**
	 * @brief Class for managing stack errors
	*/
	export class StackErrorData
	{
	public:
		enum class ErrorCondition { Empty, TooFewArguments };

		StackErrorData(ErrorCondition e) : m_err{ e } {}

		ErrorCondition error() const { return m_err; }

	private:
		ErrorCondition m_err;
	};

	/*
	********** Stack **********
	*/

	export class Stack
	{
	public:
		static Stack& Instance();

		/*
		 * Stack events that may be subscribed to
		 */
		Publisher stackEvent;

		void push(double val);
		double pop();
		void getElements(int maxSize, std::vector<double> &elements) const;
		std::vector<double> getElements(int maxSize) const;
		void swapTop();
		void clear();

		static string stackChanged() { return "stackChanged"; }
		static string stackError() { return "stackError"; }

		/* Delete every other ctor, due to the singleton pattern */
		Stack(const Stack &) = delete;
		Stack& operator=(const Stack &) = delete;
		Stack(Stack &&) = delete;
		Stack&& operator=(Stack &&) = delete;

	private:
		Stack();
		~Stack() = default;

		std::deque<double> m_stack;
	};

	Stack& Stack::Instance()
	{
		static Stack stack;
		return stack;
	}


	void Stack::push(double val)
	{
		m_stack.push_back(val);
		stackEvent.notify(stackError(), nullptr);
	}


	double Stack::pop()
	{
		if (m_stack.empty())
		{
			stackEvent.notify(stackError(), StackErrorData{ StackErrorData::ErrorCondition::Empty });
			throw Exception("Empty stack");
		}

		const double val = m_stack.back();
		m_stack.pop_back();
		stackEvent.notify(stackChanged(), nullptr);
		return val;
	}


	void Stack::getElements(int maxSize, std::vector<double> &elements) const
	{
		elements.clear();
		for (const auto &elem : m_stack)
		{
			elements.push_back(elem);
			if (elements.size() >= maxSize) break;
		}
	}


	std::vector<double> Stack::getElements(int maxSize) const
	{
		std::vector<double> elements{};
		getElements(maxSize, elements);
		return elements;
	}


	void Stack::swapTop()
	{
		if (m_stack.size() < 2)
		{
			stackEvent.notify(stackError(), StackErrorData{ StackErrorData::ErrorCondition::TooFewArguments });
			throw Exception("Too few arguments for stack operation");
		}

		const double first = m_stack.back();
		m_stack.pop_back();
		const double second = m_stack.back();
		m_stack.pop_back();

		m_stack.push_back(first);
		m_stack.push_back(second);

		stackEvent.notify(stackChanged(), nullptr);
	}


	void Stack::clear()
	{
		m_stack.clear();
		stackEvent.notify(stackChanged(), nullptr);
	}


	Stack::Stack()
	{
		/* Register all stack events, by their string representation */
		stackEvent.registerEvent(stackChanged());
		stackEvent.registerEvent(stackError());
	}
}
