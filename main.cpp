#include <array>
#include <iostream>

auto main() -> int
<%
	std::cout << "Enter two numbers: " << std::endl;

	std::array<int, 2> a;
	std::cin >> a<:0:> >> a<:1:>;

	if ((compl a<:0:> bitor a<:1:>) == compl 0)
	<%
		std::cout << "Femfemfemfemfemfem" << std::endl;
	%> else <%
		std::cout << "Bye" << std::endl;
	%>

	return 0;
%>
