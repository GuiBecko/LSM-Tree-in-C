#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include "Node.h"

#define boolean int
#define true  1
#define false  0

typedef struct BlackRedTree{
    Node *root;
} MemTable;

MemTable* createMemTable(){
    printf("Inicializando a arvore\n");
    MemTable *memtable = (MemTable*) malloc(sizeof(MemTable));
    memtable->root = NULL;
    return memtable;
}

/*
Read-only functions, passes a const pointer
so it makes sure it doesnt change the values of the MemTable
*/
void printMemTable(Node *node, int nivel){//Print, Left, Right -- Pre-order
    if(node != NULL){

        for(int i = 0; i < nivel; i++){
            printf("     ");
        }

        printf("|-- [Nivel %d] -> [%d] %s \n", nivel, node->pokemon->index, node->pokemon->name);
        printMemTable(node->left, nivel + 1);
        printMemTable(node->right, nivel + 1);
    }
}

void readMemTable(const MemTable *tree){
    if(tree == NULL || tree->root == NULL){
        printf("Arvore Vazia\n");
        return;
    }
    printf("-------------------\n");
    printMemTable(tree->root, 0);
    printf("-------------------\n");
};

int searchMemTableHelper(Node *node, int id){
    if(node != NULL){
        if(node->pokemon->index == id){
            printf("Node encontrado na memtable:\n");
            printf("[%d] - %s\n", node->pokemon->index, node->pokemon->name); 
            return 1;
        }else{
            if(node->pokemon->index > id){
                return searchMemTableHelper(node->left, id);
            }else{
                return searchMemTableHelper(node->right, id);
            }
        }
    }
    return 0;
}

void searchMemTable(Node *node, int id){
    if(!searchMemTableHelper(node, id)){
        searchSSTable(id);
    }
}
/*
Write functions
*/

void flushHelper(Node* node, FILE *f){ //Left, Print, Right - In-Order
    if(node != NULL){
        flushHelper(node->left, f);
        fprintf(f, "%d %s\n", node->pokemon->index, node->pokemon->name);
        flushHelper(node->right, f);
        free(node->pokemon);
        free(node);
    }
}

void flush(MemTable *memtable){ 
    DIR *dir = opendir("./SSTables");
    struct dirent *entry;

    if(dir == NULL){
        printf("Could not find SSTables directory");
        return;
    }

    int max_sstable_number = 0;
    while((entry = readdir(dir)) != NULL){

        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }

        char currentNumberStr[20] = {0};
        int j = 0;

        // Extrai apenas os dígitos do nome do arquivo
        for(int i = 0; entry->d_name[i] != '\0'; i++){
            if(isdigit((unsigned char)entry->d_name[i])){
                currentNumberStr[j] = entry->d_name[i];
                j++;
            }
        }

        if(j > 0){
            int currentNumber = atoi(currentNumberStr);
            if(currentNumber > max_sstable_number){
                max_sstable_number = currentNumber;
            }
        }
    }
    closedir(dir);

    int number = max_sstable_number + 1;
    char newFileName[50];
    sprintf(newFileName, "./SSTables/SSTable%d.txt", number);


    FILE *f = fopen(newFileName, "w");
    Node *node = memtable->root;
    flushHelper(node, f);
    fclose(f);
    memtable->root = NULL;
} 

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
}



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
        if (newNode->pokemon->index < x->pokemon->index) {
            x = x->left;
        } else if (newNode->pokemon->index > x->pokemon->index) {
            x = x->right;
        } else {
            return; 
        }
    }
    
    newNode->parent = y;
    
    if (y == NULL) {
        tree->root = newNode;
    } else if (newNode->pokemon->index < y->pokemon->index) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = RED;
    insertFixup(tree, newNode);
}

void delete(MemTable *memtable, int deleteID){
    Node *x = memtable->root;

    while(x != NULL){
        if(deleteID > x->pokemon->index){
            x = x->right;
        }else if(deleteID < x->pokemon->index){
            x = x->left;
        }else{
            x->isDeleted = true;
            strcpy(x->pokemon->name, " TB ");
            return;
        }
    }

    Node *tombstone = createTombstone(deleteID);
    insert(memtable, tombstone);
}