#include <jni.h>
#include <string>
#include <sample_rate_change_api.h>


//jni中 jstring转换成 char* 的函数
char *jstringTostring(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    //参数1：java类对象    参数2：方法名    参数3：该参数的签名
    jmethodID mid = env->GetMethodID(
            clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jstring strencode = env->NewStringUTF("utf-8");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    jsize alen = env->GetArrayLength(barr);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

extern "C"
JNIEXPORT jint JNICALL
Java_util_AudioJniUtil_getVersion(JNIEnv *env, jobject thiz, jstring string, jint length) {
    const char *string1 = (*env).GetStringUTFChars(string, 0);
    return TT_SRC_Get_Version(reinterpret_cast<INT8 *>(*string1), length);
}

extern "C"
JNIEXPORT jint JNICALL
Java_util_AudioJniUtil_srcInit(JNIEnv *env, jobject thiz, jobject src_params) {
    int ret = 0;
    VOID *pSrc = NULL;
    // create src
    ret = TT_SRC_Create(&pSrc);
    if (ret != 0) {
        printf("create src error! code=%d\n", ret);
    }

    // read src param from java
    jclass srcParamsJclass = (*env).GetObjectClass(src_params);
    if (srcParamsJclass == NULL) return -100;

    jfieldID inSampleRateFieldId = (*env).GetFieldID(srcParamsJclass, "inSampleRate", "I");
    if (inSampleRateFieldId == NULL) return -100;
    jint inSampleRate = (*env).GetIntField(src_params, inSampleRateFieldId);

    jfieldID outSampleRateFieldId = (*env).GetFieldID(srcParamsJclass, "outSampleRate", "I");
    if (outSampleRateFieldId == NULL) return -100;
    jint outSampleRate = (*env).GetIntField(src_params, outSampleRateFieldId);

    jfieldID channelFieldId = (*env).GetFieldID(srcParamsJclass, "channel", "I");
    if (channelFieldId == NULL) return -100;
    jint channel = (*env).GetIntField(src_params, channelFieldId);

    jfieldID qualityFieldId = (*env).GetFieldID(srcParamsJclass, "quality", "I");
    if (qualityFieldId == NULL) return -100;
    jint quality = (*env).GetIntField(src_params, qualityFieldId);

    SRCParams srcParams = {inSampleRate, outSampleRate, quality, channel};

    // init src
    ret = TT_SRC_Init(pSrc, &srcParams);
    if (ret != 0) {
        printf("init src error! code=%d\n", ret);
    }

    // get src param
    SRCParams outSrcParams;
    ret = TT_SRC_GetParams(pSrc, &outSrcParams);
    printf(" fs in is %d\n", outSrcParams.inSampleRate);
    printf(" fs out is %d\n", outSrcParams.outSampleRate);
    printf(" quality is %d\n", outSrcParams.quality);
    printf(" channel is %d\n", outSrcParams.channel);

    // save src instance pointer in java
    jclass objectJclass = env->GetObjectClass(thiz);
    jfieldID srcPtrJfieldId = env->GetFieldID(objectJclass, "srcPtr", "J");
    env->SetLongField(thiz, srcPtrJfieldId, (jlong) pSrc);
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_util_AudioJniUtil_srcProcess(JNIEnv *env, jobject thiz, jstring src_file_path,
                                  jstring dst_file_path) {
    jclass objectJclass = env->GetObjectClass(thiz);
    jfieldID srcPtrFieldId = env->GetFieldID(objectJclass, "srcPtr", "J");
    jlong srcPtrJlong = env->GetLongField(thiz, srcPtrFieldId);

    char *srcFilePath = jstringTostring(env, src_file_path);
    char *dstFilePath = jstringTostring(env, dst_file_path);

    VOID *pSrc = (VOID *) srcPtrJlong;
    return TT_SRC_Process_File(pSrc, srcFilePath, dstFilePath);
}