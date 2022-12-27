module;

#include <functional>

module RPNpp.command;

import RPNpp.stack;
import RPNpp.utilities;

using std::function;

namespace RPNpp
{
	void Command::execute()
	{
		checkPreconditionsImpl();
		executeImpl();
	}


	void Command::undo()
	{
		undoImpl();
	}


	/*
	 ********** UNARY COMMAND DECLARATION **********
	 */

	UnaryCommand::UnaryCommand(function<unaryCommandOp> f) : m_top{}, m_func{ f } {}


	void UnaryCommand::checkPreconditionsImpl() const
	{
		if (Stack::Instance().size() < 1)
		{
			throw Exception("Stack needs at least one element to perform the operation");
		}
	}


	void UnaryCommand::executeImpl() noexcept
	{
		auto &stack = Stack::Instance();
		const auto top = stack.pop();
		stack.push(m_func(top));

		// save the previous top for undo
		m_top = top;
	}


	void UnaryCommand::undoImpl() noexcept
	{
		auto &stack = Stack::Instance();
		stack.pop();
		stack.push(m_top);
	}


	UnaryCommand* UnaryCommand::cloneImpl() const
	{
		return new UnaryCommand{ *this };
	}


	BinaryCommand::BinaryCommand(function<binaryCommandOp> f) : m_a{}, m_b{}, m_func{ f } {}


	/*
	 ********** BINARY COMMAND DECLARATION **********
	 */

	void BinaryCommand::checkPreconditionsImpl() const
	{
		if (Stack::Instance().size() < 2)
		{
			throw Exception("Stack needs at least two elements to perform the operation");
		}
	}


	void BinaryCommand::executeImpl() noexcept
	{
		auto &stack = Stack::Instance();
		const auto a = stack.pop();
		const auto b = stack.pop();
		stack.push(m_func(a, b));

		// save the previous two values for undo
		m_a = a;
		m_b = b;
	}


	void BinaryCommand::undoImpl() noexcept
	{
		auto &stack = Stack::Instance();
		stack.pop();
		stack.push(m_b);
		stack.push(m_a);
	}


	BinaryCommand* BinaryCommand::cloneImpl() const
	{
		return new BinaryCommand{ *this };
	}


	EnterCommand::EnterCommand(const double d) : m_val{ d } {}


	void EnterCommand::executeImpl() noexcept
	{
		Stack::Instance().push(m_val);
	}


	void EnterCommand::undoImpl() noexcept
	{
		Stack::Instance().pop();
	}


	Command* EnterCommand::cloneImpl() const
	{
		return new EnterCommand{ *this };
	}
}
