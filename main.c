#include <stdio.h>
#include <stdlib.h>
#include "./MemTable/MemTable.h"
#include "./MemTable/Node.h"
#include "./SSTable/sstable.h"

int main(){
    MemTable *memtable = createMemTable();

    printf("Inicializando os nodes\n");
    Node *node1 = createNode("Lucario");
    Node *node2 = createNode("Gyrados");
    Node *node3 = createNode("Tiranitar");
    Node *node4 = createNode("Doublade");
    Node *node5 = createNode("Arceus");

    printf("inserindo os nodes\n");
    insert(memtable, node1);
    insert(memtable, node2);
    insert(memtable, node3);
    insert(memtable, node4);
    insert(memtable, node5);

    //read(memtable);

    
    FILE *f = fopen("SSTable.txt", "w+");
    flush(memtable->root, f);
    

    //searchSSTablebyName(f, "Doublade");
    searchSSTablebyIndex(f, 1);
    fclose(f);


    return 0;
}