#include <SDL.h>
#include <jni.h>
#include "bridge.h"

#define  LOGD(...)  SDL_Log(__VA_ARGS__)

std::string android_get_temp_dir() {
	JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	LOGD("android_get_temp_dir");
	if (auto c = env->FindClass("com/skalexey/vocabulary/MainActivity"))
	{
		if (auto m = env->GetStaticMethodID(c, "getTempDir", "()Ljava/lang/String;")) {
            auto r = (jstring) env->CallStaticObjectMethod(c, m);
            const char *chars = env->GetStringUTFChars(r, nullptr);
            std::string ret(chars);
            env->ReleaseStringUTFChars(r, chars);
            return ret;
        }
        return "";
	}
	else
	{
		LOGD("No activity class found");
		return "";
	}
}

void android_request_keyboard()
{
	JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	LOGD("request_keyboard");
	if (auto c = env->FindClass("com/skalexey/vocabulary/MainActivity"))
	{
		if (auto m = env->GetStaticMethodID(c, "requestKeyboard", "();"))
			env->CallStaticObjectMethod(c, m);
		else
			LOGD("No requestKeyboard method found");
	}
	else
		LOGD("No activity class found");
}
