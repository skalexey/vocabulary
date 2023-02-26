// word.h

#pragma once

#include <string>
#include <string_view>

struct word
{
	enum erc : int
	{
		no_error = 0,
		level_out_of_range,
		invalid_level,
		invalid_column_count
	};

	std::string value;
	std::string example;
	std::string_view translation;
	char level = -1;

	int load(const std::string& line);
};
