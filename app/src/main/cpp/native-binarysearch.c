#include <stddef.h>
#include <jni.h>
#include <malloc.h>

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

typedef struct Node NODE;

struct Node {
    int value;
    struct Node *left;
    struct Node *right;
};

struct Node *new_leaf();

void destroyTree(NODE *leaf);

void insertLeaf(NODE *leaf, jint value);

NODE *search_leaf(NODE *leaf, jint search);

JNIEXPORT struct Node *new_leaf() {
    NODE *leaf = malloc(sizeof(NODE));
    leaf->value = 0;
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
}

JNIEXPORT void destroyTree(NODE *leaf) {
    if(leaf != 0) {
        destroyTree(leaf->left);
        destroyTree(leaf->right);
        free(leaf);
    }
}

JNIEXPORT void insertLeaf(NODE *leaf, jint value) {
    if(value < leaf->value) {
        if(leaf->left != NULL) {
            insertLeaf(leaf->left, value);
        } else {
            leaf->left = new_leaf();
            leaf->left->value = value;
        }
    } else if(value > leaf->value) {
        if(leaf->right != NULL) {
            insertLeaf(leaf->right, value);
        } else {
            leaf->right = new_leaf();
            leaf->right->value = value;
        }
    }
}

JNIEXPORT NODE *search_leaf(NODE *leaf, jint search) {
    if(leaf != NULL) {
        if(leaf->value == search)
            return leaf;
        else if(search < leaf->value)
            return search_leaf(leaf->left, search);
        else if(search > leaf->value)
            return search_leaf(leaf->right, search);
        else
            return NULL;
    } else
        return NULL;
}

JNIEXPORT jint JNICALL
Java_com_arpaul_sortndk_BinarySearchActivity_binarySearchDMAJNI(JNIEnv *env, jobject instance, jintArray values_, jint search) {
    const jsize length = (*env)->GetArrayLength(env, values_);

    jint *values = (*env)->GetIntArrayElements(env, values_, NULL);

    int first = 0;
    int last = length - 1;
    int middle = (first+last)/2;
    jint searchReport = -1;

    NODE *tree = new_leaf();
    tree->value = values[middle];
    for (int i = 0; i < length; ++i) {
        if(i != middle) {
            insertLeaf(tree, values[i]);
        }
    }

    NODE* searchLeaf = search_leaf(tree, search);
    if(searchLeaf != NULL)
        searchReport = 1;

//    while (first <= last) {
//        if (values[middle] < search)
//            first = middle + 1;
//        else if (values[middle] == search) {
//            searchReport = middle;
//            break;
//        }
//        else
//            last = middle - 1;
//
//        middle = (first + last)/2;
//    }
//    if (first > last)
//        searchReport = -1;

    destroyTree(tree);

    (*env)->ReleaseIntArrayElements(env, values_, values, 0);

    return searchReport;
}