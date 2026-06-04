#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "Color.h"

typedef struct Node{
    int value;

    struct Node *left;
    struct Node *right;
    struct Node *parent;
    Color color;
} Node;

Node* createNode(int value){
    Node *newNode = (Node*) malloc(sizeof(Node));
    if(newNode != NULL){
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        newNode->color = RED;
    }

    return newNode;
}

#endif