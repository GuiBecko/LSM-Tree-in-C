#ifndef NODE_H
#define NODE_H
#define boolean int
#define true 1
#define false 0

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
    boolean isDeleted;
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
        newNode->isDeleted = false;
    }

    return newNode;
}

Node* createTombstone(int id){
    Node *newTombstone = (Node*) malloc(sizeof(Node));
    Pokemon *pokemon = (Pokemon*) malloc(sizeof(Pokemon));
    strcpy(pokemon->name, " TB ");
    pokemon->index = id;

    if(newTombstone != NULL){
        newTombstone->pokemon = pokemon;
        newTombstone->left = NULL;
        newTombstone->right = NULL;
        newTombstone->parent = NULL;
        newTombstone->color = RED;
        newTombstone->isDeleted = true;
    }
    return newTombstone;
}

#endif