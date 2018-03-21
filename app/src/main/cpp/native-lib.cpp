#include "jni.h"
#include <android/bitmap.h>
#include <opencv2/opencv.hpp>
#include <sys/system_properties.h>
#include <android/log.h>

using namespace cv;
#define  LOG_TAG    "From JNI"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_edgardeng_opencvnative_MainActivity_sayHello(JNIEnv *env, jclass type) {

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

/*
int setAndroidDeviceID(JNIEnv *env,  jclass type,jobject mContext)
{
    if(mContext == 0){
        return -1;
    }
    jclass cls_context;
    cls_context = env->FindClass("android/content/Context");
    if(cls_context == 0){
        return -1;
    }
    jmethodID getSystemService = env->GetMethodID(cls_context, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    if(getSystemService == 0){
        return -1;
    }
    jfieldID TELEPHONY_SERVICE = env->GetStaticFieldID(cls_context, "TELEPHONY_SERVICE", "Ljava/lang/String;");
    if(TELEPHONY_SERVICE == 0){
        return -1;
    }
    jstring str = (jstring) env->GetStaticObjectField(cls_context, TELEPHONY_SERVICE);

    printf("ndk--:%s",str);

    jobject telephonymanager = env->CallObjectMethod( mContext, getSystemService, str);
    if(telephonymanager == 0){
        return -1;
    }
    jclass cls_tm = env->FindClass("android/telephony/TelephonyManager");
    if(cls_tm == 0){
        return -1;
    }
    jmethodID getDeviceId = env->GetMethodID( cls_tm, "getDeviceId", "()Ljava/lang/String;");
    if(getDeviceId == 0){
        return -1;
    }
    jstring deviceid = (jstring) env->CallObjectMethod(telephonymanager, getDeviceId);

    char* device = (char *) env->GetStringUTFChars(deviceid, 0);
    printf("ndk--:%s",device);

    return 0;
}
*/

extern "C"
JNIEXPORT void JNICALL
Java_com_edgardeng_opencvnative_MainActivity_getImageEdge(JNIEnv *env, jclass type, jobject bitmap) {

    // TODO
    AndroidBitmapInfo info;
    void *pixels;

    CV_Assert(AndroidBitmap_getInfo(env, bitmap, &info) >= 0);
    CV_Assert(info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
              info.format == ANDROID_BITMAP_FORMAT_RGB_565);
    CV_Assert(AndroidBitmap_lockPixels(env, bitmap, &pixels) >= 0);
    CV_Assert(pixels);
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Mat temp(info.height, info.width, CV_8UC4, pixels);
        Mat gray;
        cvtColor(temp, gray, COLOR_RGBA2GRAY);
        Canny(gray, gray, 3, 9, 3);
        cvtColor(gray, temp, COLOR_GRAY2RGBA);
    } else {
        Mat temp(info.height, info.width, CV_8UC2, pixels);
        Mat gray;
        cvtColor(temp, gray, COLOR_RGB2GRAY);
        Canny(gray, gray, 3, 9, 3);
        cvtColor(gray, temp, COLOR_GRAY2RGB);
    }
    AndroidBitmap_unlockPixels(env, bitmap);

}extern "C"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_edgardeng_opencvnative_MainActivity_getDevice(JNIEnv *env, jclass type) {

    // 读取序号
//    char *m_devID;
//    __system_property_get("ro.serialno",m_devID);
//    LOGI("序列号：%s", m_devID);
//
//    char *m_devBrand;
//    __system_property_get("ro.product.brand",m_devBrand);
//    LOGE("品牌:%s", m_devBrand);
//
//    //读取机型
//    char *m_devModel;
//    __system_property_get("ro.product.model",m_devModel);
//    LOGE("机型:%s", m_devModel);
//
//    //读取sdk版本
//    char *m_szSdkVer;
//    __system_property_get("ro.build.version.sdk", m_szSdkVer);
//    LOGE("sdk版本:%s",m_szSdkVer);
//
//    char *m_devAbi;
//    __system_property_get("ro.product.cpu.abi", m_devAbi);
//    LOGE("abi版本:%s",m_devAbi);

    char *m_devAbiList;
    __system_property_get("ro.product.cpu.abilist", m_devAbiList);
    LOGI("abi列表:%s",m_devAbiList);


//    ro.build.id=LMY47V
//    ro.build.display.id=N928Dt_CNMobileB_1.18
//    ro.build.sw_internal_version=N928Dt_Z78_CN_MSXPH1C500J118
//    ro.build.sw_outer_version=N928Dt_CNMobileB_1.18
//    ro.build.version.incremental=eng.jiangxiaojun.20150829.170221
//    ro.build.version.sdk=22
//    ro.build.version.codename=REL
//    ro.build.version.all_codenames=REL
//    ro.build.version.release=5.1.1
//    ro.build.date=Sat Aug 29 17:03:44 CST 2015
//    ro.build.date.utc=1440839024
//    ro.build.type=user
//    ro.build.user=jiangxiaojun
//    ro.build.host=hipad25
//    ro.build.tags=release-keys
//    ro.build.flavor=N928Dt-user
//    ro.product.model=ZTE N928Dt
//    ro.product.brand=ZTE
//    ro.product.name=N928Dt
//    ro.product.device=N928Dt
//    ro.product.board=msm8909
//# ro.product.cpu.abi and ro.product.cpu.abi2 are obsolete,
//# use ro.product.cpu.abilist instead.
//    ro.product.cpu.abi=armeabi-v7a
//    ro.build.display.dcc.version=N928Dt.user.V1.18.Rev14539.20150829
//    ro.build.display.software.id=N928Dt_Z78_CN_MSXPH1C500J118
//    ro.build.display.hardware.id=P1
//    ro.build.display.hardware=P1
//    ro.product.svn.info=14539
//    ro.product.cpu.abi2=armeabi
//    ro.product.cpu.abilist=armeabi-v7a,armeabi
//    ro.product.cpu.abilist32=armeabi-v7a,armeabi
//    ro.product.cpu.abilist64=
//    ro.product.manufacturer=ZTE
//    ro.product.locale.language=zh
//    ro.product.locale.region=CN
//    ro.wifi.channels=
//    ro.board.platform=msm8909
//# ro.build.product is obsolete; use ro.product.device
//    ro.build.product=N928Dt
//# Do not try to parse description, fingerprint, or thumbprint
//    ro.build.description=N928Dt-user 5.1.1 LMY47V eng.jiangxiaojun.20150829.170221 release-keys
//    ro.build.fingerprint=ZTE/N928Dt/N928Dt:5.1.1/LMY47V/jiangxiaojun08291703:user/release-keys
//    ro.build.characteristics=default

    jstring str = env->NewStringUTF("HelloDevice");  //直接使用该JNI构造一个jstring对象返回
    return str;

}
