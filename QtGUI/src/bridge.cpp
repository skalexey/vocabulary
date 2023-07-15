#include <QTemporaryDir>
#include <QDebug>
#include "bridge.h"
#include <utils/file_utils.h>

#include <utils/Log.h>
LOG_PREFIX("[android bridge]: ");
LOG_POSTFIX("\n");

bool create_directory_if_not_exists(const std::string& path)
{
    std::error_code ec;
	if (fs::create_directory(path, ec))
	{
		LOG("Directory '" << path << "' created.");
		return true;
	}
	else
	{
		LOG_ERROR("Directory '" << path << "' creation failed. Error: '" << ec.message() << "'");
		return false;
	}
}

std::string android_get_temp_dir() {
	const std::string dir_name = "temp";
	create_directory_if_not_exists(dir_name);
	return dir_name;
}

std::string android_get_resources_dir() {
	const std::string dir_name = "resources";
	create_directory_if_not_exists(dir_name);
	return dir_name;
}
