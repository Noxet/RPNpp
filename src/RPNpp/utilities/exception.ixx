module;

#include <string>
#include <string_view>

export module RPNpp.utilities:Exception;

using std::string;
using std::string_view;


namespace RPNpp
{
	export class Exception
	{
	public:
		explicit Exception(string_view msg) : m_msg{ msg } {}
		const string &what() const { return m_msg; }

	private:
		string m_msg;
	};
}