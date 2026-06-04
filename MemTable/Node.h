#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Color.h"
#include "Pokemon.h"

typedef struct Node{
    Pokemon *pokemon;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    Color color;
} Node;

int createIndex(){
    static int global_index = 0;
    return ++global_index;
}

Node* createNode(const char *name){
    Node *newNode = (Node*) malloc(sizeof(Node));
    
    Pokemon *pokemon = (Pokemon*) malloc(sizeof(Pokemon));
    strcpy(pokemon->name, name);
    pokemon->index = createIndex();

    if(newNode != NULL){
        newNode->pokemon = pokemon;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        newNode->color = RED;
    }

    return newNode;
}


#endif