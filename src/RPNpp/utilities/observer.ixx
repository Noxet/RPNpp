module;

#include <any>
#include <string>

export module RPNpp.utilities:Observer;

using std::string;

namespace RPNpp
{
	export class Observer
	{
	public:
		explicit Observer(string &&name) : m_name(std::move(name)) {}
		virtual ~Observer() = default;

		virtual void onEvent(const std::any &data) = 0;

		string name() const { return m_name; };

	private:
		string m_name;
	};
}
