#ifndef SSTABLE_H
#define SSTABLE_H

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>

#include "Index.h"

void searchSSTable(int id) {
    if (sparseIndexCount == 0) {
        printf("Nenhum dado no disco.\n");
        return;
    }

    // 1. Busca Binária O(log n) NA MEMÓRIA RAM (Piscou, achou)
    int l = 0;
    int r = sparseIndexCount - 1;
    sparseIndexEntry *found_entry = NULL;

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (sparseIndex[m].minKey == id) {
            found_entry = &sparseIndex[m];
            break;
        } else if (sparseIndex[m].minKey < id) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    if (found_entry == NULL) {
        printf("Node nao encontrado.\n");
        return;
    }

    // 2. O "Tiro Certeiro" no Disco O(1)
    char filename[50];
    sprintf(filename, "./SSTables/SSTable%d.dat", found_entry->fileNum); 
    FILE *f = fopen(filename, "rb"); // "rb" porque o arquivo é binário (.dat)

    if (f != NULL) {
        // Pula instantaneamente para o byte exato onde o Node começa
        fseek(f, found_entry->offset, SEEK_SET);

        int disk_key;
        int disk_rowsize;

        // Lemos como foi gravado no flushHelper: primeiro a key, depois o rowsize
        fread(&disk_key, sizeof(int), 1, f);
        fread(&disk_rowsize, sizeof(int), 1, f);

        // 3. Verificamos a lápide lendo o rowsize gravado no disco
        if (disk_rowsize == 0) {
            printf("Node deletado (Tombstone encontrada) na SSTable%d!\n", found_entry->fileNum);
        } else {
            // Se não é lápide, alocamos espaço e lemos a string de dados
            char *linha = (char*) malloc(disk_rowsize + 1);
            fread(linha, disk_rowsize, 1, f);
            linha[disk_rowsize] = '\0'; // Adiciona terminador nulo por segurança

            printf("Encontrado na SSTable%d: [%d] %s\n", found_entry->fileNum, disk_key, linha);
            
            free(linha); // Evita vazamento de memória
        }
        
        fclose(f);
    } else {
        printf("Falha ao abrir a SSTable%d.\n", found_entry->fileNum);
    }
}

#endif