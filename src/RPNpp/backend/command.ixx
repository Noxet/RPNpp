module;

#include <functional>

export module RPNpp.command;

using std::function;

namespace RPNpp
{
	/**
	 * An abstract class to handle user commands
	 */
	export class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		void execute();
		void undo();

		/**
		 * Returns a copy of the derived object, since a copy constructor
		 * will not be able to deduce the derived class
		 */
		Command* clone() const { return cloneImpl(); }

		/* ctors */
		Command(const Command &) = default;
		Command(Command &&) = delete;
		Command& operator=(const Command &) = delete;
		Command& operator=(Command &&) = delete;

	private:
		/**
		 * Check to see if any preconditions are met before executing command.
		 * Since some commands do not need to check a precondition, e.g., pushing a number on the stack,
		 * this is not a pure virtual function, and default to doing nothing. Let derived classes
		 * implement the needed behaviour.
		 *
		 * The function handles all errors/exceptions
		 */
		virtual void checkPreconditionsImpl() const {}

		/*
		 * Following the NVI pattern, we have the following virtual private functions
		 */

		virtual void executeImpl() noexcept = 0;
		virtual void undoImpl() noexcept = 0;
		virtual Command* cloneImpl() const = 0;
	};


	export class UnaryCommand final : public Command
	{
		using unaryCommandOp = double(double);

	public:
		explicit UnaryCommand(function<unaryCommandOp> f);
		virtual ~UnaryCommand() override = default;

		/* ctors */
		UnaryCommand(const UnaryCommand &) = default;
		UnaryCommand(UnaryCommand &&) = delete;
		UnaryCommand &operator=(const UnaryCommand &) = delete;
		UnaryCommand &operator=(UnaryCommand &&) = delete;

	protected:
		void checkPreconditionsImpl() const override;

	private:
		void executeImpl() noexcept override;
		void undoImpl() noexcept override;
		UnaryCommand *cloneImpl() const override;

		double m_top;
		function<unaryCommandOp> m_func;
	};


	export class BinaryCommand final : public Command
	{
		using binaryCommandOp = double(double, double);

	public:
		explicit BinaryCommand(function<binaryCommandOp> f);
		virtual ~BinaryCommand() override = default;

		/* ctors */
		BinaryCommand(const BinaryCommand &) = default;
		BinaryCommand(BinaryCommand &&) = delete;
		BinaryCommand &operator=(const BinaryCommand &) = delete;
		BinaryCommand &operator=(BinaryCommand &&) = delete;

	protected:
		void checkPreconditionsImpl() const override;

	private:
		void executeImpl() noexcept override;
		void undoImpl() noexcept override;
		BinaryCommand *cloneImpl() const override;

		double m_a;
		double m_b;
		function<binaryCommandOp> m_func;
	};


	export class EnterCommand final : public Command
	{
	public:
		EnterCommand(double d);
		//virtual ~EnterCommand() override = default;

		/* ctors */
		EnterCommand(const EnterCommand &) = default;
		EnterCommand(EnterCommand &&) = delete;
		EnterCommand &operator=(const EnterCommand &) = delete;
		EnterCommand &operator=(EnterCommand &&) = delete;

	private:
		void executeImpl() noexcept override;
		void undoImpl() noexcept override;
		Command * cloneImpl() const override;

		double m_val;
	};
}
