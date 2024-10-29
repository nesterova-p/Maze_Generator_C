#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "stos.h"
#include "labir.h"
#include <ncurses.h>

void wyswietl_labirynt_graficznie(int **tablica_wys_lab, int rozmiar) {
    initscr(); // Inicjalizacja ncurses
    start_color(); // Włączenie kolorów
    init_pair(1, COLOR_BLACK, COLOR_WHITE); // Kolor dla ścian
    init_pair(2, COLOR_BLACK, COLOR_GREEN); // Kolor dla przejść

    for (int i = 0; i < 2 * rozmiar + 1; i++) {
        for (int j = 0; j < 2 * rozmiar + 1; j++) {
            if (tablica_wys_lab[i][j] == 1 || tablica_wys_lab[i][j] == 2) {
                attron(COLOR_PAIR(1));
                printw("%c ", 178);
            } else if (tablica_wys_lab[i][j] == 0 || tablica_wys_lab[i][j] == 3) {
                attron(COLOR_PAIR(2));
                printw("%c ", 176);
            } else if (tablica_wys_lab[i][j] == 4) {
                printw("w");
            }
        }
        printw("\n");
    }

    refresh(); // Odświeżenie ekranu
    getch(); // Oczekiwanie na klawisz
    endwin(); // Zakończenie ncurses
}
