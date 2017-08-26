//
// Created by ARPaul on 20-08-2017.
//
#include <jni.h>
#include <stdlib.h>
#include <time.h>

void mergeSort(int pInt[], int min, int max);

void merge(int *pInt, int min, int middle, int max);

void quickSort(jint *pInt, int min, int max);

void swap(jint *low, jint *high);

JNIEXPORT jintArray JNICALL
Java_com_arpaul_sortndk_SortActivity_bubbleSortJNI(JNIEnv *env, jobject instance, jintArray oldValues_) {
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
Java_com_arpaul_sortndk_SortActivity_insertionSortJNI(JNIEnv *env, jobject instance, jintArray oldValues_) {
    const jsize length = (*env)->GetArrayLength(env, oldValues_);

    jint *oarr = (*env)->GetIntArrayElements(env, oldValues_, NULL);

    int j;
    for (int i = 1; i < length - 1; i++) {
        j = i;

        while(j >= 0 && oarr[j] < oarr[j-1]) {
            int temp = oarr[j];
            oarr[j] = oarr[j - 1];
            oarr[j - 1] = temp;
            j--;
        }
    }

    (*env)->ReleaseIntArrayElements(env, oldValues_, oarr, 0);

    return oldValues_;
}

JNIEXPORT jintArray JNICALL
Java_com_arpaul_sortndk_SortActivity_selectionSortJNI(JNIEnv *env, jobject instance, jintArray oldValues_) {
    const jsize length = (*env)->GetArrayLength(env, oldValues_);

    jint *oarr = (*env)->GetIntArrayElements(env, oldValues_, NULL);

    int position ;
    for (int i = 0; i < length - 1; i++) {
        position = i;

        for (int j = i + 1 ; j < length ; j++) {
            if (oarr[position] > oarr[j] )
                position = j;
        }
        if (position != i) {
            int temp = oarr[i];
            oarr[i] = oarr[position];
            oarr[position] = temp;
        }
    }

    (*env)->ReleaseIntArrayElements(env, oldValues_, oarr, 0);

    return oldValues_;
}

jintArray JNICALL
Java_com_arpaul_sortndk_SortActivity_mergeSortJNI(JNIEnv *env, jobject instance, jintArray oldValues_) {
    const jsize length = (*env)->GetArrayLength(env, oldValues_);

    jint *oarr = (*env)->GetIntArrayElements(env, oldValues_, NULL);

    mergeSort(oarr, 0, length);

    (*env)->ReleaseIntArrayElements(env, oldValues_, oarr, 0);

    return oldValues_;
}

JNIEXPORT void mergeSort(int pInt[], int min, int max) {
    if (min < max) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = min + (max - min)/2;

        // Sort first and second halves
        mergeSort(pInt, min, m);
        mergeSort(pInt, m+1, max);

        merge(pInt, min, m, max);
    }
}

JNIEXPORT void merge(int *pInt, int min, int middle, int max) {
    int i, j, k;
    int n1 = middle - min + 1;
    int n2 =  max - middle;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = pInt[min + i];
    for (j = 0; j < n2; j++)
        R[j] = pInt[middle + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = min; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            pInt[k++] = L[i++];
        } else {
            pInt[k++] = R[j++];
        }
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        pInt[k++] = L[i++];
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        pInt[k++] = R[j++];
    }
}


JNIEXPORT jintArray JNICALL
Java_com_arpaul_sortndk_SortActivity_getRandomListJNI(JNIEnv *env, jobject instance, jint length, jint maxVal) {

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
Java_com_arpaul_sortndk_SortActivity_separateZerosJNI(JNIEnv *env, jobject instance, jintArray oldValues_) {
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

JNIEXPORT jintArray JNICALL
Java_com_arpaul_sortndk_SortActivity_quicksortSortJNI(JNIEnv *env, jobject instance, jintArray oldValues_) {
    const jsize length = (*env)->GetArrayLength(env, oldValues_);

    jint *oarr = (*env)->GetIntArrayElements(env, oldValues_, NULL);

    quickSort(oarr, 0, length);

    (*env)->ReleaseIntArrayElements(env, oldValues_, oarr, 0);

    return oldValues_;
}

JNIEXPORT void quickSort(jint *pInt, int min, int max) {
    if (min < max)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(pInt, min, max);

        // Separately sort elements before
        // partition and after partition
        quickSort(pInt, min, pi - 1);
        quickSort(pInt, pi + 1, max);
    }
}

JNIEXPORT jint partition(jint *pInt, int min, int max) {
    int pivot = pInt[max];    // pivot
    int i = (min - 1);  // Index of smaller element

    for (int j = min; j <= max- 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (pInt[j] <= pivot) {
            i++;    // increment index of smaller element
            swap(&pInt[i], &pInt[j]);
        }
    }
    swap(&pInt[i + 1], &pInt[max]);
    return (i + 1);
}

JNIEXPORT void swap(jint *low, jint *high) {
    int temp = *low;
    *low = *high;
    *high = temp;
}