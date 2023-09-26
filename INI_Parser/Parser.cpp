#include <iostream>
#include <string>

#include "ini_parser.h"
#include "ini_parser2.h"

int main()
{
	setlocale(0, "");

	try
	{
		ini_parser2 parser("config.ini");
		auto value = parser.get_value<double>("Section1.var1");
		std::cout << "value double = " << value << std::endl;

		ini_parser2 parser2("config.ini");
		auto value2 = parser2.get_value<int>("Section1.var1");
		std::cout << "value int = " << value2 << std::endl;

		ini_parser2 parser3("config.ini");
		auto value3 = parser3.get_value<std::string>("Section1.var1");
		std::cout << "value string = " << value3 << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
