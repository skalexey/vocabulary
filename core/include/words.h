// words.h

#pragma once

#include <utility>
#include <string>
#include <vector>
#include <utils/ordered_map.h>
#include <utils/filesystem.h>
#include "word.h"

struct words
{
	enum erc : int
	{
		no_error = 0,
		cant_open
	};
	enum add_word_erc : int
	{
		success = 0,
		word_exists,
		load_error,
	};
	utils::ordered_map<std::string, word> list;
	int load(const fs::path& path);
	int update_local_storage();
	std::pair<std::reference_wrapper<word>, int> new_word(const std::string& w);

private:
	std::vector<std::string> m_lines;
	fs::path m_fpath;
};
