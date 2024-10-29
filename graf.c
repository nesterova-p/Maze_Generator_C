#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "stos.h"
#include "labir.h"
#include "graficz.h"
#include "graf.h"

// Funkcja dodająca wagę do komórek, które są przejściem
void dodaj_wagi(maze ***labirynt, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((*labirynt)[i][j].top) {
                (*labirynt)[i][j].weight = (float)(rand() % 11);
            }
        }
    }
}

// Funkcja pomocnicza dla rekurencyjnego szukania dróg
void dfs(maze ***labirynt, int size, int y, int x, int **visited, float current_weight, float *min_weight, float *max_weight, int *path_count) {
    if (y < 0 || y >= size || x < 0 || x >= size || visited[y][x] || (*labirynt)[y][x].wall) {
        return;
    }

    visited[y][x] = 1;
    current_weight += (*labirynt)[y][x].weight;

    // Jeśli dotarliśmy do wyjścia
    if (y == size - 1 && x == size - 1) {
        // Aktualizuj minimalną i maksymalną wagę
        *min_weight = fmin(*min_weight, current_weight);
        *max_weight = fmax(*max_weight, current_weight);
        (*path_count)++;  // Zwiększ licznik dróg
    }

    // Przeszukaj sąsiednie komórki
    dfs(labirynt, size, y - 1, x, visited, current_weight, min_weight, max_weight, path_count);  // Góra
    dfs(labirynt, size, y + 1, x, visited, current_weight, min_weight, max_weight, path_count);  // Dół
    dfs(labirynt, size, y, x - 1, visited, current_weight, min_weight, max_weight, path_count);  // Lewo
    dfs(labirynt, size, y, x + 1, visited, current_weight, min_weight, max_weight, path_count);  // Prawo

    visited[y][x] = 0;  // Oznacz jako nieodwiedzone po zakończeniu przeglądu
}

// Funkcja do znalezienia dróg od wejścia do wyjścia
void znajdz_drogi(maze ***labirynt, int size) {
    int **visited = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        visited[i] = malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            visited[i][j] = 0;
        }
    }

    float min_weight = FLT_MAX;  // Początkowo ustawione na nieskończoność
    float max_weight = 0;
    int path_count = 0;  // Licznik dróg

    // Szukaj dróg rekurencyjnie zaczynając od punktu (0, 0)
    dfs(labirynt, size, 0, 0, visited, 0, &min_weight, &max_weight, &path_count);

    // Wypisz informacje o znalezionych drogach
    printf("Ilość dróg prowadzących od wejścia do wyjścia: %d\n", path_count);
    printf("Najkrótsza droga (suma wag): %.2f\n", min_weight);
    printf("Najdłuższa droga (suma wag): %.2f\n", max_weight);

    // Zwolnij zaalokowaną pamięć
    for (int i = 0; i < size; i++) {
        free(visited[i]);
    }
    free(visited);
}
