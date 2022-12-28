module;

#include <algorithm>
#include <compare>
#include <istream>
#include <sstream>
#include <iterator>
#include <ranges>
#include <regex>
#include <string>
#include <vector>


export module RPNpp.utils;

namespace RPNpp::Utils
{
	export bool isNum(const std::string &str)
	{
		const std::regex numExpr("^[-]*\\d+[\\.\\d+]*$");
		return std::regex_match(str, numExpr);
	}

	export std::vector<std::string> tokenize(std::stringstream &ss)
	{
		std::vector<std::string> tokens;
		/*for (std::istream_iterator<std::string> i{ is }; i != std::istream_iterator<std::string>{}; ++i)
		{
			std::string t;
			std::ranges::transform(*i, std::back_inserter<std::string>(t), ::tolower);
			tokens.push_back(std::move(t));
		}*/

		std::string t;
		while (ss >> t)
		{
			tokens.push_back(t);
		}

		return tokens;
	}
}
