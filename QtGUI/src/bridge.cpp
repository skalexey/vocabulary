#include <QTemporaryDir>
#include <QDebug>
#include "bridge.h"

#define  LOGD(...)  qDebug() << __VA_ARGS__

std::string android_get_temp_dir() {
	QTemporaryDir dir;
    if (dir.isValid())
	{
		LOGD("Temp dir found: '" << dir.path() << "'");
        return dir.path().toStdString();
	}
    else
	{
		LOGD("No temp dir found");
		return "";
	}
}

std::string android_get_resources_dir() {
	QTemporaryDir dir;
    if (dir.isValid())
	{
		LOGD("Resource dir found: '" << dir.path() << "'");
        return dir.path().toStdString();
	}
    else
	{
		LOGD("No resource dir found");
		return "";
	}
}

// void android_request_keyboard()
// {
// 	JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
// 	LOGD("request_keyboard");
// 	if (auto c = env->FindClass("com/skalexey/vocabulary/MainActivity"))
// 	{
// 		if (auto m = env->GetStaticMethodID(c, "requestKeyboard", "()V"))
// 			env->CallStaticVoidMethod(c, m);
// 		else
// 			LOGD("No requestKeyboard method found");
// 	}
// 	else
// 		LOGD("No activity class found");
// }


void android_copy_assets()
{
	LOGD("android_copy_assets for Qt is not supported yet");
	// JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	// LOGD("android_copy_assets");
	// if (auto c = env->FindClass("com/skalexey/vocabulary/MainActivity"))
	// {
	// 	if (auto m = env->GetStaticMethodID(c, "copyAssets", "()V"))
	// 		env->CallStaticVoidMethod(c, m);
	// 	else
	// 		LOGD("No android_copy_assets method found");
	// }
	// else
	// 	LOGD("No activity class found");
}
