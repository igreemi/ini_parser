#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>

class ini_parser2
{
private:
	std::map<std::string, std::map<std::string, std::string>> sections;
	std::string get_value_string(const std::string s);
	int count_str = 0;

public:
	explicit ini_parser2(const std::string& file_name);

	template<typename T>
	T get_value(const std::string s)
	{
		static_assert(sizeof(T) == -1, "not implemented type for get_value");
	}

	template<>
	std::string get_value(std::string s)
	{
		std::string str_val = get_value_string(s);

		if (str_val.find(',') != std::string::npos)
		{
			std::size_t d_pos = str_val.find(',');
			str_val[d_pos] = '.';
		}

		return str_val;
	}

	template<>
	int get_value(std::string s)
	{
		std::string str_val = get_value_string(s);

		return std::stoi(str_val);
	}

	template<>
	double get_value(std::string s)
	{
		std::string str_val = get_value_string(s);

		if (str_val.find('.') != std::string::npos)
		{
			std::size_t d_pos = str_val.find('.');
			str_val[d_pos] = ',';
		}

		return std::stod(str_val);
	}
};

