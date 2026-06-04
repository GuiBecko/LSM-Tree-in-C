#include <stdio.h>
#include <string.h>
#include "./../MemTable/Pokemon.h"

void searchSSTablebyName(FILE *f, char *searchName){
    rewind(f);
    int flag = 0;
    char content[1000];
    int index;
    char pokemonName[30];

    while(fgets(content, 1000, f)){
        sscanf(content, "%d %s", &index, pokemonName);

        if(!strcmp(searchName, pokemonName)){
            printf("%d\n", index);
            flag = 1;
            break;
        }
    }
    if(!flag){
        printf("Pokemon nao encontrado!\n");
    }
    rewind(f);
}

void searchSSTablebyIndex(FILE *f, int searchIndex){
    rewind(f);
    char content[1000];
    int index;
    char pokemonName[30];
    int flag = 0;

    fseek(f, 0 ,SEEK_END);

    long r = ftell(f);
    long l = 0;

    while(r > l){
        long m = l + (r - l) / 2;
        fseek(f, m , SEEK_SET);

        if (m != 0) {
            int ch;
            while ((ch = fgetc(f)) != '\n' && ch != EOF) {
                // Moves the pointer to the end of the line or the end of the file
                // fgetc(f) reads the byteit is and moves to the nex
            }
        }

        fgets(content, 1000, f);
        sscanf(content, "%d %s", &index, pokemonName);
        
        if(index > searchIndex){
            r = m - 1;
        }else if(index < searchIndex){
            l = m + 1;
        }else{
            printf("%s\n", pokemonName);
            flag = 1;
            break;
        }
    }

    if(flag == 0){
        printf("Pokemon nao encontrado\n");
    }

    rewind(f);
}