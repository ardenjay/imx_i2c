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
extern "C" int JNICALL
Java_com_myandroid_imx_1i2c_MainActivity_i2c_1init
        (JNIEnv *env, jobject, jint addr) {
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
