#include <any>
#include <string>

export module RPNpp.utilities:Observer;

using std::string;

namespace RPNpp
{
	export class Observer
	{
	public:
		explicit Observer(string &&name);

		void onEvent(std::any data);
		string name() const;

	private:
		string m_name;
	};

	Observer::Observer(string &&name) : m_name{ std::move(name) } {}
	void Observer::onEvent(std::any data) {}


	string Observer::name() const
	{
		return m_name;
	}
}
