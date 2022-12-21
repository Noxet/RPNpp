import RPNpp.stack;
import RPNpp.utilities;
import RPNpp.command;

#include <any>
#include <iostream>

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


int main()
{
	auto &stack = Stack::Instance();

	// attack observers
	stack.stackEvent.attach(Stack::stackError(), std::make_unique<StackErrorObserver>("StackErrorObserver"));
	stack.stackEvent.attach(Stack::stackChanged(), std::make_unique<StackChangedObserver>("StackChangedObserver"));

	BinaryCommand add{ [](double a, double b) { return a + b; } };

	try
	{
		stack.push(13.37);
		stack.push(69);
		add.execute();
		cout << stack.pop() << endl;
		stack.pop();
	}
	catch (Exception &e)
	{
		cout << e.what() << endl;
	}
}
