#include "ini_parser.h"

ini_parser::ini_parser(const std::string& file_name)
{
	std::ifstream file(file_name);
	if (!file) {
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