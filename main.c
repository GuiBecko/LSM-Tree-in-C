#include <stdio.h>
#include <stdlib.h>
#include "MemTable.h"
#include "Node.h"

int main(){
    MemTable *memtable = (MemTable*) malloc(sizeof(MemTable));
    Node *node1 = (Node*) malloc(sizeof(Node));
    Node *node2 = (Node*) malloc(sizeof(Node));
    Node *node3 = (Node*) malloc(sizeof(Node));

    node1->value = 3;
    node2->value = 4;
    node3->value = 5;

    insert(memtable, node1);
    insert(memtable, node2);
    insert(memtable, node3);

    read(memtable);
    free(node1);
    free(node2);
    free(memtable);

    return 0;
}