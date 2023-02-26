// word.cpp

#include <cassert>
#include <functional>
#include <string_view>
#include <string>
#include <vector>
#include <utils/Log.h>
#include <boost/algorithm/string/regex.hpp>
#include "word.h"

LOG_PREFIX("[word]: ");
LOG_POSTFIX("\n");

const int max_column_count = 4;

void word()
{
	LOG(" * Test 1 * ");
}

int word::load(const std::string &line)
{
	auto load_columns = [=, this](const std::vector<std::string_view>& columns)
	{
		bool level_is_present = true;
		try
		{
			level = std::stoi(columns.back().data());
		}
		catch (std::invalid_argument const& ex)
		{
			level_is_present = false;
		}
		catch (std::out_of_range const& ex)
		{
			return level_out_of_range;
		}
		if (!level_is_present)
			level = 0;
		else if (level < 0)
			return invalid_level;

		const int local_max_column_count = level_is_present ? max_column_count : max_column_count - 1;

		int sz = int(columns.size());
		assert(sz > 0); // It is checked on the level above
		value = columns[0];

		// Columns after the value may vary
		using cmd_t = std::function<void(const std::string_view&)>;
		std::vector<cmd_t> commands;
		commands.reserve(max_column_count);

		if (sz == local_max_column_count)
			commands.push_back([=, this](const std::string_view& column) {
				translation = column;
			});
			
		if (sz >= local_max_column_count - 1)
			commands.push_back([=, this](const std::string_view& column) {
				example = column;
			});
			
		for (int i = 0; i < commands.size(); i++)
			commands[i](columns[i + 1]);
	};

	// Parse the line into columns array
	std::vector<std::string_view> columns;
	columns.reserve(max_column_count);
	boost::algorithm::split_regex(columns, line, boost::regex("\t+"));

	// Load the columns into the word
	if (columns.size() < 1)
		return erc::invalid_column_count;
	load_columns(columns);
	return 0;
}
