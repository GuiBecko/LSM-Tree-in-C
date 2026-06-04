#include <stdio.h>
#include <stdlib.h>
#include "./MemTable/MemTable.h"
#include "./MemTable/Node.h"

int main(){
    MemTable *memtable = createMemTable();

    printf("Inicializando os nodes\n");
    Node *node1 = createNode(-3);
    Node *node2 = createNode(0);
    Node *node3 = createNode(99);
    Node *node4 = createNode(36);

    
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