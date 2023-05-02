#pragma once

#include <memory>
#include <stdio.h>
#include <csignal>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <utils/io_utils.h>
#include <utils/print_defs.h>
#include <utils/common.h>
#include <utils/Log.h>
#ifdef LOG_ON
    #include <QDebug>
#endif
#include "QtGUI/include/app.h"

LOG_POSTFIX("\n");
LOG_PREFIX("[app]: ");

using utils::void_int_cb;

namespace
{
	const std::string log_fname = "vocabulary_log.txt";
}

app::app(int argc, char* argv[])
	: utils::ui::app(argc, argv)
	, utils::ui::qt::app(argc, argv)
	, vocabulary_core::app(argc, argv)
{
	// Create a new log file
	std::ofstream f(utils::file::temp_directory_path() / log_fname);
}

int app::init()
{
    LOG("app::init");
	return vocabulary_core::app::init();
}

bool app::on_update(float dt) {
	if (!m_log_stream.str().empty())
		m_log_stream.out();
	return vocabulary_core::app::on_update(dt);
}

void app::log_stringstream::out()
{
	if (str().empty())
		return;
	std::ofstream f(utils::file::temp_directory_path() / log_fname, std::ios::app);
	assert(f.is_open());
    f << str();
#ifdef LOG_ON
    qDebug() << str();
#endif
	str("");
}
