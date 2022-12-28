module;

#include <algorithm>
#include <string_view>
#include <string>
#include <sstream>
#include <vector>

export module RPNpp.userInterfaces:CLI;

import :UserInterface;

namespace RPNpp
{
	export class CLI : public UserInterface
	{
	public:
		CLI(std::istream &in, std::ostream &out);

		void run();

	private:
		/* These should only be called through a UserInterface reference, hence they are in the private scope. */
		void postMessage(std::string_view strView) override;
		void stackChanged() override;

		std::vector<std::string> tokenize(std::istream &is);

		std::istream &m_in;
		std::ostream &m_out;
	};


	CLI::CLI(std::istream &in, std::ostream &out) : m_in{ in }, m_out{ out } {}


	void CLI::run()
	{
		for (std::string line; std::getline(m_in, line); )
		{
			std::istringstream iss{ line };
			for (const auto &token : tokenize(iss))
			{
				if (token == "exit" || token == "quit") return;
				uiEvent.notify(commandEntered(), token);
			}
		}
	}


	void CLI::postMessage(std::string_view strView) {}
	void CLI::stackChanged() {}
	std::vector<std::string> CLI::tokenize(std::istream &is)
	{
		std::vector<std::string> tokens{};
		for (std::istream_iterator<std::string> i{is}; i != std::istream_iterator<std::string>{}; ++i)
		{
			std::string t;
			std::ranges::transform(*i, std::back_inserter<std::string>(t), ::tolower);
			tokens.push_back(std::move(t));
		}
		return tokens;
	}
}
