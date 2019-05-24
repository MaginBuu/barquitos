#ifndef LIBVAIXELLS_H_INCLUDED
#define LIBVAIXELLS_H_INCLUDED

//disparar dentro del tablero
int disparar(int dim, int table[][10], int px, int py, int *mida_barco);

//colocar los barcos aleatoriamente
void colocar_barcos_aleatoriamente(int dim, int table[][10]);

// colocar los barcos manualmente
void colocar_barcos_manualmente(int dim, int table[][10]);


#endif
