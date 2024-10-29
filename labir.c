#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stos.h"
#include "labir.h"
#include "graf.h"
//funkcja do generowania losowej liczby w zakresie od 0 do 'size'
int losowa_liczba(int *x, int size)
{
    *x = rand()%size;
    return *x;
}
//inicjalizacja labiryntu o wymiarach size*size
void inicjacja(maze ***labirynt, int size)
{
    int i, j;
    *labirynt = malloc(size * sizeof (maze *));

    for (i = 0; i < size; i++) 
    {
        (*labirynt)[i] = malloc(size * sizeof(maze));
        for (j = 0; j<size; j++)
        {
            (*labirynt)[i][j].visited = false;
            (*labirynt)[i][j].top = false;
            (*labirynt)[i][j].bottom = false;
            (*labirynt)[i][j].right = false;
            (*labirynt)[i][j].left = false;
           

        }
    }
}

//Funkcja do generowania labiryntu z użyciem algorytmu DFS
void generowanie_labiryntu(maze ***labirynt,int size, int **move, int wspol_y, int wspol_x)
{
    int punkt_y = wspol_y;
    int punkt_x = wspol_x;
    dodaj_wagi(labirynt, size); 
    (*labirynt)[punkt_y][punkt_x].visited = true;
    push_stack(move, punkt_x, punkt_y, size*size);



    while( top_stack(move, size*size) != -1)
    {
        while( usun_sciane(labirynt, size, move, &punkt_x, &punkt_y) == -1 )
        {
            pop_stack(move, size*size);
            int indeks = top_stack(move, size*size);
            if (indeks == -1)
            {
                return;
            }
            punkt_y = move[indeks][0];
            punkt_x = move[indeks][1];
        }
    }
        if (punkt_x == wspol_x && punkt_y == wspol_y)
        {
          return;
        }
}

//Wyświetlenie w formie tekstowej
/* Najpierw wypełnienie licbą 4
   Potem wypełnienie ścian 2
   Ustawienie każdej 2iej kratki (od 0 do 2n + 1) na 1
   Ustawienie komórki powyżej wierzchołków (po analizie tego jaka jest zawartość labiryntu)
   Ustawienie komórki z prawej strony od wierzchołka
   Losowe usunięcie ścian
   Zerowanie początkowej i końcowej ściany
   Koregowanie ścian bocznych, żeby były stworzone wyłącznie z 2
   Oraz wypisanie labiryntu w postaci liczb 
*/
void wysw_tekstowe(maze ***labirynt, int size, int wspol_x, int xkon, int **tablica) 
{
    for (int i = 0; i < 2 * size + 1; i++) 
    {
        for (int j = 0; j < 2 * size + 1; j++) 
        {
            tablica[i][j] = 4;
        }
    }

    for (int i = 0; i < 2 * size + 1; i++) 
    {
        tablica[i][0] = 2;
        tablica[i][2 * size] = 2;
        tablica[0][i] = 2;
        tablica[2 * size][i] = 2;
    }

    for (int i = 0; i < 2 * size + 1; i+= 2) 
    {
        for (int j = 0; j < 2 * size + 1; j+= 2) 
        {
            tablica[i][j] = 2;
        }
    }

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if ((*labirynt)[i][j].top == true) 
            {
                tablica[i * 2][j * 2 + 1] = 0;
            }
            else   tablica[i * 2][j * 2 + 1] = 1;
            tablica[i * 2 + 1][j * 2 + 1] = 3;
        }
    }
    
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if ((*labirynt)[i][j].right == true) 
            {
                tablica[i * 2 + 1][j * 2 + 2] = 0;
            }
            else   tablica[i * 2 + 1][j * 2 + 2] = 1;
        }
    }

    for (int i = 0; i < size; i++) 
    {
        tablica[0][i * 2 + 1] = 2;
        tablica[i * 2 + 1][2 * size] = 2;
    }

    for (int i = 0; i < 2 * size + 1; i++) 
    {
        for (int j = 0; j < 2 * size + 1; j++)
         {
            if (tablica[i][j] == 1) 
            {
                int los = rand() % 9;
                if (los == 1) 
                {
                    tablica[i][j] = 0;
                }
            }
        }
    }

    tablica[0][wspol_x*2+1] = 0;
    tablica[2 * size][xkon*2+1] = 0;

    for (int i = 0; i < 2 * size + 1; i++) 
    {
        for (int j = 0; j < 2 * size + 1; j++) 
        {
            printf("%d ", tablica[i][j]);
        }
        printf("\n");
    }
}
//Funkcja do usuwania ścian w labiryncie
int usun_sciane(maze ***labirynt, int size, int **move, int *punkt_x, int *punkt_y) 
{
    //możliwe kierunki
    bool kierunek_tabl[4]  = {false};
    //liczba możliwych kierunków 
    int available_number = 0; 
    bool czy_udalo = false;

    if (*punkt_y > 0 && !(*labirynt)[*punkt_y - 1][*punkt_x].visited) //czy kierunek jest dostępny
    {
        //Top
        kierunek_tabl[0] = true; 
        available_number++;
    }
    if (*punkt_x < size - 1 && !(*labirynt)[*punkt_y][*punkt_x + 1].visited) 
    {
        //Right
        kierunek_tabl[1] = true; 
        available_number++;
    }
    if (*punkt_y < size - 1 && !(*labirynt)[*punkt_y + 1][*punkt_x].visited) 
    {
        //Bottom
        kierunek_tabl[2] = true; 
        available_number++;
    }
    if (*punkt_x > 0 && !(*labirynt)[*punkt_y][*punkt_x - 1].visited) 
    {
        //Left
        kierunek_tabl[3] = true; 
        available_number++;
    }

    // Losowanie kierunka
    while (available_number > 0 && !czy_udalo) 
    {
        int kierunek = rand() % 4;
        if (kierunek_tabl[kierunek]) 
        {
            if (kierunek == 0) 
            {
                (*labirynt)[*punkt_y][*punkt_x].top = true;
                (*labirynt)[(*punkt_y) - 1][*punkt_x].bottom = true;
                (*punkt_y)--;
            } 
            else if (kierunek == 1) 
            {
                (*labirynt)[*punkt_y][*punkt_x].right = true;
                (*labirynt)[*punkt_y][(*punkt_x) + 1].left = true;
                (*punkt_x)++;
            } 
            else if (kierunek == 2) 
            {
                (*labirynt)[*punkt_y][*punkt_x].bottom = true;
                (*labirynt)[(*punkt_y) + 1][*punkt_x].top = true;
                (*punkt_y)++;
            } 
            else if (kierunek == 3) 
            {
                (*labirynt)[*punkt_y][*punkt_x].left = true;
                (*labirynt)[*punkt_y][(*punkt_x) - 1].right = true;
                (*punkt_x)--;
            }
            (*labirynt)[*punkt_y][*punkt_x].visited = true;

            push_stack(move, *punkt_x, *punkt_y, size * size);
            czy_udalo = true;
        } 
        
    }
    // Jeśli już nie ma możliwych kierunków
    if (!czy_udalo) 
    {
        return -1;
    }
    return 1;
}

//Zwolnienie pamięci, którą zajmuje labirynt
void zwolnienie(maze ***labirynt, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        free((*labirynt)[i]);
    }
    free(*labirynt);
    *labirynt = NULL;
}
