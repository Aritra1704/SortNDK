#include <stddef.h>
#include <jni.h>

//
// Created by ARPaul on 26-08-2017.
//

JNIEXPORT jint JNICALL
Java_com_arpaul_sortndk_BinarySearchActivity_binarySearchJNI(JNIEnv *env, jobject instance, jintArray values_, jint search) {
    const jsize length = (*env)->GetArrayLength(env, values_);

    jint *values = (*env)->GetIntArrayElements(env, values_, NULL);

    int first = 0;
    int last = length - 1;
    int middle = (first+last)/2;
    jint searchReport = -1;

    while (first <= last) {
        if (values[middle] < search)
            first = middle + 1;
        else if (values[middle] == search) {
            searchReport = middle;
            break;
        }
        else
            last = middle - 1;

        middle = (first + last)/2;
    }
    if (first > last)
        searchReport = -1;

    (*env)->ReleaseIntArrayElements(env, values_, values, 0);

    return searchReport;
}