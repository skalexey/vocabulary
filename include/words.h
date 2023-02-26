// words.h

#pragma once

#include <string>
#include <utils/ordered_map.h>
#include <utils/filesystem.h>
#include "word.h"

struct words
{
	utils::ordered_map<std::string, word> list;
	int load(const fs::path& path);
};
