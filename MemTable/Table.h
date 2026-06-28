#ifndef TABLE_H
#define TABLE_H
#include "MemTable.h"

typedef struct Table {
    char name[20];
    MemTable *memtable;
    char database[20];
    char schema[20];
} Table;

#endif