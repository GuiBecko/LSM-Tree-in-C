#include <stdio.h>
#include <stdlib.h>
#include "./SSTable/SSTable.h"
#include "./MemTable/MemTable.h"
#include "./MemTable/Node.h"

#include "SSTable/Index.h" 

int compareIndex(const void *a, const void *b) {
    return (((sparseIndexEntry*)a)->minKey - (((sparseIndexEntry*)b)->minKey));
}

void bootDatabase() {
    DIR *dir = opendir("./SSTables");
    if (dir == NULL) return;

    struct dirent *entry;
    int last_id = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        int file_num = 0;
        if (sscanf(entry->d_name, "SSTable%d.dat", &file_num) == 1) {
            char filename[100];
            sprintf(filename, "./SSTables/%s", entry->d_name);
            FILE *f = fopen(filename, "rb");
            
            if (f != NULL) {
                int current_key;
                int current_rowsize;

                while (fread(&current_key, sizeof(int), 1, f) == 1) {
                    fread(&current_rowsize, sizeof(int), 1, f);
                    
                    long data_offset = ftell(f); 
                    
                    addSparseIndex(current_key, data_offset, file_num);

                    if (current_key > last_id) {
                        last_id = current_key;
                    }
                    
                    if (current_rowsize > 0) {
                        fseek(f, current_rowsize, SEEK_CUR);
                    }
                }
                fclose(f);
            }
        }
    }
    closedir(dir);

    if (sparseIndexCount > 0) {
        qsort(sparseIndex, sparseIndexCount, sizeof(sparseIndexEntry), compareIndex);
    }

    setGlobalIndex(last_id);
    printf("Banco de Dados inicializado. %d registros indexados na RAM.\n", sparseIndexCount);
}

int main() {
    bootDatabase();
    MemTable *memtable = createMemTable();

    int option = 1;
    int id;

    while (option >= 1 && option <= 5) {
        printf("------------------------------\n");
        printf("1. Criar node\n");
        printf("2. Printar Arvore\n");
        printf("3. Descarregar Arvore (Flush)\n");
        printf("4. Buscar node\n");
        printf("5. Deletar node\n");
        printf("6. Encerrar aplicacao\n");
        printf("------------------------------\n");
        printf("Selecione uma opcao: ");
        scanf(" %d", &option);
        
        switch (option) {
            case 1: {
                char buffer[256];
                printf("Digite o dado do novo registro (ex: Pikachu): ");
                // O espaço antes do % evita que o scanf pule o input por causa de 'enters' pendentes
                // O [^\n] faz com que ele leia a frase inteira, incluindo espaços, até o usuário dar enter
                scanf(" %[^\n]", buffer); 

                // Aloca dinamicamente apenas o tamanho necessário para salvar a string
                int rowsize = strlen(buffer);
                char *data = (char*) malloc(rowsize + 1); 
                strcpy(data, buffer);

                // Cria o nó e insere na árvore Rubro-Negra (MemTable)
                Node *newNode = createNode(data, rowsize);
                insert(memtable, newNode);
                
                printf("-> Registro inserido com sucesso! ID gerado: [%d]\n", newNode->key);
                break;
            }
            case 2:
                readMemTable(memtable);
                break;
            case 3:
                printf("Descarregando memtable no disco...\n");
                flush(memtable);
                printf("-> Flush concluido e MemTable resetada!\n");
                break;
            case 4:
                printf("Digite o ID da linha a ser buscada: ");
                scanf("%d", &id);
                searchMemTable(memtable->root, id);
                break;
            case 5:
                printf("Digite o ID da linha a ser deletada: ");
                scanf("%d", &id);
                delete(memtable, id);
                printf("-> Comando de delecao executado para o ID [%d].\n", id);
                break;
            case 6:
                printf("Encerrando o banco de dados...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                // Força o loop a continuar rodando caso o usuário digite um número errado
                option = 1; 
                break;
        }
    }

    // Libera a estrutura da árvore principal antes de sair
    free(memtable);
    return 0;
}