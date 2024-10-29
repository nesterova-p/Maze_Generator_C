#ifndef LABIRYNT_H_
#define LABIRYNT_H_
#include <stdbool.h>

typedef struct {
    bool wall;
    bool top, bottom, right,left;
    bool visited;
    float weight; 
} maze;

int losowa_liczba(int *x, int size);
void inicjacja(maze ***labirynt, int size);
void generowanie_labiryntu(maze ***labirynt, int size, int **move, int wspol_y, int wspol_x);
void wysw_tekstowe(maze ***labirynt, int size, int wspol_x, int xkon, int **tablica);
void zwolnij_stos(int size, int **move);
void zwolnienie(maze ***labirynt, int size);
int usun_sciane(maze ***labirynt, int size, int **move, int *punkt_x, int *punkt_y);

#endif 