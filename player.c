#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

// Funkce pro načtení hráčů z CSV souboru
Player *loadPlayers(const char *fileName, int *numPlayers) {
    FILE *file = fopen(fileName, "r"); // Otevření souboru pro čtení
    if (file == NULL) {
        printf("Chyba: Nelze otevrit soubor '%s'\n", fileName);
        exit(1);
    }

    // Načtení hlavičky s názvy sloupců
    char line[MAX_LINE_LENGTH];
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
        printf("Chyba: Prazdny soubor '%s'\n", fileName);
        exit(1);
    }

    // Počet hráčů
    int count = 0;
    Player *players = NULL;

    // Načtení dat hráčů
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        Player player;
        char *token = strtok(line, ",");
        strcpy(player.name, token);

        token = strtok(NULL, ",");
        strcpy(player.team, token);

        token = strtok(NULL, ",");
        strcpy(player.pos, token);

        token = strtok(NULL, ",");
        player.games = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.g = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.a = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.pts = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.plusMinus = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.pim = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.sog = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.gwg = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.ppg = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.ppa = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.shg = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.sha = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.hits = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.bs = (int) strtol(token, NULL, 10);


        // Dynamická alokace paměti pro hráče
        players = (Player *) realloc(players, (count + 1) * sizeof(Player));
        if (players == NULL) {
            printf("Chyba: Nedostatek paměti\n");
            exit(1);
        }

        // Přidání hráče do pole
        players[count] = player;
        count++;
    }

    fclose(file); // Uzavření souboru
    *numPlayers = count; // Uložení počtu načtených hráčů do proměnné numPlayers
    return players; // Vrácení pole hráčů
}

// Funkce pro uvolnění paměti alokované pro hráče
void freePlayers(Player *players) {
    free(players);
}

// Funkce pro výpis hráče
void printPlayer(Player player) {
    printf("\n\n-------------------------------------\n");
    printf("%s\n", player.name);
    printf("-------------------------------------\n");
    printf("  Tym: %s\n", player.team);
    printf("  Pozice: %s\n", player.pos);
    printf("  Bodu: %d\n", player.pts);
    printf("  Zapasu: %d\n", player.games);
    printf("  Golu: %d\n", player.g);
    printf("  Asistenci: %d\n", player.a);
    printf("  +/- body: %d\n", player.plusMinus);
    printf("  Trestne minuty: %d\n", player.pim);
    printf("  Strely na branu: %d\n", player.sog);
    printf("  Vitezne goly: %d\n", player.gwg);
    printf("  Presilovkove goly: %d\n", player.ppg);
    printf("  Presilovkove nahravky: %d\n", player.ppa);
    printf("  Goly v oslabeni: %d\n", player.shg);
    printf("  Asistence v oslabeni: %d\n", player.sha);
    printf("  Blokovanych strel: %d\n", player.bs);
    printf("  Hitu: %d\n", player.hits);
    printf("-------------------------------------\n");
}

// Funkce pro výpis TOP 5 nejproduktivnějších hráčů
void top5(Player *players, int numPlayers) {
    // Seřazení hráčů podle celkového počtu bodů (points) - algoritmus bubble sort
    for (int i = 0; i < numPlayers - 1; i++) {
        for (int j = 0; j < numPlayers - i - 1; j++) {
            if (players[j].pts < players[j + 1].pts) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    // Výpis TOP 5 hráčů
    printf("\n> TOP 5 nejproduktivnějších hráčů kanadského bodování:\n");
    printf("=======================================================\n\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. ", i + 1);
        printPlayerRow(players[i]);
    }
}

// Funkce pro nalezení nejlepšího střelce
Player *bestScorer(Player *players, int numPlayers) {
    if (numPlayers == 0) {
        // Pokud je počet hráčů 0, vrátíme NULL
        return NULL;
    }

    Player *bestScorer = &players[0]; // Předpokládáme, že první hráč je nejlepší střelec

    // Projdeme všechny hráče a porovnáme počet vstřelených branek
    for (int i = 1; i < numPlayers; i++) {
        if (players[i].g > bestScorer->g) {
            // Pokud má aktuální hráč více branek než dosud nejlepší střelec, aktualizujeme ho
            bestScorer = &players[i];
        }
    }

    // Vrátíme pointer na nejlepšího střelce
    return bestScorer;
}

// Funkce pro nalezení hráče s největším počtem trestných minut
Player *mostPenalties(Player *players, int numPlayers) {
    if (numPlayers == 0) {
        // Pokud je počet hráčů 0, vrátíme NULL
        return NULL;
    }

    Player *mostPenalties = &players[0]; // Předpokládáme, že první hráč má největší počet trestných minut

    // Projdeme všechny hráče a porovnáme počet trestných minut
    for (int i = 1; i < numPlayers; i++) {
        if (players[i].pim > mostPenalties->pim) {
            // Pokud má aktuální hráč více trestných minut než dosud hráč s největším počtem trestných minut, aktualizujeme ho
            mostPenalties = &players[i];
        }
    }

    // Vrátíme pointer na hráče s největším počtem trestných minut
    return mostPenalties;
}

// Funkce pro nalezení obránce s nejvíce asistencemi
Player *defensemanWithMostAssists(Player *players, int numPlayers) {
    Player *defenseman = NULL;
    int maxAssists = 0;

    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].pos, "D") == 0 && players[i].a > maxAssists) {
            maxAssists = players[i].a;
            defenseman = &players[i];
        }
    }

    return defenseman;
}

void searchPlayerByName(Player *players, int numPlayers, const char *namePart) {
    int found = 0; // Počet nalezených hráčů
    printf("\n> Nalezeni hraci s jmenem obsahujicim '%s':\n", namePart);
    printf("===================================================\n\n");
    for (int i = 0; i < numPlayers; i++) {
        if (strstr(players[i].name, namePart) != NULL) {
            printPlayerRow(players[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("\n> Zadny hrac s timto jmenem nebyl nalezen.\n");
    }
}

// Funkce pro zjednodušený výpis hráče
void printPlayerRow(Player player) {
    printf("%-30s %-5s Z: %3d B: %3d G: %3d A: %3d\n", player.name, player.team, player.games, player.pts, player.g,
           player.a);
}

int sortPlayers(Player *players, int numPlayers, SortCriteria sortCriteria, SortOrder sortOrder) {
    switch (sortCriteria) {
        case NAME:
            qsort(players, numPlayers, sizeof(Player), sortOrder == ASCENDING ? compareByNameAsc : compareByNameDesc);
            break;
        case GAMES_PLAYED:
            qsort(players, numPlayers, sizeof(Player), sortOrder == ASCENDING ? compareByGamesAsc : compareByGamesDesc);
            break;
        case GOALS:
            qsort(players, numPlayers, sizeof(Player), sortOrder == ASCENDING ? compareByGoalsAsc : compareByGoalsDesc);
            break;
        case ASSISTS:
            qsort(players, numPlayers, sizeof(Player),
                  sortOrder == ASCENDING ? compareByAssistAsc : compareByAssistDesc);
            break;
        default:
            return 0;
    }
}

int compareByNameAsc(const void *p1, const void *p2) {
    Player *player1 = (Player *) p1;
    Player *player2 = (Player *) p2;
    return strcmp(player1->name, player2->name);
}

int compareByNameDesc(const void *p1, const void *p2) {
    Player *player1 = (Player *) p1;
    Player *player2 = (Player *) p2;
    return strcmp(player2->name, player1->name);
}

int compareByGamesAsc(const void *p1, const void *p2) {
    Player *player1 = (Player *) p1;
    Player *player2 = (Player *) p2;
    return player1->games - player2->games;
}

int compareByGamesDesc(const void *p1, const void *p2) {
    Player *player1 = (Player *) p1;
    Player *player2 = (Player *) p2;
    return player2->games - player1->games;
}

int compareByGoalsAsc(const void *p1, const void *p2) {
    Player *player1 = (Player *) p1;
    Player *player2 = (Player *) p2;
    return player1->g - player2->g;
}

int compareByGoalsDesc(const void *p1, const void *p2) {
    Player *player1 = (Player *) p1;
    Player *player2 = (Player *) p2;
    return player2->g - player1->g;
}

int compareByAssistAsc(const void *p1, const void *p2) {
    Player *player1 = (Player *) p1;
    Player *player2 = (Player *) p2;
    return player1->a - player2->a;
}

int compareByAssistDesc(const void *p1, const void *p2) {
    Player *player1 = (Player *) p1;
    Player *player2 = (Player *) p2;
    return player2->a - player1->a;
}

void printTop10(Player *players, int numPlayers) {
    printf("\n---- TOP 10 ----\n");
    for (int i = 0; i < 10 && i < numPlayers; i++) {
        printf("%2d. ", i + 1);
        printPlayerRow(players[i]);
    }
}