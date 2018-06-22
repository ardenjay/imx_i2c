#include <jni.h>
#include <string>
#include<android/log.h>

#define TAG "imx-i2c-jni"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

extern "C" JNIEXPORT jstring
JNICALL
Java_com_myandroid_imx_1i2c_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "JNI";
    return env->NewStringUTF(hello.c_str());
}

/*
 * Class:     com_myandroid_imx_i2c_MainActivity
 * Method:    i2c_init
 * Signature: (I)V
 */
extern "C" void JNICALL
Java_com_myandroid_imx_1i2c_MainActivity_i2c_1init
        (JNIEnv *env, jobject, jint addr) {
    LOGD("addr: 0x%x", addr);
}
