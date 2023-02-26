// words.h

#pragma once

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
	utils::ordered_map<std::string, word> list;
	int load(const fs::path& path);
	int update_local_storage();

private:
	std::vector<std::string> m_lines;
	fs::path m_fpath;
};
