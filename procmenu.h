#ifndef PROC_H_INCLUDED
#define PROC_H_INCLUDED

// funciones dentro del menu
void menu_players(int *lvl, int *players, int *barcos, int *dim);

void menu_dim(int *lvl, int *players, int *barcos, int *dim);

void menu_barcos(int *lvl, int *players, int *barcos, int *dim);

void menu_IA(int *lvl, int *players, int *barcos, int *dim);


// inicialitzar la partida de 2 jugadors
int partida_p1_vs_p2(int dim, int barcos, int players, int lvl, int table1[][10], int table2[][10], int barcos_p1, int barcos_p2, int turno, int lanzamientos_totales, int n1, int n2, int lanzamientos1[10], int lanzamientos2[10], float efectivitat1, float efectivitat2, float puntuacion_total1, float puntuacion_total2);

//inicialitzar la partida de 1 jugador
int partida_p1_vs_IA(int dim, int barcos, int players, int lvl,  int table1[][10], int table2[][10], int barcos_p1, int barcos_p2, int turno, int lanzamientos_totales, int n1, int n2, int lanzamientos1[10], int lanzamientos2[10], float efectivitat1, float efectivitat2, float puntuacion_total1, float puntuacion_total2);

//inicialitzar la partida de 0 jugadors
int partida_IA_vs_IA(int dim, int barcos, int players, int lvl, int table1[][10], int table2[][10], int barcos_p1, int barcos_p2, int turno, int lanzamientos_totales, int n1, int n2, int lanzamientos1[10], int lanzamientos2[10], float efectivitat1, float efectivitat2, float puntuacion_total1, float puntuacion_total2);


// llegir una partida
void load(int *dim, int s1[][dim],int s2[][dim], int *barcos_p1, int *barcos_p2, int *turno, int *lanzamientos_totales, int *n1, int *n2, int lanzamientos1[10],int lanzamientos2[10], int *players, int *lvl, int *barcos, float *efectivitat1, float *efectivitat2, float *puntuacion_total2, float *puntuacion_total1, FILE *in);

//llegir els records
void records();





#endif
