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

#endif