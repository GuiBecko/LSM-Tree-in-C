#include <stdio.h>
#include <stdlib.h>
#include "./MemTable/MemTable.h"
#include "./MemTable/Node.h"

int main(){
    MemTable *memtable = createMemTable();

    printf("Inicializando os nodes\n");
    Node *node1 = createNode("Lucario");
    Node *node2 = createNode("Gyrados");
    Node *node3 = createNode("Tiranitar");
    Node *node4 = createNode("Doublade");

    
    printf("Inserindo na arvore node 1\n");
    insert(memtable, node1);
    printf("Inserindo na arvore node 2\n");
    insert(memtable, node2);
    printf("Inserindo na arvore node 3\n");
    insert(memtable, node3);
    printf("Inserindo na arvore node 4\n");
    insert(memtable, node4);
    
    read(memtable);

    return 0;
}