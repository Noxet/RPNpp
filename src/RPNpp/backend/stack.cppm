
#include <deque>
#include <vector>

export module RPNpp.Stack;

namespace RPNpp
{
	export class Stack
	{
	public:
		static Stack& Instance();
		void push(double val);
		double pop();
		void getElements(int maxSize, std::vector<double> &elements) const;
		std::vector<double> getElements(int maxSize) const;
		void swapTop();

		Stack(const Stack &) = delete;
		Stack &operator=(const Stack &) = delete;
		Stack(Stack &&) = delete;
		Stack &&operator=(Stack &&) = delete;
	private:
		Stack() = default;
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
	}


	double Stack::pop()
	{
		const double val = m_stack.back();
		m_stack.pop_back();
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
		if (m_stack.size() < 2) return;

		const double first = m_stack.back();
		m_stack.pop_back();
		const double second = m_stack.back();
		m_stack.pop_back();

		m_stack.push_back(first);
		m_stack.push_back(second);
	}
}
