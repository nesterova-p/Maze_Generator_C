#ifndef GRAF_H_
#define GRAF_H_

#include "labir.h"

void dodaj_wagi(maze ***labirynt, int size);
void dfs(maze ***labirynt, int size, int y, int x, int **visited, float current_weight, float *min_weight, float *max_weight, int *path_count);
void znajdz_drogi(maze ***labirynt, int size);

#endif  

