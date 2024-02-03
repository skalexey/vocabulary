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
#include <utils/log_stream.h>
#ifdef LOG_ON
	#include <QDebug>
	// LOG_STREAM(qDebug());
	// LOG_STREAM(qDebug());
#endif
#include "QtGUI/include/app.h"
#include "QtGUI/include/import_qml_plugins.h"
#include "QtGUI/include/import_qml_components_plugins.h"

LOG_POSTFIX("\n");
LOG_PREFIX("[qtgui-app]: ");

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
	GLOBAL_LOG_STREAM(qDebug().noquote());
}

int app::init()
{
    LOG("app::init");
	auto r = utils::ui::qt::app::init();
	if (r != 0)
		return r;
	return vocabulary_core::app::init();
}

bool app::on_update(float dt) {
	if (!m_log_stream.str().empty())
		m_log_stream.out();
	return true;
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
