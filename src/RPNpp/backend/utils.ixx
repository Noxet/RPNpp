module;

#include <regex>
#include <string>

export module RPNpp.utils;

namespace RPNpp::Utils
{
	export bool isNum(const std::string &str)
	{
		const std::regex numExpr("^[-]*\\d+[\\.\\d+]*$");
		return std::regex_match(str, numExpr);
	}
}
