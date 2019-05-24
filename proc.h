#ifndef PROC_H_INCLUDED
#define PROC_H_INCLUDED

//escojer una coordenada para disparar, con el tablero de 2 personas
void escojer_barco_2P(int dim, int table1[][10],int table2[][10], int *pxx, int *pyy, int turno);

// calcular puntuacion
float efectivitat_trets(int mida_barco, int n, int lanzamientos[n]);

//guardar la partida
void write(int dim,int s1[][10],int s2[][10], int barcos_p1,
	int barcos_p2, int turno, int lanzamientos_totales, int n1, int n2, int lanzamientos1[10],
	int lanzamientos2[10], int players, int lvl, int barcos, float efectivitat1, float efectivitat2, float puntuacion_total2,
	float puntuacion_total1, FILE *out);

//calcular coordenada aleatoria
void cpu_lvl1(int dim, int s[][10], int *x, int *y);

void cpu_lvl2(int dim,int s[][10], int *x, int *y);

void cpu_lvl3(int dim, int s[][10], int *x, int *y, int *fire_x, int *fire_y);

//escojer una coordenada para disparar, con el tablero de 1 persona
void escojer_barco_1P(int dim, int table1[][10],int table2[][10], int *pxx, int *pyy, int turno);

// imprimir tablero(solo se usa cuando esta jugando un solo jugador)
void imprimir_Barcos_p1(int dim, int table1[][10], int table2[][10], int resultado1, int resultado2);

// imprimir tablero(solo se usa cuando no esta jugando ningun jugador)
void imprimir_Barcos_p0(int dim, int table1[][10], int table2[][10]);

// escribir la puntuacion al ranking
void s_record(int score, FILE *out);





#endif
