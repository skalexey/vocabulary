// word.cpp

#include <cassert>
#include <functional>
#include <string_view>
#include <string>
#include <vector>
#include <utils/Log.h>
#include <boost/algorithm/string/regex.hpp>
#include "words.h"
#include "word.h"

LOG_PREFIX("[word]: ");
LOG_POSTFIX("\n");

const int max_column_count = 4;

int word::load()
{
	auto load_columns = [=, this](const std::vector<std::string_view>& columns)
	{
		bool level_is_present = true;
		try
		{
			m_level = std::stoi(columns.back().data());
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
			m_level = 0;
		else if (m_level < 0)
			return invalid_level;

		const int local_max_column_count = level_is_present ? max_column_count : max_column_count - 1;

		int sz = int(columns.size());
		assert(sz > 0); // It is checked on the level above
		m_value = columns[0];

		// Columns after the value may vary
		using cmd_t = std::function<void(const std::string_view&)>;
		std::vector<cmd_t> commands;
		commands.reserve(max_column_count);

		if (sz == local_max_column_count)
			commands.push_back([=, this](const std::string_view& column) {
				m_translation = column;
			});
			
		if (sz >= local_max_column_count - 1)
			commands.push_back([=, this](const std::string_view& column) {
				m_example = column;
			});
			
		for (int i = 0; i < commands.size(); i++)
			commands[i](columns[i + 1]);
	};

	// Parse the line into columns array
	std::vector<std::string_view> columns;
	columns.reserve(max_column_count);
	boost::algorithm::split_regex(columns, m_data, boost::regex("\t+"));
	if (columns.size() == 1 && columns[0] == m_data)
		return erc::invalid_column_count;
	// Load the columns into the word
	if (columns.size() < 1)
		return erc::invalid_column_count;
	load_columns(columns);
	return 0;
}

int word::write()
{
	m_data = serialize();
	return erc::no_error;
}

std::string word::serialize() const
{
	static const std::string delimeter = "\t\t\t";
	std::string result = m_value;
	if (!m_translation.empty())
		result += delimeter + std::string(m_translation);
	if (!m_example.empty())
		result += delimeter + m_example;
	if (m_level >= 0)
		result += delimeter + std::to_string(m_level);
	return result;
}

const std::string &word::get_example() const
{
	if (m_example == "^^")
		while (auto prev = previous())
			if (prev->m_example != "^^")
				return prev->m_example;
	return m_example;
}

void word::set_level(char level)
 {
	m_level = level;
	m_is_changed = true;
}

void word::set_example(const std::string &example)
{
	m_example = example;
	m_is_changed = true;
}

void word::set_translation(const std::string_view &translation)
{
	m_translation = translation;
	m_is_changed = true;
}

word* word::previous() const
{
	auto index = m_parent.list.get_index(m_value);
	assert(index >= 0);
	if (index == 0)
		return nullptr;
	return &m_parent.list.at(index - 1);
}

void word::set_value(const std::string &value)
{
	auto index = m_parent.list.rename(m_value, value);
	m_value = value;
	m_is_changed = true;
}	
