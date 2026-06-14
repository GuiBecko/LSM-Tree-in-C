#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include "./../MemTable/Pokemon.h"

void searchSSTable(int id){
    DIR *dir = opendir("./SSTables");
    if (dir == NULL) {
        printf("Diretório SSTables não encontrado ou vazio.\n");
        return;
    }

    // 1. Encontra o número da SSTable mais recente
    int max_sstable_number = 0;
    struct dirent *entry;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char currentNumberStr[20] = {0};
        int j = 0;
        for (int i = 0; entry->d_name[i] != '\0'; i++) {
            if (isdigit((unsigned char)entry->d_name[i])) {
                currentNumberStr[j++] = entry->d_name[i];
            }
        }
        if (j > 0) {
            int currentNumber = atoi(currentNumberStr);
            if (currentNumber > max_sstable_number) {
                max_sstable_number = currentNumber;
            }
        }
    }
    closedir(dir);

    // 2. Loop Reverso: Da SSTable mais nova até a SSTable 1
    for (int i = max_sstable_number; i >= 1; i--) {
        char filename[50];
        sprintf(filename, "./SSTables/SSTable%d.txt", i);

        FILE *f = fopen(filename, "r"); 
        if (f == NULL) continue; 

        printf("Buscando na SSTable%d...\n", i);

        // 3. Busca Binária no Disco
        fseek(f, 0, SEEK_END);
        long r = ftell(f);
        long l = 0;

        while (r >= l) {
            long m = l + (r - l) / 2;
            fseek(f, m, SEEK_SET);

            // Truque de alinhamento: avança até a próxima linha se cairmos no meio de uma palavra
            if (m != 0) {
                int ch;
                while ((ch = fgetc(f)) != '\n' && ch != EOF) {}
            }

            char content[1000];
            if (!fgets(content, 1000, f)) {
                // Se não conseguiu ler nada, o cursor bateu no final do arquivo (EOF)
                r = m - 1; 
                continue;
            }

            int index;
            char pokemonName[30];
            sscanf(content, "%d %s", &index, pokemonName);

            // Avalia o resultado da busca
            if (index == id) {
                if (strcmp(pokemonName, "TB") == 0) {
                    // O escudo da Tombstone funcionou! Achamos a lápide.
                    printf("Pokemon deletado (Tombstone encontrada na SSTable%d)!\n", i);
                } else {
                    printf("Encontrado na SSTable%d: [%d] %s\n", i, index, pokemonName);
                }
                fclose(f);
                return; // Achou o dado ou a lápide, encerra a função imediatamente!
                
            } else if (index < id) {
                // Precisa ir para a direita. ftell(f) nos dá a posição exata após o fgets
                l = ftell(f); 
            } else {
                // Precisa ir para a esquerda
                r = m - 1;
            }
        }
        fclose(f); // Fecha o arquivo atual e vai para a SSTable mais antiga (i--)
    }

    // Se o loop terminar e não achar em NENHUMA SSTable
    printf("Pokemon nao encontrado em nenhuma SSTable.\n");
}
