module;

module RPNpp.command;

import RPNpp.stack;
import RPNpp.utilities;

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
		stack.push(unaryOperation(top));

		// save the previous top for undo
		m_top = top;
	}


	void UnaryCommand::undoImpl() noexcept
	{
		auto &stack = Stack::Instance();
		stack.pop();
		stack.push(m_top);
	}


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
		stack.push(binaryOperation(a, b));

		// save the previous two values for undo
		m_a = a;
		m_b = b;
	}


	void BinaryCommand::undoImpl() noexcept
	{
		auto &stack = Stack::Instance();
		stack.pop();
		stack.pop();
		stack.push(m_b);
		stack.push(m_a);
	}
}
