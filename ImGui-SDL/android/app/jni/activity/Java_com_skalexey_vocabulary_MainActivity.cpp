#include <string>
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "vocabulary/activity_bridge"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C"
{
	JNIEXPORT std::string JNICALL Java_com_skalexey_vocabulary_MainActivity_getTempDir(JNIEnv* env, jobject self);
};

JNIEXPORT std::string JNICALL Java_com_skalexey_vocabulary_MainActivity_getTempDir(JNIEnv* env, jobject self)
{
	LOGD("getTempDir()");
	return std::filesystem::temp_directory_path().string(); 
}
