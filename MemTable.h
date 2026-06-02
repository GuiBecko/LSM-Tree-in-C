#include <stdio.h>
#include "Node.h"

typedef struct BlackRedTree{
    Node *root;
} MemTable;

/*
Read-only functions, passes a const pointer
so it makes sure it doesnt change the values of the MemTable
*/
void printMemTable(Node *node, int nivel, FILE *f){//Print, Left, Right -- Pre-order
    if(node != NULL){

        for(int i = 0; i < nivel; i++){
            printf("     ");
        }
        
        fprintf(f, "|-- [Nivel %d] -> %d \n", nivel, node->value);
        printMemTable(node->left, nivel + 1, f);
        printMemTable(node->right, nivel + 1, f);
    }
};

void read(const MemTable *tree){
    FILE *f;
    fopen("SSTables.txt", "w");
    if(tree == NULL || tree->root == NULL){
        fprintf(f, "Arvore Vazia");
        return;
    }
    fprintf(f, "-------------------\n");
    printMemTable(tree->root, 0, f);
    fprintf(f, "-------------------");
};

void LeftR(MemTable *tree, Node *pivot){
    //pivot desce
    //seu filho sobe (y)
    //filho esquerdo de y sobe
    Node *y = pivot->right;
    pivot->right = y->left;
    
    if (y->left != NULL) {
        y->left->parent = pivot;
    }
    
    y->parent = pivot->parent;
    
    if (pivot->parent == NULL) {
        tree->root = y; 
    } else if (pivot == pivot->parent->left) {
        pivot->parent->left = y;
    } else {
        pivot->parent->right = y;
    }
    
    y->left = pivot;
    pivot->parent = y;
};

void RightR(MemTable *tree, Node *pivot){
    //pivot desce
    //seu filho sobe (x)
    //filho direito de x sobe
    Node *x = pivot->left; // 
    pivot->left = x->right;
    
    if (x->right != NULL) {
        x->right->parent = pivot;
    }
    
    x->parent = pivot->parent;
    
    if (pivot->parent == NULL) {
        tree->root = x; 
    } else if (pivot == pivot->parent->right) {
        pivot->parent->right = x;
    } else {
        pivot->parent->left = x;
    }
    
    x->right = pivot;
    pivot->parent = x;
};


/*
Write functions
*/
void insertFixup(MemTable *tree, Node *z) {
    while (z != tree->root && z->parent->color == RED) {
        
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right; 

            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;       
                y->color = BLACK;
                z->parent->parent->color = RED; 
                z = z->parent->parent;          
            } 
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftR(tree, z); 
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightR(tree, z->parent->parent);
            }
        } 
        else {
            Node *y = z->parent->parent->left;

            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightR(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftR(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(MemTable *tree, Node *newNode) {
    Node *y = NULL;
    Node *x = tree->root;

    while (x != NULL) {
        y = x;
        if (newNode->value < x->value) {
            x = x->left;
        } else if (newNode->value > x->value) {
            x = x->right;
        } else {
            return; 
        }
    }

    newNode->parent = y;
    
    if (y == NULL) {
        tree->root = newNode;
    } else if (newNode->value < y->value) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = RED;
}
