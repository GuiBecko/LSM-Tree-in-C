#include <stdio.h>
#include <stdlib.h>
#include "./MemTable/MemTable.h"
#include "./MemTable/Node.h"
#include "./SSTable/sstable.h"

int main(){
    MemTable *memtable = createMemTable();

    Node *node1 = createNode("Pikachu");
    Node *node2 = createNode("Charizard"); 

    insert(memtable, node1);
    insert(memtable, node2);
    
    delete(memtable, 1);

    read(memtable);
    FILE *f = fopen("SSTable.txt", "w+");
    flush(memtable->root, f);
    fclose(f);
    return 0;
}