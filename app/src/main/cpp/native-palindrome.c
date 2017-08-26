//
// Created by ARPaul on 25-08-2017.
//
#include <jni.h>
#include <android/log.h>

JNIEXPORT jboolean JNICALL Java_com_arpaul_sortndk_PalindromeActivity_normalPalindromeJNI__J(JNIEnv *env, jobject instance,
                                                                                             jlong actualNumber) {

    long actualcopy = actualNumber;
    int i = 0, reverseNumber = 0;
    actualcopy = actualNumber;
    while(actualcopy) {
        reverseNumber = reverseNumber*10 + actualcopy%10;
        actualcopy /= 10;
    }

    if(actualNumber == reverseNumber)
        return 1;
    else
        return 0;
}

JNIEXPORT jboolean JNICALL
Java_com_arpaul_sortndk_PalindromeActivity_stringPalindromeJNI(JNIEnv *env, jobject instance, jstring actualString_) {
    const char *actualString = (*env)->GetStringUTFChars(env, actualString_, 0);
    const jsize length = (*env)->GetStringLength(env, actualString_);

    int i = 0;
    jint stringSize = length;

    int start = 0;
    jboolean isMatch = 1;
    stringSize--;
    while(start < stringSize) {
        char actual = actualString[start];
        char rev = actualString[stringSize];
        if(actual == rev) {
            start++;
            stringSize--;
            continue;
        } else {
            isMatch = 0;
            break;
        }
    }
    return isMatch;
}