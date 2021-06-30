#include <jni.h>
#include <string>
#include <sample_rate_change_api.h>
#include <noise_suppress_api.h>
#include <agc_process_api.h>


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

extern "C"
JNIEXPORT jint JNICALL
Java_util_AudioJniUtil_nsInit(JNIEnv *env, jobject thiz, jobject ns_params) {
    int ret = 0;
    VOID *pNs = NULL;
    // create ns
    ret = TT_NS_Create(&pNs);
    if (ret != 0) {
        printf("create nc error! code=%d\n", ret);
    }

    // read ns param from java
    jclass nsParamsJclass = (*env).GetObjectClass(ns_params);
    if (nsParamsJclass == NULL) return -100;

    jfieldID fsFieldId = (*env).GetFieldID(nsParamsJclass, "fs", "I");
    if (fsFieldId == NULL) return -100;
    jint fs = (*env).GetIntField(ns_params, fsFieldId);

    jfieldID maxDenoiseDbFieldId = (*env).GetFieldID(nsParamsJclass, "maxDenoiseDb", "I");
    if (maxDenoiseDbFieldId == NULL) return -100;
    jint maxDenoiseDb = (*env).GetIntField(ns_params, maxDenoiseDbFieldId);

    stNSParams stNsParams = {fs, maxDenoiseDb};

    // init ns
    ret = TT_NS_Init(pNs, &stNsParams);
    if (ret != 0) {
        printf("init ns error! code=%d\n", ret);
    }

    // save ns instance pointer in java
    jclass objectJclass = env->GetObjectClass(thiz);
    jfieldID nsPtrJfieldId = env->GetFieldID(objectJclass, "nsPtr", "J");
    env->SetLongField(thiz, nsPtrJfieldId, (jlong) pNs);
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_util_AudioJniUtil_nsProcess(JNIEnv *env, jobject thiz, jstring src_file_path,
                                 jstring dst_file_path) {

    jclass objectJclass = env->GetObjectClass(thiz);
    jfieldID nsPtrFieldId = env->GetFieldID(objectJclass, "nsPtr", "J");
    jlong nsPtrJlong = env->GetLongField(thiz, nsPtrFieldId);

    char *srcFilePath = jstringTostring(env, src_file_path);
    char *dstFilePath = jstringTostring(env, dst_file_path);

    VOID *pSrc = (VOID *) nsPtrJlong;
    return TT_NS_Process_File(pSrc, srcFilePath, dstFilePath);
}

extern "C"
JNIEXPORT jint JNICALL
Java_util_AudioJniUtil_agcInit(JNIEnv *env, jobject thiz, jobject agc_params) {
    int ret = 0;
    VOID *pAgc = NULL;
    // create agc
    ret = TT_AGC_Create(&pAgc);
    if (ret != 0) {
        printf("create agc error! code=%d\n", ret);
    }

    // read agc param from java
    jclass agcParamsJclass = (*env).GetObjectClass(agc_params);
    if (agcParamsJclass == NULL) return -100;

    jfieldID fsFieldId = (*env).GetFieldID(agcParamsJclass, "fs", "J");
    if (fsFieldId == NULL) return -100;
    jlong fs = (*env).GetLongField(agc_params, fsFieldId);

    jfieldID targetLevelDbFsFieldId = (*env).GetFieldID(agcParamsJclass, "targetLevelDbfs", "S");
    if (targetLevelDbFsFieldId == NULL) return -100;
    jshort targetLevelDbfs = (*env).GetShortField(agc_params, targetLevelDbFsFieldId);

    jfieldID compressionGainDbFieldId = (*env).GetFieldID(agcParamsJclass, "compressionGainDb",
                                                          "S");
    if (compressionGainDbFieldId == NULL) return -100;
    jshort compressionGainDb = (*env).GetShortField(agc_params, compressionGainDbFieldId);

    jfieldID limiterEnableFieldId = env->GetFieldID(agcParamsJclass, "limiterEnable", "Z");
    if (limiterEnableFieldId == NULL) return -100;
    jboolean limiterEnable = (*env).GetBooleanField(agc_params, limiterEnableFieldId);

    unsigned int fsInt = fs & 0xffffffff;
    char limiterEnableChar = 1;
    if (limiterEnable) { limiterEnableChar = 1; } else { limiterEnableChar = 0; }

    stAGCParams stAgcParams = {fsInt, targetLevelDbfs, compressionGainDb, limiterEnableChar};

    // init agc
    ret = TT_AGC_Init(pAgc, &stAgcParams);
    if (ret != 0) {
        printf("init agc error! code=%d\n", ret);
    }

    // save agc instance pointer in java
    jclass objectJclass = env->GetObjectClass(thiz);
    jfieldID nsPtrJfieldId = env->GetFieldID(objectJclass, "agcPtr", "J");
    env->SetLongField(thiz, nsPtrJfieldId, (jlong) pAgc);
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_util_AudioJniUtil_agcProcess(JNIEnv *env, jobject thiz, jstring src_file_path,
                                  jstring dst_file_path) {
    jclass objectJclass = env->GetObjectClass(thiz);
    jfieldID agcPtrFieldId = env->GetFieldID(objectJclass, "agcPtr", "J");
    jlong agcPtrJlong = env->GetLongField(thiz, agcPtrFieldId);

    char *srcFilePath = jstringTostring(env, src_file_path);
    char *dstFilePath = jstringTostring(env, dst_file_path);

    VOID *pAgc = (VOID *) agcPtrJlong;
    return TT_AGC_Process_File(pAgc, srcFilePath, dstFilePath);
}

extern "C"
JNIEXPORT jint JNICALL
Java_util_AudioJniUtil_nsFree(JNIEnv *env, jobject thiz) {
    jclass objectJclass = env->GetObjectClass(thiz);
    jfieldID nsPtrFieldId = env->GetFieldID(objectJclass, "nsPtr", "J");
    jlong nsPtrJlong = env->GetLongField(thiz, nsPtrFieldId);

    VOID *pNs = (VOID *) nsPtrJlong;

    return TT_NS_Free(pNs);
}

extern "C"
JNIEXPORT jint JNICALL
Java_util_AudioJniUtil_agcFree(JNIEnv *env, jobject thiz) {
    jclass objectJclass = env->GetObjectClass(thiz);
    jfieldID agcPtrFieldId = env->GetFieldID(objectJclass, "agcPtr", "J");
    jlong agcPtrJlong = env->GetLongField(thiz, agcPtrFieldId);

    VOID *pAgc = (VOID *) agcPtrJlong;

    return TT_AGC_Free(pAgc);
}