#include "stos.h"
#include <stdio.h>
#include <stdlib.h>

int pop_stack(int **stos_z_ruchami, int rozmiar) {
    int i = 0;
    while (i < rozmiar && stos_z_ruchami[i][0] != -1 && stos_z_ruchami[i][1] != -1) {
        i++;
    }
    if (i == 0) {
        //Stos pusty
        return -1; 
    } else {
        stos_z_ruchami[i - 1][0] = -1;
        stos_z_ruchami[i - 1][1] = -1;
        return 0;
    }
}

int top_stack(int **stos_z_ruchami, int rozmiar) {
    int i = 0;
    while (i < rozmiar && stos_z_ruchami[i][0] != -1 && stos_z_ruchami[i][1] != -1) {
        i++;
    }
    if (i == 0) {
        //Stos  pusty
        return -1; 
    } else {
        return i - 1;
    }
}

int push_stack(int **stos_z_ruchami, int x, int y, int rozmiar) {
    int i = 0;
    while (i < rozmiar && stos_z_ruchami[i][0] != -1 && stos_z_ruchami[i][1] != -1) {
        i++;
    }
    if (i >= rozmiar) {
        //Stos przepełniony
        return -1; 
    }
    stos_z_ruchami[i][0] = y;
    stos_z_ruchami[i][1] = x;
    return 0;
}