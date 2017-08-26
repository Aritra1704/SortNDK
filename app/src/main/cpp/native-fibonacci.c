//
// Created by ARPaul on 26-08-2017.
//

#include <jni.h>

JNIEXPORT jintArray JNICALL Java_com_arpaul_sortndk_FibonacciActivity_normalFibonacciJNI(JNIEnv *env, jobject instance, jint length) {

    jintArray newArray = (*env)->NewIntArray(env, length);
    jint *narr = (*env)->GetIntArrayElements(env, newArray, NULL);

    int val1 = 0, val2 = 1, val3 = 0;
    if(length > 0)
        narr[0] = val1;
    if(length > 1)
        narr[1] = val2;
    if(length > 2) {
        for(int i = 2; i < length; i++) {
            val3 = val2 + val1;
            narr[i] = val3;
            val1 = val2;
            val2 = val3;
        }
    }

    (*env)->ReleaseIntArrayElements(env, newArray, narr, NULL);
    return newArray;
}

JNIEXPORT jintArray JNICALL Java_com_arpaul_sortndk_FibonacciActivity_recurFibonacciJNI(JNIEnv *env, jobject instance, jint length) {

    jintArray newArray = (*env)->NewIntArray(env, length);
    jint *narr = (*env)->GetIntArrayElements(env, newArray, NULL);

    int counter;
    for(counter = 0; counter < length; counter++){
        narr[counter] = fibonacci(counter);
    }

    (*env)->ReleaseIntArrayElements(env, newArray, narr, NULL);
    return newArray;
}

int fibonacci(int term){
    /* Exit condition of recursion*/
    if(term < 2)
        return term;
    return fibonacci(term - 1) + fibonacci(term - 2);
}