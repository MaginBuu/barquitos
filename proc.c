#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "proc.h"
#include "proc.h"
FILE *out;

enum
{
  KEY_ESC     = 27,
  ARROW_UP    = 256 + 72,
  ARROW_DOWN  = 256 + 80,
  ARROW_LEFT  = 256 + 75,
  ARROW_RIGHT = 256 + 77,
  KEY_F9      = 256 + 67,
  KEY_F10     = 256 + 68
};

void escojer_barco_2P(int dim, int table1[][10],int table2[][10], int *pxx, int *pyy, int turno)
{
  // player1 intentara hundir al tablero1 y el player 2 al 2
  int ch, py=0, px=0, i, j, x;
  system("cls");
  px=0; py=0;
  do{
  	printf("ESC=Menu\tF9=Guardar\tF10=Guardar y salir\n");
    printf("TURNO DE P%i\n\n", turno);
      if(turno==1){
        for (i = 0; i < dim; ++i)
        {
        for (j = 0; j < dim; ++j)
        { if (px==j && py==i){
          if(table1[i][j]==0 || table1[i][j]==2){
              printf(" [?] ");}
            else if(table1[i][j]==1){
              printf(" [.] ");}
            else if(table1[i][j]==3){
              printf(" [@] ");}
            else if(table1[i][j]==4){
              printf(" [X] ");}
        }
          else{
            if(table1[i][j]==0 || table1[i][j]==2){
              printf("  ?  ");}
            else if(table1[i][j]==1){
              printf("  .  ");}
            else if(table1[i][j]==3){
              printf("  @  ");}
            else if(table1[i][j]==4){
              printf("  X  ");}
          }}
          printf("\t\t");
          for (x = 0; x < dim; ++x)
          {
            if(table2[i][x]==0){
              printf("  ?  ");}
            else if(table2[i][x]==1){
              printf("  .  ");}
            else if(table2[i][x]==2){
              printf("  ?  ");}
            else if(table2[i][x]==3){
              printf("  @  ");}
            else if(table2[i][x]==4){
              printf("  X  ");}
          }
          printf("\n\n");}}
      else{
        for (i = 0; i < dim; ++i)
        {
          for (j = 0; j < dim; ++j)
          {
            if(table1[i][j]==0){
              printf("  ?  ");}
            else if(table1[i][j]==1){
              printf("  .  ");}
            else if(table1[i][j]==2){
              printf("  ?  ");}
            else if(table1[i][j]==3){
              printf("  @  ");}
            else if(table1[i][j]==4){
              printf("  X  ");}
            }
            printf("\t\t");
            for (x = 0; x < dim; ++x)
            {
              if (px==x && py==i){
                if(table2[i][x]==2 || table2[i][x]==0){
                  printf(" [?] ");}
                else if(table2[i][x]==1){
                  printf(" [.] ");}
                else if(table2[i][x]==3){
                  printf(" [@] ");}
                else if(table2[i][x]==4){
                  printf(" [X] ");}}
              else{
                if(table2[i][x]==2 || table2[i][x]==0){
                  printf("  ?  ");}
                else if(table2[i][x]==1){
                  printf("  .  ");}
                else if(table2[i][x]==3){
                  printf("  @  ");}
                else if(table2[i][x]==4){
                  printf("  X  ");}}
            }
            printf("\n\n");}
        }


    ch = getch();
    if ( ch == 0 || ch == 224 ){ch = 256 + getch();}
    if ( ch == ARROW_UP ){py-=1;}
    if ( ch == ARROW_DOWN ){py+=1;}
    if ( ch == ARROW_LEFT ){px-=1;}
    if ( ch == ARROW_RIGHT ){px+=1;}

    if (px<0){px=dim-1;}
    if (px>dim-1){px=0;}
    if (py<0){py=dim-1;}
    if (py>dim-1){py=0;}

    system("cls");

  *pxx=px;
  *pyy=py;

  }while((ch != 13 || (turno==1 && (table2[py][px]!=2 && table2[py][px]!=0)) && (turno==2 && (table1[py][px]!=2 && table1[py][px]!=0))) && ch!= KEY_ESC && ch!= KEY_F9 && ch!= KEY_F10);
  if(ch==KEY_F9){
  	*pyy=dim+1;
  	*pxx=dim+1;}
  else if(ch==KEY_F10){
  	*pyy=dim+2;
  	*pxx=dim+2;}
  else if(ch==KEY_ESC){
  	*pyy=dim+3;
  	*pxx=dim+3;}
}
// f9=67, f10=68

float efectivitat_trets(int mida_barco, int n, int lanzamientos[n]){

	int i, j=0;
	float efectivitat;

	efectivitat=((2*mida_barco)-1);
	for (i = 1; i <= n; ++i)
	{
		j+=(4-lanzamientos[i]);
	}
    if(j==0){j=1;}
	efectivitat/=j;

	return efectivitat;}

 void write(int dim,int s1[][10],int s2[][10], int barcos_p1,
	int barcos_p2, int turno, int lanzamientos_totales, int n1, int n2, int lanzamientos1[10],
	int lanzamientos2[10], int players, int lvl, int barcos, float efectivitat1, float efectivitat2, float puntuacion_total2,
	float puntuacion_total1, FILE *out){

char save[20];
int i, j;

printf("Digita el nombre del save (ej: save1.txt):  ");
gets(save);

if(turno==2){turno=3;}

out = fopen(save,"w+");

fprintf(out, "%i ", dim);
fprintf(out, "%s", "\n");

for (i = 0; i < 10; ++i)
{
	for (j = 0; j < 10; ++j)
	{
		fprintf(out, "%i ", s1[i][j]);
	}

}

fprintf(out, "%s", "\n");

for (i = 0; i < 10; ++i)
{
	for (j = 0; j < 10; ++j)
	{
		fprintf(out, "%i ", s2[i][j]);
	}

}

fprintf(out, "%s", "\n");

for (i = 0; i < 10; ++i)
{
	fprintf(out, "%i ", lanzamientos1[i]);
}
fprintf(out, "%s", "\n");
for (i = 0; i < 10; ++i)
{
	fprintf(out, "%i ", lanzamientos2[i]);
}

fprintf(out, "%s", "\n");
fprintf(out, "%i", barcos_p1);
fprintf(out, "%s", "\n");
fprintf(out, "%i", barcos_p2);
fprintf(out, "%s", "\n");
fprintf(out, "%i", turno);
fprintf(out, "%s", "\n");
fprintf(out, "%i", lanzamientos_totales);
fprintf(out, "%s", "\n");
fprintf(out, "%i", n1);
fprintf(out, "%s", "\n");
fprintf(out, "%i", n2);
fprintf(out, "%s", "\n");
fprintf(out, "%i", players);
fprintf(out, "%s", "\n");
fprintf(out, "%i", lvl);
fprintf(out, "%s", "\n");
fprintf(out, "%i", barcos);
fprintf(out, "%s", "\n");
fprintf(out, "%f", efectivitat1);
fprintf(out, "%s", "\n");
fprintf(out, "%f", efectivitat2);
fprintf(out, "%s", "\n");
fprintf(out, "%f", puntuacion_total1);
fprintf(out, "%s", "\n");
fprintf(out, "%f", puntuacion_total2);}


void cpu_lvl1(int dim,int s[][10], int *x, int *y){
srand(time(NULL));
int px , py;
px = rand() % dim;
py = rand() % dim;
*y=px; *x=py;}


void cpu_lvl2(int dim,int s[][10], int *x, int *y){
srand(time(NULL));
int px , py;
do{
px = rand() % dim;
py = rand() % dim;
}while((s[px][py]!=2 && s[px][py]!=0) || s[px+1][py]==4 || s[px-1][py]==4 || s[px][py+1]==4 || s[px][py-1]==4);
*y=px; *x=py;}


void cpu_lvl3(int dim, int s[][10], int *x, int *y, int *fire_x, int *fire_y){
    int x1, y1;
    x1=*x; y1=*y;
    while((s[x1][y1]==1 || s[x1][y1]==4 || s[x1+1][y1]==4 || s[x1-1][y1]==4 || s[x1][y1+1]==4  || s[x1][y1-1]==4)&&(s[x1][y1]!=3)){
    x1 = rand() % dim;
    y1 = rand() % dim;
    *x=x1;
    *y=y1;
    }

    if (s[x1][y1]==2 || s[x1][y1]==0 )
    {
        *fire_x=y1;
        *fire_y=x1;
    }

    else if (s[x1][y1]==3)
    {
        if (s[x1+1][y1]==2 || s[x1+1][y1]==0 && x1!=dim-1)
        {
            x1+=1;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1+1][y1]==3 && ( s[x1+2][y1]==2 || s[x1+2][y1]==0) && x1!=dim-2)
        {
            x1+=2;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1+1][y1]==3 && s[x1+2][y1]==3 && ( s[x1+3][y1]==2 || s[x1+3][y1]==0) && x1!=dim-3)
        {
            x1+=3;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1-1][y1]==2 || s[x1-1][y1]==0 && x1!=0)
        {
            x1-=1;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1-1][y1]==3 && ( s[x1-2][y1]==2 || s[x1-2][y1]==0) && x1!=0 )
        {
            x1-=2;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1-1][y1]==3 && s[x1-2][y1]==3 && ( s[x1-3][y1]==2 || s[x1-3][y1]==0) && x1!=0)
        {
            x1-=3;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1][y1+1]==2 || s[x1][y1+1]==0 && y1!=dim-1)
        {
            y1+=1;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1][y1+1]==3 && ( s[x1][y1+2]==2 || s[x1][y1+2]==0) && y1!=dim-2)
        {
            y1+=2;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1][y1+1]==3 && s[x1][y1+2]==3 && ( s[x1][y1+3]==2 || s[x1][y1+3]==0) && y1!=dim-3)
        {
            y1+=3;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1][y1-1]==2 || s[x1][y1-1]==0 && y1!=0)
        {
            y1-=1;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1][y1-1]==3 && ( s[x1][y1-2]==2 || s[x1][y1-2]==0) && y1!=0)
        {
            y1-=2;
            *fire_x=y1;
            *fire_y=x1;
        }
        else if (s[x1][y1-1]==3 && s[x1][y1-2]==3 && ( s[x1][y1-3]==2 || s[x1][y1-3]==0) && y1!=0)
        {
            y1-=3;
            *fire_x=y1;
            *fire_y=x1;
        }
    }}



void escojer_barco_1P(int dim, int table1[][10],int table2[][10], int *pxx, int *pyy, int turno)
{
  // player1 intentara hundir al tablero1 y el player 2 al 2
  int ch, py=0, px=0, i, j, x;
  system("cls");
  px=0; py=0;
  do{
  	printf("ESC=Menu\tF9=Guardar\tF10=Guardar y salir\n");
  	    for (i = 0; i < dim; ++i)
        {
        for (j = 0; j < dim; ++j){
            if(table1[i][j]==0){
             	printf("  .  ");}
            else if(table1[i][j]==1){
             	printf("  -  ");}
            else if(table1[i][j]==2){
            	printf("  @  ");}
            else if(table1[i][j]==3){
             	printf("  #  ");}
            else if(table1[i][j]==4){
             	printf("  X  ");}
          }
          printf("\t\t");
          for (x = 0; x < dim; ++x)
          {
            if(px==x && py==i){
                if(table2[i][x]==0){
                  printf(" [?] ");}
                else if(table2[i][x]==1){
                  printf(" [.] ");}
                else if(table2[i][x]==2){
                  printf(" [?] ");}
                else if(table2[i][x]==3){
                  printf(" [@] ");}
                else if(table2[i][x]==4){
                  printf(" [X] ");}
          }
           else {
                if(table2[i][x]==0){
                  printf("  ?  ");}
                else if(table2[i][x]==1){
                  printf("  .  ");}
                else if(table2[i][x]==2){
                  printf("  ?  ");}
                else if(table2[i][x]==3){
                  printf("  @  ");}
                else if(table2[i][x]==4){
                  printf("  X  ");}
           }}
          printf("\n\n");}


    ch = getch();
    if ( ch == 0 || ch == 224 ){ch = 256 + getch();}
    if ( ch == ARROW_UP ){py-=1;}
    if ( ch == ARROW_DOWN ){py+=1;}
    if ( ch == ARROW_LEFT ){px-=1;}
    if ( ch == ARROW_RIGHT ){px+=1;}

    if (px<0){px=dim-1;}
    if (px>dim-1){px=0;}
    if (py<0){py=dim-1;}
    if (py>dim-1){py=0;}

    system("cls");

  *pxx=px;
  *pyy=py;

  }while((ch != 13 || (turno==1 && (table2[py][px]!=2 && table2[py][px]!=0)) && (turno==2 && (table1[py][px]!=2 && table1[py][px]!=0))) && ch!= KEY_ESC && ch!= KEY_F9 && ch!= KEY_F10);
  if(ch==KEY_F9){
  	*pyy=dim+1;
  	*pxx=dim+1;}
  else if(ch==KEY_F10){
  	*pyy=dim+2;
  	*pxx=dim+2;}
  else if(ch==KEY_ESC){
  	*pyy=dim+3;
  	*pxx=dim+3;}}



void imprimir_Barcos_p1(int dim, int table1[][10], int table2[][10], int resultado1, int resultado2){
	int i, j, x;
        switch(resultado2){
        case 1: printf("AGUA   \t\t\t\t\t\t\t"); break;
        case 3: printf("BARCO TOCADO   \t\t\t\t\t\t"); break;
        case 4: printf("BARCO HUNDIDO!!!   \t\t\t\t\t"); break;
        default: printf("CASILLA REPETIDA   \t\t\t\t\t"); break;}

        switch(resultado1){
        case 1: printf("AGUA\n"); break;
        case 3: printf("BARCO TOCADO\n"); break;
        case 4: printf("BARCO HUNDIDO!!!\n"); break;
        default: printf("CASILLA REPETIDA\n"); break;}

  		for (i = 0; i < dim; ++i)
  	    {
  			for (j = 0; j < dim; ++j)
  			{
  				if(table1[i][j]==0){
  					printf("  .  ");}
  				else if(table1[i][j]==1){
  					printf("  -  ");}
  				else if(table1[i][j]==2){
  					printf("  @  ");}
  				else if(table1[i][j]==3){
  					printf("  #  ");}
  				else if(table1[i][j]==4){
  					printf("  X  ");}
  				}
  				printf("\t\t");
  				for (x = 0; x < dim; ++x)
  				{
  				if(table2[i][x]==2 || table2[i][x]==0){
  					printf("  ?  ");}
  				else if(table2[i][x]==1){
  					printf("  .  ");}
  				else if(table2[i][x]==3){
  					printf("  @  ");}
  				else if(table2[i][x]==4){
  					printf("  X  ");}
  				}
  				printf("\n\n");}}


void imprimir_Barcos_p0(int dim, int table1[][10], int table2[][10]){
	int i, j, x;

  		for (i = 0; i < dim; ++i)
  	    {
  			for (j = 0; j < dim; ++j)
  			{
  				if(table1[i][j]==0){
  					printf("  ?  ");}
  				else if(table1[i][j]==1){
  					printf("  .  ");}
  				else if(table1[i][j]==2){
  					printf("  ?  ");}
  				else if(table1[i][j]==3){
  					printf("  @  ");}
  				else if(table1[i][j]==4){
  					printf("  X  ");}
  				}
  				printf("\t\t");
  				for (x = 0; x < dim; ++x)
  				{
  				if(table2[i][x]==2 || table2[i][x]==0){
  					printf("  ?  ");}
  				else if(table2[i][x]==1){
  					printf("  .  ");}
  				else if(table2[i][x]==3){
  					printf("  @  ");}
  				else if(table2[i][x]==4){
  					printf("  X  ");}
  				}
  				printf("\n\n");}}


void s_record(int score, FILE *out){
  char name[20];
  time_t curtime;time(&curtime);
  printf("Como te llamas?\n");
  gets(name);

  time_t now;
  struct tm ts;
  char buf[80];
  time(&now);
  ts = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d", &ts);

  out = fopen("ranking.txt","a");
  fprintf(out,"%s",name);
  fprintf(out,"%s","\t\t");
  fprintf(out,"%i",score);
  fprintf(out,"%s","\t\t");
  fprintf(out,"%s",buf);
  fprintf(out,"%s","\n");}


