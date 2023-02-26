// words.cpp

#include <fstream>
#include <sstream>
#include <string_view>
#include <utils/Log.h>
#include <utils/file_utils.h>
#include "words.h"

LOG_PREFIX("[words]: ");
LOG_POSTFIX("\n");

void read_file_lines_easiest_way()
{

}

int words::load(const fs::path& fpath)
{
	if (!list.empty())
		list.clear();
    auto lines = utils::file::lines(fpath);
	for (int i = 0; i < lines.size(); i++)
	{
		auto& line = lines[i];
		list.reserve(lines.size());
		word w;
		if (w.load(line) == word::erc::no_error)
			list.add(w.value, w);
	}
	return utils::file::last_errcode();
}