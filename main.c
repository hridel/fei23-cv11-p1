#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"

void printMenu();

void printSortMenu();

int main() {
    Player *players = NULL;
    int numPlayers = 0;
    Player *selectedPlayer;

    char userInput[100]; // Předpokládáme, že uživatel zadá nejvýše 99 znaků
    int menuChoice;
    char *invalidChoice;

    players = loadPlayers("data/stats.csv", &numPlayers); // Volání funkce pro načtení hráčů

    while (1) {
        printMenu();
        printf("Vyberte akci: ");

        fgets(userInput, sizeof(userInput), stdin); // Načtení vstupu jako řetězce
        userInput[strcspn(userInput, "\n")] = '\0'; // Odstranění znaku nového řádku z vstupu
        menuChoice = (int) strtol(userInput, &invalidChoice, 10); // Převedení řetězce na celé číslo

        if (userInput[0] == '\0' || *invalidChoice != '\0') {
            printf("Zadali jste neplatne cele cislo.\n");
        } else {
            switch (menuChoice) {
                case 1:
                    top5(players, numPlayers); // Volání funkce pro výpis top 5 hráčů
                    break;
                case 2:
                    selectedPlayer = bestScorer(players, numPlayers); // Volání funkce pro nalezení nejlepšího střelce
                    printPlayer(*selectedPlayer);
                    break;
                case 3:
                    selectedPlayer = mostPenalties(players,
                                                   numPlayers); // Volání funkce pro nalezení hráče s nejvíce tresty
                    printPlayer(*selectedPlayer);
                    break;
                case 4:
                    selectedPlayer = defensemanWithMostAssists(players,
                                                               numPlayers); // Volání funkce pro nalezení obránce s nejvíce asistencemi
                    printPlayer(*selectedPlayer);
                    break;
                case 5:
                    printf("Zadejte hledane jmeno hrace: ");
                    fgets(userInput, sizeof(userInput), stdin); // Načtení vstupu jako řetězce
                    userInput[strcspn(userInput, "\n")] = '\0'; // Odstranění znaku nového řádku z vstupu
                    searchPlayerByName(players, numPlayers, userInput);
                    break;
                case 6:
                    printSortMenu();
                    printf("Vyberte kriterium pro razeni: ");
                    fgets(userInput, sizeof(userInput), stdin);
                    userInput[strcspn(userInput, "\n")] = '\0';
                    SortCriteria sortCriteria = (SortCriteria) strtol(userInput, &invalidChoice, 10);
                    if (userInput[0] == '\0' || *invalidChoice != '\0') {
                        printf("Zadali jste neplatne cele cislo.\n");
                        break;
                    }
                    printf("Vyberte smer razeni (0 - vzestupne, 1 - sestupne): ");
                    fgets(userInput, sizeof(userInput), stdin);
                    userInput[strcspn(userInput, "\n")] = '\0';
                    SortOrder sortOrder = (SortOrder) strtol(userInput, &invalidChoice, 10);
                    if (userInput[0] == '\0' || *invalidChoice != '\0') {
                        printf("Zadali jste neplatne cele cislo.\n");
                        break;
                    }
                    sortPlayers(players, numPlayers, sortCriteria, sortOrder);
                    printTop10(players, numPlayers);
                    break;
                case 0:
                    freePlayers(players); // Volání funkce pro uvolnění paměti pro hráče
                    printf("Program ukoncen.\n");
                    return 0;
                default:
                    printf("Neplatna volba. Zvolte znovu.\n");
                    break;
            }
        }
    }
}

// Funkce pro tisk menu
void printMenu() {
    printf("\n---- MENU ----\n");
    printf("1 - TOP 5 (nejproduktivnejsi hraci kanadskeho bodovani)\n");
    printf("2 - Nejlepsi strelec\n");
    printf("3 - Nejtretanejsi hrac\n");
    printf("4 - Obrance s nejvyssim poctem asistenci\n");
    printf("5 - Hledat hrace podle jmena\n");
    printf("6 - Serazeni hracu\n");
    printf("0 - Ukoncit program\n");
}

void printSortMenu() {
    printf("\n---- SORT MENU ----\n");
    printf("0 - Razeni podle jmena\n");
    printf("1 - Razeni podle poctu zapasu\n");
    printf("2 - Razeni podle poctu golu\n");
    printf("3 - Razeni podle poctu asistenci\n");
}