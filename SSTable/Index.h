#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int minKey;  //first key
    long offset; //first key byte
    int fileNum; //SSTable number
} sparseIndexEntry;

sparseIndexEntry *sparseIndex = NULL;
int sparseIndexCount = 0;
int sparseIndexCapacity = 0;

void addSparseIndex(int minKey, long offset, int fileNum){
    if(sparseIndexCount >= sparseIndexCapacity){
        sparseIndexCapacity = sparseIndexCapacity == 0 ? 100 : sparseIndexCapacity * 2;
        sparseIndex = (sparseIndexEntry*) realloc(sparseIndex, sparseIndexCapacity * sizeof(sparseIndexEntry));
    }
    sparseIndex[sparseIndexCount].minKey = minKey;
    sparseIndex[sparseIndexCount].offset = offset;
    sparseIndex[sparseIndexCount].fileNum = fileNum;

    sparseIndexCount++;
}

#endif