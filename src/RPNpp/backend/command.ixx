export module RPNpp.command;

namespace RPNpp
{
	export class Command
	{
	public:
		virtual ~Command();
		void execute();
		void redo();

	protected:
		Command();

	private:
		virtual void executeImpl() = 0;
		virtual void undoImpl() = 0;
	};
}