#include <stdio.h>
#include "MemTable/MemTable.h"

const char *pokemons[] = {
    /* Geração I (Kanto) */
    "Bulbasaur", "Ivysaur", "Venusaur",
    "Charmander", "Charmeleon", "Charizard",
    "Squirtle", "Wartortle", "Blastoise",
    "Caterpie", "Metapod", "Butterfree",
    "Weedle", "Kakuna", "Beedrill",
    "Pidgey", "Pidgeotto", "Pidgeot",
    "Rattata", "Raticate",
    "Spearow", "Fearow",
    "Ekans", "Arbok",
    "Pikachu", "Raichu",
    "Sandshrew", "Sandslash",
    "NidoranF", "Nidorina", "Nidoqueen",
    "NidoranM", "Nidorino", "Nidoking",
    "Clefairy", "Clefable",
    "Vulpix", "Ninetales",
    "Jigglypuff", "Wigglytuff",
    "Zubat", "Golbat",
    "Oddish", "Gloom", "Vileplume",
    "Paras", "Parasect",
    "Venonat", "Venomoth",
    "Diglett", "Dugtrio",
    "Meowth", "Persian",
    "Psyduck", "Golduck",
    "Mankey", "Primeape",
    "Growlithe", "Arcanine",
    "Poliwag", "Poliwhirl", "Poliwrath",
    "Abra", "Kadabra", "Alakazam",
    "Machop", "Machoke", "Machamp",
    "Bellsprout", "Weepinbell", "Victreebel",
    "Tentacool", "Tentacruel",
    "Geodude", "Graveler", "Golem",
    "Ponyta", "Rapidash",
    "Slowpoke", "Slowbro",
    "Magnemite", "Magneton",
    "Farfetch'd",
    "Doduo", "Dodrio",
    "Seel", "Dewgong",
    "Grimer", "Muk",
    "Shellder", "Cloyster",
    "Gastly", "Haunter", "Gengar",
    "Onix",
    "Drowzee", "Hypno",
    "Krabby", "Kingler",
    "Voltorb", "Electrode",
    "Exeggcute", "Exeggutor",
    "Cubone", "Marowak",
    "Hitmonlee", "Hitmonchan",
    "Lickitung",
    "Koffing", "Weezing",
    "Rhyhorn", "Rhydon",
    "Chansey",
    "Tangela",
    "Kangaskhan",
    "Horsea", "Seadra",
    "Goldeen", "Seaking",
    "Staryu", "Starmie",
    "Mr. Mime",
    "Scyther",
    "Jynx",
    "Electabuzz",
    "Magmar",
    "Pinsir",
    "Tauros",
    "Magikarp", "Gyarados",
    "Lapras",
    "Ditto",
    "Eevee", "Vaporeon", "Jolteon", "Flareon",
    "Porygon",
    "Omanyte", "Omastar",
    "Kabuto", "Kabutops",
    "Aerodactyl",
    "Snorlax",
    "Articuno", "Zapdos", "Moltres",
    "Dratini", "Dragonair", "Dragonite",
    "Mewtwo", "Mew",

    /* Geração II (Johto) */
    "Chikorita", "Bayleef", "Meganium",
    "Cyndaquil", "Quilava", "Typhlosion",
    "Totodile", "Croconaw", "Feraligatr",
    "Sentret", "Furret",
    "Hoothoot", "Noctowl",
    "Ledyba", "Ledian",
    "Spinarak", "Ariados",
    "Crobat",
    "Chinchou", "Lanturn",
    "Pichu",
    "Cleffa",
    "Igglybuff",
    "Togepi", "Togetic",
    "Natu", "Xatu",
    "Mareep", "Flaaffy", "Ampharos",
    "Bellossom",
    "Marill", "Azumarill",
    "Sudowoodo",
    "Politoed",
    "Hoppip", "Skiploom", "Jumpluff",
    "Aipom",
    "Sunkern", "Sunflora",
    "Yanma",
    "Wooper", "Quagsire",
    "Espeon", "Umbreon",
    "Murkrow",
    "Slowking",
    "Misdreavus",
    "Unown",
    "Wobbuffet",
    "Girafarig",
    "Pineco", "Forretress",
    "Dunsparce",
    "Gligar",
    "Steelix",
    "Snubbull", "Granbull",
    "Qwilfish",
    "Scizor",
    "Shuckle",
    "Heracross",
    "Sneasel",
    "Teddiursa", "Ursaring",
    "Slugma", "Magcargo",
    "Swinub", "Piloswine",
    "Corsola",
    "Remoraid", "Octillery",
    "Delibird",
    "Mantine",
    "Skarmory",
    "Houndour", "Houndoom",
    "Kingdra",
    "Phanpy", "Donphan",
    "Porygon2",
    "Stantler",
    "Smeargle",
    "Tyrogue",
    "Hitmontop",
    "Smoochum",
    "Elekid",
    "Magby",
    "Miltank",
    "Blissey",
    "Raikou", "Entei", "Suicune",
    "Larvitar", "Pupitar", "Tyranitar",
    "Lugia", "Ho-Oh",
    "Celebi"
};    
const int TOTAL_POKEMONS = sizeof(pokemons) / sizeof(pokemons[0]);

#include <time.h>
int main(){
    MemTable *memtable = createMemTable();
    
    // Usamos um fator pequeno para o Valgrind não demorar horas
    int fator_mult = 100; 
    
    printf("1. Inserindo dados...\n");
    for(int j = 0; j < fator_mult; j++){
        for(int i = 0; i < TOTAL_POKEMONS; i++){
            insert(memtable, createNode(pokemons[i]));
        }
    }
    
    printf("2. Fazendo Flush e libertando nós...\n");
    flush(memtable); // O seu flush deve estar a fazer a travessia Post-Order e dar free() aos nós!

    printf("3. Libertando a MemTable principal...\n");
    free(memtable);  // Liberta a estrutura base que criámos na 1ª linha

    return 0; // O programa tem de terminar para o Valgrind fazer o relatório final
}
/*Tempo de Inserção
n          | tempo
25.100     | 0.012s
251.000    | 0.13s
2.510.000  | 1.358
25.100.000 | ~10s
*/

/* Tempo de Busca (pior caso) (Memtable)
n          | tempo | operações 
25.100     | 0s    | 14
251.000    | 0.003s      | 17
2.510.000  | 0.003s      | 21
25.100.000 | 0s    | 24
*/

/*Tempo de Busca (pior caso) (SSTable)
n          | tempo     | operações 
25.100     | 0s        | 14
251.000    | 0s        | 17
2.510.000  | 0s        | 21
25.100.000 | 0.002s    | 24
*/

/* Tempo do flush
n          | tempo
25.100     | 0.02s
251.000    | 0.17s
2.510.000  | 1.75s
25.100.000 | ~14s
*/