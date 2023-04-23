// words.cpp

#include <fstream>
#include <sstream>
#include <string_view>
#include <utils/Log.h>
#include <utils/file_utils.h>
#include "words.h"

LOG_PREFIX("[words]: ");
LOG_POSTFIX("\n");

int words::load(const fs::path& fpath)
{
	if (!list.empty())
		list.clear();
	m_fpath = fpath;
    m_lines = utils::file::lines(m_fpath);
	for (int i = 0; i < m_lines.size(); i++)
	{
		auto& line = m_lines[i];
		list.reserve(m_lines.size());
		word w(*this, line);
		if (w.load() == word::erc::no_error)
			list.add(w.get_value(), w);
	}
	return utils::file::last_errcode();
}

int words::update_local_storage()
{
	std::ofstream ofs(m_fpath, std::ios::binary);
	if (!ofs.is_open())
		return erc::cant_open;
	std::for_each(list.begin(), list.end(), [&](auto entry) {
		auto& word = entry.second;
		if (word.is_changed())
			word.write();
		ofs << word.get_data() << std::endl;
	});
	return 0;
}