//
// Created by ARPaul on 20-08-2017.
//
#include <jni.h>
#include <stdlib.h>
#include <time.h>

JNIEXPORT jintArray JNICALL
Java_com_arpaul_sortndk_MainActivity_bubbleSortJNI(JNIEnv *env, jobject instance,
                                                   jintArray oldValues_) {
    const jsize length = (*env)->GetArrayLength(env, oldValues_);

    jint *oarr = (*env)->GetIntArrayElements(env, oldValues_, NULL);

    for (int i = 0; i < length - 1; i++) {
        // Last i elements are already in place
        for (int j = 0; j < length - i - 1; j++) {
            if (oarr[j] > oarr[j + 1]) {
                int temp = oarr[j];
                oarr[j] = oarr[j + 1];
                oarr[j + 1] = temp;
            }
        }
    }

    (*env)->ReleaseIntArrayElements(env, oldValues_, oarr, NULL);

    return oldValues_;
}

JNIEXPORT jintArray JNICALL
Java_com_arpaul_sortndk_MainActivity_insertionSortJNI(JNIEnv *env, jobject instance,
                                                   jintArray oldValues_) {
    const jsize length = (*env)->GetArrayLength(env, oldValues_);

    jint *oarr = (*env)->GetIntArrayElements(env, oldValues_, NULL);

    for (int i = 1; i < length - 1; i++) {
        key = oarr[i];
        j = i-1;

        while(j >= 0 && oarr[j] > key) {
            oarr[j + 1] = oarr[j];
            j = j - 1;
        }
        oarr[j + 1] = key;
    }

    (*env)->ReleaseIntArrayElements(env, oldValues_, oarr, NULL);

    return oldValues_;
}

JNIEXPORT jintArray JNICALL
Java_com_arpaul_sortndk_MainActivity_getRandomListJNI(JNIEnv *env, jobject instance, jint length, jint maxVal) {

    jintArray newArray = (*env)->NewIntArray(env, length);
    jint *narr = (*env)->GetIntArrayElements(env, newArray, NULL);

    time_t t;

    /* Intializes random number generator */
    srand((unsigned) time(&t));

    for(int i = 0; i < length; i++) {
        narr[i] = rand() % maxVal;
    }

    (*env)->ReleaseIntArrayElements(env, newArray, narr, NULL);
    return newArray;
}

JNIEXPORT jintArray JNICALL
Java_com_arpaul_sortndk_MainActivity_separateZerosJNI(JNIEnv *env, jobject instance, jintArray oldValues_) {
    const jsize length = (*env)->GetArrayLength(env, oldValues_);
    jintArray newArray = (*env)->NewIntArray(env, length);

    jint *oarr = (*env)->GetIntArrayElements(env, oldValues_, NULL);
    jint *narr = (*env)->GetIntArrayElements(env, newArray, NULL);

    int descOrder = length;
    int ascOrder = 0;
    for(int i = 0; i < length; i++) {
        if(oarr[i] == 0)
            narr[descOrder++] = oarr[i];
        else
            narr[ascOrder++] = oarr[i];
    }
    (*env)->ReleaseIntArrayElements(env, newArray, narr, NULL);
//    env->ReleaseIntArrayElements(oldValues_, oarr, NULL);

    return newArray;
}

