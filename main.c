#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stos.h"
#include "labir.h"
#include "graficz.h"
#include "graf.h"


//funkcja do zwolnienia pamięci stosu
void zwolnij_stos(int size, int **move) {
    for (int i = 0; i < size; i++) {
        free(move[i]);
    }
    free(move);
}

int main() {
    int size;
    int wspol_y = 0;
    int wspol_x = 0;
    int punkt_koncowy = size - 1;
    srand(time(NULL));

    //otrzymanie informacji od użytkownika o rozmiarach labiryntu 
    
    printf("Podaj rozmiar labiryntu: "); 
    fflush(stdout);
    scanf("%d", &size);
    printf("\n"); fflush(stdout);

    //inicjalizacja 
    maze **labirynt = malloc(size * sizeof (maze *));
    if (labirynt == NULL) {
        printf("Nie udalo się stworzyć labirynt. Błąd pamięci.\n"); 
        fflush(stdout);
        return 1;
    }
    inicjacja(&labirynt, size);

    // tworzenie tablicy z dostępnymi ruchami oraz wypelnienie jej zawartości -1
    int size2 = size * size;
    int **move = (int **)malloc(size2 * sizeof(int *));
    if (move == NULL) {
        printf("Nie udalo się stworzyć labirynt. Błąd pamięci.\n"); 
        fflush(stdout);
        return 1;
    }
    for (int i = 0; i < size2; i++) {
        move[i] = (int *)malloc(2 * sizeof(int));
        if (move[i] == NULL) {
            printf("Nie udalo się stworzyć labirynt. Błąd pamięci.\n"); 
            fflush(stdout);
            return 1;
        }
    }
    for (int i = 0; i < size2; i++) {
        move[i][0] = -1;
        move[i][1] = -1;
    }

    losowa_liczba(&wspol_x, size);
    losowa_liczba(&punkt_koncowy, size);



    generowanie_labiryntu(&labirynt, size, move, wspol_y, wspol_x);

    dodaj_wagi(&labirynt, size);

    //tworzenie tablicy o wymairach 2n+1*2n+1; tablica dynamiczna
    int **tablica = malloc((2 * size + 1) * sizeof (int *));
    if (tablica == NULL) {
        printf("Nie udało się wygenerować labirynt. Błąd pamięci\n"); 
        fflush(stdout);
        return 1;
    }
    for (int i = 0; i < 2 * size + 1; i++) {
        tablica[i] = malloc((2 * size + 1) * sizeof(int));
        if (tablica[i] == NULL) {
            printf("Nie udało się wygenerować labirynt. Błąd pamięci\n"); 
            fflush(stdout);
            return 1;
        }
    }
    wysw_tekstowe(&labirynt, size, wspol_x, punkt_koncowy, tablica);
    wyswietl_labirynt_graficznie(tablica, size); 
    

    znajdz_drogi(&labirynt, size);

    zwolnienie(&labirynt, size);
    zwolnij_stos(size2, move);
    for (int i = 0; i < 2 * size + 1; i++) {
        free(tablica[i]);
    }
    free(tablica);
    return 0;
}

