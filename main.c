#include <stdio.h>
#include <stdlib.h>
#include "./SSTable/SSTable.h"
#include "./MemTable/MemTable.h"
#include "./MemTable/Node.h"

void loadLastId() {
    DIR *dir = opendir("./SSTables");
    if (dir == NULL) {
        return;
    }

    struct dirent *entry;
    int last_id = 0;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        int currentNumber = 0;
        if (sscanf(entry->d_name, "SSTable%d.txt", &currentNumber) == 1) {
            char filename[100];
            sprintf(filename, "./SSTables/%s", entry->d_name);
            FILE *f = fopen(filename, "r");
            if (f != NULL) {
                char line[100];
                int file_max_id = 0;
                while (fgets(line, sizeof(line), f)) {
                    int id;
                    if (sscanf(line, "%d", &id) == 1) {
                        if (id > file_max_id) {
                            file_max_id = id;
                        }
                    }
                }
                fclose(f);
                if (file_max_id > last_id) {
                    last_id = file_max_id;
                }
            }
        }
    }
    closedir(dir);

    setGlobalIndex(last_id);
    printf("ID dos proximos pokemons atualizado para iniciar em: %d\n", last_id + 1);
}

int main(){
    loadLastId();
    MemTable *memtable = createMemTable();

    int option = 1;
    int id;

    while(option >= 1 && option <= 5){
        printf("------------------------------\n");

        printf("1. Criar node\n");
        printf("2. Printar Arvore\n");
        printf("3. Descarregar Arvore\n");
        printf("4. Buscar node\n");
        printf("5. Deletar node\n");
        printf("6. Encerrar aplicacao\n");
        printf("------------------------------\n");
        printf("Selecione uma opcao: ");
        scanf(" %d", &option);
        
        switch(option){
            case 1:
                printf("Digite o nome do pokemon: ");
                char pokemonName[20];
                scanf("%s", pokemonName);
                Node *node = createNode(pokemonName);
                printf("Node criado:\n");
                printf("[%d]", node->pokemon->index);
                printf("%s\n", node->pokemon->name);
                insert(memtable, node);
                break;
            case 2:
                readMemTable(memtable);
                break;
            case 3:
                printf("Descarregando memtable...\n");
                flush(memtable);
                break;
            case 4:
                printf("Digite o id do pokemon a ser buscado\n");
                scanf("%d", &id);
                searchMemTable(memtable->root, id);
                break;
            case 5:
                printf("Digite o id do pokemon a ser deletado\n");
                scanf("%d", &id);
                delete(memtable, id);
                break;
        }
    }

    return 0;
}