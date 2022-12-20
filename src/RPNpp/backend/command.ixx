export module RPNpp.command;

namespace RPNpp
{
	/**
	 * An abstract class to handle user commands
	 */
	export class Command
	{
	public:
		virtual ~Command() = default;
		void execute();
		void undo();

		/**
		 * Returns a copy of the derived object, since a copy constructor
		 * will not be able to deduce the derived class
		 */
		Command* clone() const { return cloneImpl(); }

		/* Deleted ctors */
		Command(const Command &) = delete;
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


	export class UnaryCommand : public Command
	{
	public:
		virtual ~UnaryCommand() = default;

		/* Deleted ctors */
		UnaryCommand(const UnaryCommand &) = delete;
		UnaryCommand(UnaryCommand &&) = delete;
		UnaryCommand &operator=(const UnaryCommand &) = delete;
		UnaryCommand &operator=(UnaryCommand &&) = delete;

	protected:
		void checkPreconditionsImpl() const override;

	private:
		void executeImpl() noexcept override final;
		void undoImpl() noexcept override final;
		virtual double unaryOperation(double val) const = 0;

		double m_top;
	};


	export class BinaryCommand : public Command
	{
	public:
		virtual ~BinaryCommand() = default;

		/* Deleted ctors */
		BinaryCommand(const BinaryCommand &) = delete;
		BinaryCommand(BinaryCommand &&) = delete;
		BinaryCommand &operator=(const BinaryCommand &) = delete;
		BinaryCommand &operator=(BinaryCommand &&) = delete;

	protected:
		void checkPreconditionsImpl() const override;

	private:
		void executeImpl() noexcept override final;
		void undoImpl() noexcept override final;
		virtual double binaryOperation(double a, double b) const = 0;

		double m_a;
		double m_b;
	};
}
