import RPNpp.stack;
import RPNpp.utilities;
import RPNpp.command;
//import RPNpp.commandManager;
import RPNpp.commandDispatcher;

#include <any>
#include <iostream>
#include <vector>

using namespace RPNpp;
using std::string;
using std::cout;
using std::endl;


/**
 * Test classes for observing events
 */
namespace
{
	class StackErrorObserver : public Observer
	{
	public:
		StackErrorObserver(string name) : Observer(name) {}


		void onEvent(const std::any &data) override
		{
			try
			{
				const auto &d = std::any_cast<StackErrorData>(data);
				cout << "Stack error event: " << StackErrorData::Message(d.error()) << endl;
			}
			catch (const std::bad_any_cast &)
			{
				cout << "Failed conversion" << endl;
			}
		}
	};


	class StackChangedObserver : public Observer
	{
	public:
		StackChangedObserver(string name) : Observer(name) {}


		void onEvent(const std::any &data) override
		{
			cout << "Stack changed" << endl;
		}
	};
}


void printStack()
{
	auto &stack = Stack::Instance();
	const auto &elems = stack.getElements(10);
	cout << "Elements on stack: ";
	for (const auto &elem : elems)
	{
		cout << elem << ", ";
	}
	cout << endl;
}


int main()
{
	auto &stack = Stack::Instance();

	// attack observers
	stack.stackEvent.attach(Stack::stackError(), std::make_unique<StackErrorObserver>("StackErrorObserver"));
	stack.stackEvent.attach(Stack::stackChanged(), std::make_unique<StackChangedObserver>("StackChangedObserver"));

	registerCoreCommands();

	try
	{
		auto &cf = CommandFactory::Instance();
		CommandManager cm;
		auto add = cf.createCommand("+");
		//cm.executeCommand(std::move(add));

		stack.push(13.37);
		stack.push(69);
		printStack();
		cm.executeCommand(std::move(add));
		printStack();
		cm.undo();
		printStack();
		cm.redo();
		printStack();
	}
	catch (Exception &e)
	{
		cout << e.what() << endl;
	}
}
