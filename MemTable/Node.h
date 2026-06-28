#ifndef NODE_H
#define NODE_H
#define boolean int
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Color.h"

typedef struct Node{
    int key;
    void *data;
    int rowsize;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    Color color;
    boolean isDeleted;
} Node;

static int global_index = 0;

void setGlobalIndex(int val) {
    global_index = val;
}

int createIndex(){
    return ++global_index;
}

Node* createNode(const void *data, int rowsize){
    Node *newNode = (Node*) malloc(sizeof(Node));
    
    if(newNode != NULL){
        newNode->data = data;
        newNode->key = createIndex();
        newNode->rowsize = rowsize;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        newNode->color = RED;
        newNode->isDeleted = false;
    }

    return newNode;
}

Node* createTombstone(int id){
    Node *newTombstone = (Node*) malloc(sizeof(Node));

    if(newTombstone != NULL){
        newTombstone->data = NULL;
        newTombstone->key = id;
        newTombstone->left = NULL;
        newTombstone->right = NULL;
        newTombstone->parent = NULL;
        newTombstone->color = RED;
        newTombstone->isDeleted = true;
    }
    return newTombstone;
}

#endif