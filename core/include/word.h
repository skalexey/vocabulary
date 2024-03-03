// word.h

#pragma once

#include <climits>
#include <string>
#include <string_view>

class words;

class word
{
public:
	enum erc : int
	{
		no_error = 0,
		level_out_of_range,
		invalid_level,
		invalid_column_count
	};

	using level_t = char;
	static constexpr level_t level_max = CHAR_MAX;

	word(words& parent, std::string& data) : m_parent(&parent), m_data(&data) {}
	int load();
	int write();
	std::string serialize() const;

	std::string& data() { return *m_data; }
	words& parent() { return *m_parent; }
	const words& get_parent() const { return *m_parent; }
	const std::string& get_data() const { return *m_data; }
	const std::string& get_value() const { return m_value; }
	const std::string& get_example() const;
	const std::string& get_translation() const { return m_translation; }
	level_t get_level() const { return m_level; }
	bool is_changed() const { return m_is_changed; }

	void set_level(level_t level);
	bool set_value(const std::string& value);
	void set_example(const std::string& example);
	void set_translation(const std::string& translation);

protected:
	const word* previous() const;

private:
	words* m_parent;
	std::string* m_data;
	std::string m_value = "";
	std::string m_example = "";
	std::string m_translation = "";
	level_t m_level = -1;
	bool m_is_changed = false;
};
