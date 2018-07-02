#include <jni.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>

#define TAG "imx-i2c-jni"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

#define I2C_SLAVE_FORCE 0x0706
#define I2C_MASTER_DEV "/dev/i2c-0"

#define CLASS_PATH "com/myandroid/imx_i2c/MainActivity"
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

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
extern "C" JNIEXPORT jint JNICALL
Java_com_myandroid_imx_1i2c_MainActivity_i2c_1init(
        JNIEnv *env, jobject obj, jint addr) {
    LOGD("addr: 0x%x", addr);
    int fd = open(I2C_MASTER_DEV, O_RDWR);
    if (fd < 0) {
        LOGD("open device error\n");
        return -1;
    }

    int ret = ioctl(fd, I2C_SLAVE_FORCE, addr);
    if (ret < 0) {
        LOGD("Set slave address error (%d)\n", ret);
        goto fail;
    }

    LOGD("successful\n");
    return 0;

fail:
    close(fd);
    return -1;
}

static int regiserNativeMethods(JNIEnv* env, const char* classname,
    JNINativeMethod* gMethods, int numMethods) {
    jclass clazz;
    int r;

    /* java class */
    clazz = env->FindClass(classname);
    if (clazz == NULL) return JNI_FALSE;

    r = env->RegisterNatives(clazz, gMethods, numMethods);
    if (r < 0)
        return JNI_FALSE;

    return JNI_TRUE;
}

extern "C" JNIEXPORT jint JNICALL
native_i2c_init(JNIEnv* env, jclass clazz, jint addr) {
    LOGD("native_i2c_init\n");
    return 0;
}

static JNINativeMethod sMethods[] = {
        { "dynamic_i2c_init", "(I)I", (void *) native_i2c_init },
};

int register_ndk_load(JNIEnv *env) {
    int res = regiserNativeMethods(env, CLASS_PATH, sMethods, NELEM(sMethods));
    if (res < 0)
        LOGD("Unable to register native methods");
    return res;
}

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
        return -1;

    register_ndk_load(env);

    return JNI_VERSION_1_4;
}