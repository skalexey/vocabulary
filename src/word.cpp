// word.cpp

#include <cassert>
#include <functional>
#include <string_view>
#include <string>
#include <vector>
#include <utils/Log.h>
#include <utils/string_utils.h>
#include "words.h"
#include "word.h"

LOG_PREFIX("[word]: ");
LOG_POSTFIX("\n");

const int max_column_count = 4;

int word::load()
{
	if (m_data.empty())
		return erc::invalid_column_count;
	//m_data.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
	auto load_columns = [=, self = this](const std::vector<std::string_view>& columns)
	{
		bool level_is_present = true;
		try
		{
			self->m_level = std::stoi(columns.back().data());
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
			self->m_level = 0;
		else if (self->m_level < 0)
			return invalid_level;

		const int local_max_column_count = level_is_present ? max_column_count : max_column_count - 1;

		int sz = int(columns.size());
		assert(sz > 0); // It is checked on the level above
		self->m_value = columns[0];

		// Columns after the value may vary
		using cmd_t = std::function<void(const std::string_view&)>;
		std::vector<cmd_t> commands;
		commands.reserve(max_column_count);

		if (sz == local_max_column_count)
			commands.push_back([=](const std::string_view& column) {
				self->m_translation = column;
			});

		if (sz >= local_max_column_count - 1)
			commands.push_back([=](const std::string_view& column) {
				self->m_example = column;
			});

		for (int i = 0; i < commands.size(); i++)
			commands[i](columns[i + 1]);

		return erc::no_error;
	};

	// Parse the line into columns array
	std::vector<std::string_view> columns;
	std::vector<std::string> columns2;
	columns.reserve(max_column_count);
	utils::split_repeated_delimeter(columns, m_data, '\t');
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
	{
		auto w = this;
		while (w = w->previous())
			if (w->m_example != "^^")
				return w->m_example;
	}
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

void word::set_translation(const std::string &translation)
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
