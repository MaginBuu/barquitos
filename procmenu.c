#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "proc.h"
#include "libvaixells.h"

FILE *out;
FILE *in;
FILE *ranking;

struct data
{
	char name[20];
	int score;
	char date[20];
}player[99];

enum
{
  ESC         = 27,
  Enter       = 13,
  KEY_DOWN    = 256 + 80,
  KEY_UP      = 256 + 72,
};

void menu_players(int *lvl, int *players, int *barcos, int *dim){
    int i=1, tecla, partida=1;
    do{
        system("cls");
        if(i==1){printf("\n=> IA vs IA");}
        else{printf("\n    IA VS IA");}
        if(i==2){printf("\n=> 1P vs IA");}
        else{printf("\n    1P vs IA");}
        if(i==3){printf("\n=> 1P vs 2P\n");}
        else{printf("\n    1P vs 2P\n");}

        tecla = getch();
        if (tecla == 0 || tecla == 224){tecla = 256 + getch();}

        if(tecla == KEY_DOWN && i < 3){i++;}
        if(tecla == KEY_UP && i > 1){i--;}
    }while(tecla != Enter && tecla != ESC);
    if(tecla==Enter){*players=i;
        menu_dim(lvl, players, barcos, dim);}
    else{main(partida);}}

void menu_dim(int *lvl, int *players, int *barcos, int *dim){
    int i=1, tecla;
    do{
        system("cls");
        if(i==1){printf("\n=> Dim = 8");}
        else{printf("\n    Dim = 8");}
        if(i==2){printf("\n=> Dim = 9");}
        else{printf("\n    Dim = 9");}
        if(i==3){printf("\n=> Dim = 10\n");}
        else{printf("\n    Dim = 10\n");}

        tecla = getch();
        if (tecla == 0 || tecla == 224){tecla = 256 + getch();}

        if(tecla == KEY_DOWN && i < 3){i++;}
        if(tecla == KEY_UP && i > 1){i--;}
    }while(tecla != Enter && tecla != ESC);
    if(tecla==Enter && *players!=1){*dim=i;
        menu_barcos(lvl, players, barcos, dim);}
    else if(tecla==Enter && *players==1){*dim=i; *barcos=1; menu_IA(lvl, players, barcos, dim);}
    else {menu_players(lvl, players, barcos, dim);}}


void menu_barcos(int *lvl, int *players, int *barcos, int *dim){
    int i=1, tecla;
    do{
        system("cls");
        if(i==1){printf("\n=> colocar barcos aleatoriamente");}
        else{printf("\n    colocar barcos aleatoriamente");}
        if(i==2){printf("\n=> colocar barcos manualmente\n");}
        else{printf("\n    colocar barcos manualmente\n");}

        tecla = getch();
        if (tecla == 0 || tecla == 224){tecla = 256 + getch();}

        if(tecla == KEY_DOWN && i < 2){i++;}
        if(tecla == KEY_UP && i > 1){i--;}
    }while(tecla != Enter && tecla != ESC);
    if(tecla == Enter && (*players==2 || *players==1)){*barcos=i;
        menu_IA(lvl, players, barcos, dim);}
    else if(tecla == Enter && *players==3){*lvl=-1; *barcos=i;}
    else{menu_dim(lvl, players, barcos, dim);}
}

void menu_IA(int *lvl, int *players, int *barcos, int *dim){
    int i=1, tecla;
    do{
        system("cls");
        if(i==1){printf("\n=> IA lvl 1");}
        else{printf("\n    IA lvl 1");}
        if(i==2){printf("\n=> IA lvl 2");}
        else{printf("\n    IA lvl 2");}
        if(i==3){printf("\n=> IA lvl 3\n");}
        else{printf("\n    IA lvl 3\n");}

        tecla = getch();
        if (tecla == 0 || tecla == 224){tecla = 256 + getch();}

        if(tecla == KEY_DOWN && i < 3){i++;}
        if(tecla == KEY_UP && i > 1){i--;}
        }while(tecla != Enter && tecla != ESC);
        if(tecla==Enter){*lvl=i;}
        else{menu_barcos(lvl, players, barcos, dim);}}



int partida_p1_vs_p2(int dim, int barcos, int players, int lvl, int table1[][dim], int table2[][dim], int barcos_p1, int barcos_p2, int turno, int lanzamientos_totales, int n1, int n2, int lanzamientos1[10], int lanzamientos2[10], float efectivitat1, float efectivitat2, float puntuacion_total1, float puntuacion_total2){
// players=1 -> IA vs IA, players=2 -> 1P vs IA, players=3 -> 1P vs 2P
// barcos=1 -> colocar aleatoriamente, barcos=2 -> colocar barcos manualmente
// IA=-1 -> no hay IA porque es P1 vs P2
	int x=0, y=0, resultado, mida_barco=0, puntuacion_final=0, menu, partida=0;
	//colocar barcos
	if(barcos==1){
		colocar_barcos_aleatoriamente(dim, table1);
		colocar_barcos_aleatoriamente(dim, table2);
		barcos=3;}
	else if(barcos==2){
		colocar_barcos_manualmente(dim, table1);
		colocar_barcos_manualmente(dim, table2);
		barcos=3;}
    //iniciar juego
	while(barcos_p2!=10 && barcos_p1!=10){
        if(turno!=3){
            lanzamientos_totales++;
            n1++;
            turno=1;
            //escojer el barco en el que quiere disparar el P1
            escojer_barco_2P(dim, table1, table2, &x, &y, turno);
             //opcion de guardar
            if(x==dim+1 && y==dim+1){
                write(dim, table1, table2, barcos_p1, barcos_p2, turno, lanzamientos_totales, n1, n2, lanzamientos1, lanzamientos2, players, lvl, efectivitat1, efectivitat2, puntuacion_total2, puntuacion_total1, barcos, out);
                turno=4;}
            //opcion de ir al menu
            else if(x==dim+3 && y==dim+3){
                menu=main(partida);
                turno=4;
                if(menu==0){return 0;}
                else if(menu==1){write(dim, table1, table2, barcos_p1, barcos_p2, turno, lanzamientos_totales, n1, n2, lanzamientos1, lanzamientos2, players, lvl, efectivitat1, efectivitat2, puntuacion_total2, puntuacion_total1, barcos, out);}}
            //opcion de guardar y salir
            else if(x==dim+2 && y==dim+2){
                write(dim, table1, table2, barcos_p1, barcos_p2, turno, lanzamientos_totales, n1, n2, lanzamientos1, lanzamientos2, players, lvl, efectivitat1, efectivitat2, puntuacion_total2, puntuacion_total1, barcos, out);
                return 0;}
            if(x<dim && y<dim){
                //disparar
                resultado=disparar(dim, table1, x, y, &mida_barco);
                lanzamientos1[n1]=resultado;
                turno++;
                //si el barco se hunde
                if(resultado==4){barcos_p1++;
                    efectivitat1=efectivitat_trets(mida_barco, n1, lanzamientos1);
                    puntuacion_total1+=efectivitat1;
                    n1=0;}}}

		if(barcos_p1!=10 && turno!=4){
			turno=2;
			n2++;
			//escojer el la posicion donde el P2 quiere disparar
			escojer_barco_2P(dim, table1, table2, &x, &y, turno);
			//opcion de guardar
            if(x==dim+1 && y==dim+1){
                write(dim, table1, table2, barcos_p1, barcos_p2, turno, lanzamientos_totales, n1, n2, lanzamientos1, lanzamientos2, players, lvl, efectivitat1, efectivitat2, puntuacion_total2, puntuacion_total1, barcos, out);
                turno=3;}
            //opcion de ir al menu
            else if(x==dim+3 && y==dim+3){
                menu=main(partida);
                turno=3;
                if(menu==0){return 0;}
                else if(menu==1){write(dim, table1, table2, barcos_p1, barcos_p2, turno, lanzamientos_totales, n1, n2, lanzamientos1, lanzamientos2, players, lvl, efectivitat1, efectivitat2, puntuacion_total2, puntuacion_total1, barcos, out);}}
            //opcion de guardar y salir
            else if(x==dim+2 && y==dim+2){
                write(dim, table1, table2, barcos_p1, barcos_p2, turno, lanzamientos_totales, n1, n2, lanzamientos1, lanzamientos2, players, lvl, efectivitat1, efectivitat2, puntuacion_total2, puntuacion_total1, barcos, out);
                return 0;}
            if(x<dim && y<dim){
                //disparar
                resultado=disparar(dim, table2, x, y, &mida_barco);
                lanzamientos2[n2]=resultado;
                //si el barco se hunde
                if(resultado==4){barcos_p2++;
                    efectivitat2=efectivitat_trets(mida_barco, n2, lanzamientos2);
                    puntuacion_total2+=efectivitat2;;
                    n2=0;}}}}
    //decir quien ha ganado y escribir la puntiacion en el ranking
	if(barcos_p1==10){
    	puntuacion_total1=100*((float)dim/(float)lanzamientos_totales)*puntuacion_total1;
    	puntuacion_final=(int)puntuacion_total1;
		printf("PLAYER 1 WINS WITH %i POINTS!!", puntuacion_final);}
	else if (barcos_p2==10){
        puntuacion_total2=100*((float)dim/(float)lanzamientos_totales)*puntuacion_total2;
        puntuacion_final=(int)puntuacion_total2;
		printf("PLAYER 2 WINS WITH %i POINTS!!", puntuacion_final);}
        printf("\nEscribir puntuacion: \n");
        s_record(puntuacion_final, out);
        return 0;}


int partida_p1_vs_IA(int dim, int barcos, int players, int lvl, int table1[][10], int table2[][10], int barcos_p1, int barcos_p2, int turno, int lanzamientos_totales, int n1, int n2, int lanzamientos1[10], int lanzamientos2[10], float efectivitat1, float efectivitat2, float puntuacion_total1, float puntuacion_total2){
// players=1 -> IA vs IA, players=2 -> 1P vs IA, players=3 -> 1P vs 2P
// barcos=1 -> colocar aleatoriamente, barcos=2 -> colocar barcos manualmente
// IA=-1 -> no hay IA porque es P1 vs P2
	int x=0, y=0, resultado1, resultado2, mida_barco=0, puntuacion_final=0, menu, partida=0, x1=0, y1=0, fire_x, fire_y;
	//colocar barcos
	if(barcos==1){
		colocar_barcos_aleatoriamente(dim, table1);
		colocar_barcos_aleatoriamente(dim, table2);
		barcos=3;}
	else if(barcos==2){
		colocar_barcos_manualmente(dim, table1);
		colocar_barcos_aleatoriamente(dim, table2);
		barcos=3;}
	fflush(stdin);
	//empezar juego
	while(barcos_p2!=10 && barcos_p1!=10){
		lanzamientos_totales++;
		n1++;
		turno=1;
		//escojer el barco en el que el P1 quiere disparar
		escojer_barco_1P(dim, table1, table2, &x, &y, turno);
		//opcion de guardar
        if(x==dim+1 && y==dim+1){
            write(dim, table1, table2, barcos_p1, barcos_p2, turno, lanzamientos_totales, n1, n2, lanzamientos1, lanzamientos2, players, lvl, efectivitat1, efectivitat2, puntuacion_total2, puntuacion_total1, barcos, out);
            turno++;}
        //opcion de ir al menu
        else if(x==dim+3 && y==dim+3){
            menu=main(partida);
            turno++;
            if(menu==0){return 0;}
            else if(menu==1){write(dim, table1, table2, barcos_p1, barcos_p2, turno, lanzamientos_totales, n1, n2, lanzamientos1, lanzamientos2, players, lvl, efectivitat1, efectivitat2, puntuacion_total2, puntuacion_total1, barcos, out);}}
        //opcion de guardar y salir
        else if(x==dim+2 && y==dim+2){
            write(dim, table1, table2, barcos_p1, barcos_p2, turno, lanzamientos_totales, n1, n2, lanzamientos1, lanzamientos2, players, lvl, efectivitat1, efectivitat2, puntuacion_total2, puntuacion_total1, barcos, out);
            return 0;}
         //disparar
        if(x<dim && y<dim){
        resultado1=disparar(dim, table2, x, y, &mida_barco);
		lanzamientos1[n1]=resultado1;}
		//si hunde barco
		if(resultado1==4){barcos_p1++;
			efectivitat1=efectivitat_trets(mida_barco, n1, lanzamientos1);
			puntuacion_total1+=efectivitat1;
			n1=0;}
			turno++;
        //turno p2(cpu)
        if(barcos_p1!=10 && turno==2){
			n2++;
			//calcular tiro cpu
            if(lvl==1){cpu_lvl1(dim, table1, &fire_x, &fire_y);}
            else if(lvl==2){cpu_lvl2(dim, table1, &fire_x, &fire_y);}
            else if(lvl==3){cpu_lvl3(dim, table1, &x1, &y1, &fire_x, &fire_y);}
            //disparar
            resultado2=disparar(dim, table1, fire_x, fire_y, &mida_barco);
            //imprimir tablero
			imprimir_Barcos_p1(dim, table1, table2, resultado1, resultado2);
			getch();
			lanzamientos2[n2]=resultado2;
			//si hunde barco
			if(resultado2==4){barcos_p2++;
				efectivitat2=efectivitat_trets(mida_barco, n2, lanzamientos2);
				puntuacion_total2+=efectivitat2;
				n2=0;}}}
        //indicar al ganador,  i en caso de que gane el jugador escribir su record en el ranking
		if(barcos_p1==10){
	    	puntuacion_total1=100*((float)dim/(float)lanzamientos_totales)*puntuacion_total1;
	    	puntuacion_final=(int)puntuacion_total1;
			printf("PLAYER 1 WINS WITH %i POINTS!!", puntuacion_final);
			printf("\nEscribir puntuacion: \n");
            s_record(puntuacion_final, out);}
		else if (barcos_p2==10){
	        puntuacion_total2=100*((float)dim/(float)lanzamientos_totales)*puntuacion_total2;
	        puntuacion_final=(int)puntuacion_total2;
	        system("cls");
			printf("CPU WINS WITH %i POINTS!!", puntuacion_final);}
			return 0;}



int partida_IA_vs_IA(int dim, int barcos, int players, int lvl, int table1[][10], int table2[][10], int barcos_p1, int barcos_p2, int turno, int lanzamientos_totales, int n1, int n2, int lanzamientos1[10], int lanzamientos2[10], float efectivitat1, float efectivitat2, float puntuacion_total1, float puntuacion_total2){
// players=1 -> IA vs IA, players=2 -> 1P vs IA, players=3 -> 1P vs 2P
// barcos=1 -> colocar aleatoriamente, barcos=2 -> colocar barcos manualmente
// IA=-1 -> no hay IA porque es P1 vs P2
// como solo juega la cpu, no existe la funcion de guardar partida
	int x1=0, y1=0, x2=0, y2=0, fire_x, fire_y, resultado, mida_barco=0, puntuacion_final=0;
	//colocar barcos
    colocar_barcos_aleatoriamente(dim, table1);
    colocar_barcos_aleatoriamente(dim, table2);
    //iniciar juego
	while(barcos_p2!=10 && barcos_p1!=10){
        system("cls");
		lanzamientos_totales++;
		n1++;
		turno=1;
		//calcular tiro cpu
		if(lvl==1){cpu_lvl1(dim, table1, &fire_x, &fire_y);}
        else if(lvl==2){cpu_lvl2(dim, table1, &fire_x, &fire_y);}
        else if(lvl==3){cpu_lvl3(dim, table1, &x1, &y1, &fire_x, &fire_y);}
        //disparar
        resultado=disparar(dim, table1, fire_x, fire_y, &mida_barco);
        printf("TURNO DE CPU1: \n");
        //imprimir tablero
        imprimir_Barcos_p0(dim, table1, table2);
        if(resultado==1){printf("\nAGUA\n");}
        else if(resultado==3){printf("\nBARCO TOCADO\n");}
        else if(resultado==4){printf("\nBARCO HUNDIDO!!\n");}
        else{printf("\nCASILLA REPETIDA\n");}
        getch();
		lanzamientos1[n1]=resultado;
		//si el barco se hunde
		if(resultado==4){barcos_p1++;
			efectivitat1=efectivitat_trets(mida_barco, n1, lanzamientos1);
			puntuacion_total1+=efectivitat1;
			n1=0;}
        //turno cpu2
        if(barcos_p1!=10){
            system("cls");
			turno++;
			n2++;
			//calcular tiro cpu2
            if(lvl==1){cpu_lvl1(dim, table2, &fire_x, &fire_y);}
            else if(lvl==2){cpu_lvl2(dim, table2, &fire_x, &fire_y);}
            else if(lvl==3){cpu_lvl3(dim, table2, &x2, &y2, &fire_x, &fire_y);}
            //disparar
            resultado=disparar(dim, table2, fire_x, fire_y, &mida_barco);
            printf("TURNO DE CPU2:\n");
            //imprimir tablero
			imprimir_Barcos_p0(dim, table1, table2);
            if(resultado==1){printf("\nAGUA\n");}
            else if(resultado==3){printf("\nBARCO TOCADO\n");}
            else if(resultado==4){printf("\nBARCO HUNDIDO!!\n");}
            else{printf("\nCASILLA REPETIDA\n");}
			getch();
			lanzamientos2[n2]=resultado;
			//si el barco se hunde
			if(resultado==4){barcos_p2++;
				efectivitat2=efectivitat_trets(mida_barco, n2, lanzamientos2);
				puntuacion_total2+=efectivitat2;
				n2=0;}}}
        //decir quien es el ganador, en este caso como solo juega la cpu, no esta la opcion de guardar record
		if(barcos_p1==10){
	    	puntuacion_total1=100*((float)dim/(float)lanzamientos_totales)*puntuacion_total1;
	    	puntuacion_final=(int)puntuacion_total1;
			printf("CPU 1 WINS WITH %i POINTS!!", puntuacion_final);}
		else if (barcos_p2==10){
	        puntuacion_total2=100*((float)dim/(float)lanzamientos_totales)*puntuacion_total2;
	        puntuacion_final=(int)puntuacion_total2;
			printf("CPU 2 WINS WITH %i POINTS!!", puntuacion_final);}
			return 0;}




void load(int *dim, int s1[][10],int s2[][10], int *barcos_p1,int *barcos_p2, int *turno, int *lanzamientos_totales, int *n1, int *n2, int lanzamientos1[10], int lanzamientos2[10], int *players, int *lvl, int *barcos, float *efectivitat1, float *efectivitat2, float *puntuacion_total2,	float *puntuacion_total1, FILE *in){

	char save[20];
	int i, j, x;
	float f;

	printf("Digite el nombre del save que desea cargar (ej: save.txt):  ");
	gets(save);

	in = fopen(save,"r");

	fscanf(in,"%i",&x);
	*dim=x;

	for (i = 0; i < 10; ++i)
	{
		for (j = 0; j < 10; ++j)
		{
			fscanf(in,"%i",&s1[i][j]);
		}
	}


	for (i = 0; i < 10; ++i)
	{
		for (j = 0; j < 10; ++j)
		{
			fscanf(in,"%i",&s2[i][j]);
		}
	}

	for (i = 0; i < 10; ++i)
	{
	fscanf(in, "%i ",&lanzamientos1[i]);
	}
	for (i = 0; i < 10; ++i)
	{
	fscanf(in, "%i ",&lanzamientos2[i]);
	}


fscanf(in, "%i", &i);
*barcos_p1=i;
fscanf(in, "%i", &i);
*barcos_p2=i;
fscanf(in, "%i", &i);
*turno=i;
fscanf(in, "%i", &i);
*lanzamientos_totales=i;
fscanf(in, "%i", &i);
*n1=i;
fscanf(in, "%i", &i);
*n2=i;
fscanf(in, "%i", &i);
*players=i;
fscanf(in, "%i", &i);
*lvl=i;
fscanf(in, "%i", &i);
*barcos=i;
fscanf(in, "%f", &f);
*efectivitat1=f;
fscanf(in, "%f", &f);
*efectivitat2=f;
fscanf(in, "%f", &f);
*puntuacion_total1=f;
fscanf(in, "%f", &f);
*puntuacion_total1=f;
}





//llegir els records
void records()
{ int x, y;
	ranking = fopen("Ranking.txt","r");
	int max_score,i=0, n=10,temp2;
	char temp1[20],temp3[20];

	fscanf(ranking,"%i",&max_score);

	while (!feof(ranking)){
	fscanf(ranking,"%s",&player[i].name);
	fscanf(ranking,"%i",&player[i].score);
	fscanf(ranking,"%s",&player[i].date);
	i++;
	}


for(x=0; x<n; x++)
	{
		for(y=0; y<n-1; y++)

		{
			if(player[y].score<player[y+1].score)

			{
				strcpy(temp1, player[y+1].name);
				temp2 = player[y+1].score;
				strcpy(temp3, player[y+1].date);

				strcpy(player[y+1].name, player[y].name);
				player[y+1].score = player[y].score;
				strcpy(player[y+1].date, player[y].date);

				strcpy(player[y].name, temp1);
				player[y].score = temp2;
				strcpy(player[y].date, temp3);

			}
		}
	}



	for (i = 0; i < 30; ++i)
	{
		printf("%s		",player[i].name );
		printf("%i		",player[i].score );
		printf("%s		",player[i].date );
		printf("\n");
	}
}


