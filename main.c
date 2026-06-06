#include <stdio.h>
#include <stdlib.h>
#include "./MemTable/MemTable.h"
#include "./MemTable/Node.h"
#include "./SSTable/sstable.h"

int main(){
    MemTable *memtable = createMemTable();

    Node *node1 = createNode("Pikachu");
    Node *node2 = createNode("Hitmonlee");
    insert(memtable, node1);
    insert(memtable, node2);

    flush(memtable);
    
    Node *node3 = createNode("Raichu");
    Node *node4 = createNode("Hitmonchan");

    insert(memtable, node3);
    insert(memtable, node4);

    readMemTable(memtable);
    flush(memtable);

    return 0;
}