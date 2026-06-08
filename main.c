#include <stdio.h>
#include <stdlib.h>
#include "./MemTable/MemTable.h"
#include "./MemTable/Node.h"
#include "./SSTable/sstable.h"

int main(){
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
                searchMemTableByID(memtable, id);
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