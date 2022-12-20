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
		Command(Command &) = delete;
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
}
