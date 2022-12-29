module;

#include <format>
#include <string_view>
#include <string>
#include <sstream>
#include <istream>
#include <vector>

export module RPNpp.userInterfaces:CLI;

import RPNpp.utils;
import RPNpp.stack;
import :UserInterface;

namespace RPNpp
{
	export class CLI : public UserInterface
	{
	public:
		CLI(std::istream &in, std::ostream &out);

		void run() const;

	private:
		/* These should only be called through a UserInterface reference, hence they are in the private scope. */
		void postMessage(std::string_view strView) override;
		void stackChanged() override;

		std::istream &m_in;
		std::ostream &m_out;
	};


	CLI::CLI(std::istream &in, std::ostream &out) : m_in{ in }, m_out{ out } {}


	void CLI::run() const
	{
		for (std::string line; std::getline(m_in, line); )
		{
			m_out << "CLI RUN" << std::endl;
			std::stringstream ss{ line };
			for (const auto &token : Utils::tokenize(ss))
			{
				if (token == "exit" || token == "quit") return;
				notify(token);
			}
		}
	}


	void CLI::postMessage(std::string_view strView)
	{
		m_out << strView << std::endl;
	}


	void CLI::stackChanged()
	{
		m_out << "Current stack:\n";
		int index{ 0 };
		for (const auto &item : Stack::Instance().getElements(4))
		{
			m_out << std::format("{}: {}\n", ++index, item);
		}
		//m_out << std::format("{:->20}") << std::endl;
		m_out << std::string(10, '-') << std::endl;
	}

}
