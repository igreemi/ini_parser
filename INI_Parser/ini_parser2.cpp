#include "ini_parser2.h"
ini_parser2::ini_parser2(const std::string& file_name)
{
	std::ifstream file(file_name);
	if (!file)
	{
		throw std::runtime_error("Ошибка открытия файла.");
	}

	std::string line;
	std::string current_section;

	while (std::getline(file, line))
	{
		count_str++;

		if (!line.empty() && line[0] == '[' && line[line.size() - 1] == ']')
		{
			current_section = line.substr(1, line.size() - 2);
		}
		else if (!line.empty() && line[0] == ';')
		{
			continue;
		}
		else if (line.find('=') != std::string::npos)
		{
			std::size_t delimiter_pos = line.find('=');

			if (delimiter_pos != std::string::npos)
			{
				std::string key = line.substr(0, delimiter_pos);
				std::string value = line.substr(delimiter_pos + 1);
				if (value.find(';') != std::string::npos)
				{
					delimiter_pos = value.find(';');
					value = value.substr(0, delimiter_pos);
				}
				sections[current_section][key] = value;
			}

		}
		else if (!line.empty())
		{
			throw std::runtime_error("Неверный синтаксис. Строка: " + std::to_string(count_str));
		}
	}
}

std::string ini_parser2::get_value_string(const std::string s)
{

	std::size_t delimiter_pos = s.find('.');

	if (delimiter_pos == std::string::npos)
	{
		throw std::runtime_error("Неверный формат поиска. Требуется [название_секции.название_переменной].");
	}

	std::string search_section = s.substr(0, delimiter_pos);
	std::string search_var = s.substr(delimiter_pos + 1);

	if (sections.find(search_section) == sections.end())
	{
		throw std::runtime_error("Секция отсутствует.");
	}

	if (sections.at(search_section).find(search_var) == sections.at(search_section).end())
	{
		std::string tmp_var;

		int count = 1;
		size_t size = sections.at(search_section).size();

		for (const auto& pair : sections.at(search_section))
		{
			tmp_var += pair.first;
			if (count < size)
			{
				tmp_var += " или ";
			}
			count++;
		}

		throw std::runtime_error("Переменная отсутствует. Возможно Вы имели ввиду: " + tmp_var);
	}

	std::string value(sections.at(search_section).at(search_var));

	//	if (value.find('.') != std::string::npos)
	//	{
	//		std::size_t d_pos = value.find('.');
	//		value[d_pos] = ',';
	//	}

	if (value.empty())
	{
		throw std::runtime_error("Значение переменной отсутствует.");
	}

	return value;
}