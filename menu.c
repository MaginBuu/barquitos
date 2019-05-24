#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "proc.h"
#include "procmenu.h"
#include "libvaixells.h"

FILE *in;


enum{
  ESC         = 27,
  Enter       = 13,
  KEY_DOWN    = 256 + 80,
  KEY_UP      = 256 + 72,
};




int main(int partida){
    int i, tecla, lvl, players, dim, barcos;
    i=1;
    // variables necesarias para cargar un juego:
    int s1[10][10], s2[10][10], barcos_p1=0, barcos_p2=0, turno=0, lanzamientos_totales=0, n1=-1, n2=-1, lanzamientos1[10], lanzamientos2[10];
    float efectivitat1=0, efectivitat2=0, puntuacion_total2=0, puntuacion_total1=0;
    system("cls");
    do{

        if(i == 1){printf("\n=> Crear partida");}
        else {printf("\n    Crear partida");}
        if(i == 2){printf("\n=> Recuperar partida");}
        else {printf("\n    Recuperar partida");}


        if(partida == 0){
            if(i == 3){printf("\n=> Continuar partida");}
            else {printf("\n    Continuar partida");}
            if(i == 4){printf("\n=> Guardar partida");}
            else {printf("\n    Guardar partida");}}

        if(i == 5){printf("\n=> Ver ranking");}
        else {printf("\n    Ver ranking");}
        if(i == 6){printf("\n=> Salir del juego\n");}
        else {printf("\n    Salir del juego\n");}

        tecla = getch();
        if (tecla == ESC){system("cls"); return 5;}
        if (tecla == 0 || tecla == 224){tecla = 256 + getch();}

        if(tecla == KEY_DOWN && i < 6){i++;}
        if(tecla == KEY_UP && i > 1){i--;}
        if(tecla == KEY_DOWN && i == 3 && partida!=0){i=5;}
        if(tecla == KEY_UP && partida != 0 && i == 4){i=2;}

        system("cls");

    }while(tecla != Enter);
    switch(i){
            case 1:

                menu_players(&lvl, &players, &barcos, &dim);
                dim+=7;
                if(players==3){partida_p1_vs_p2(dim,barcos,players,lvl,s1,s2,barcos_p1,barcos_p2,turno,lanzamientos_totales,n1,n2,lanzamientos1,lanzamientos2,efectivitat1,efectivitat2,puntuacion_total1,puntuacion_total2);}
                else if(players==2){partida_p1_vs_IA(dim,barcos,players,lvl,s1,s2,barcos_p1,barcos_p2,turno,lanzamientos_totales,n1,n2,lanzamientos1,lanzamientos2,efectivitat1,efectivitat2,puntuacion_total1,puntuacion_total2);}
                else if(players==1){partida_IA_vs_IA(dim,barcos,players,lvl,s1,s2,barcos_p1,barcos_p2,turno,lanzamientos_totales,n1,n2,lanzamientos1,lanzamientos2,efectivitat1,efectivitat2,puntuacion_total1,puntuacion_total2);}

                    break;

            case 2:
                load(&dim, s1, s2, &barcos_p1, &barcos_p2, &turno, &lanzamientos_totales, &n1, &n2, lanzamientos1, lanzamientos2, &players, &lvl, &efectivitat1, &efectivitat2, &puntuacion_total2, &puntuacion_total1, &in);
                if(players==3){partida_p1_vs_p2(dim,barcos,players,lvl,s1,s2,barcos_p1,barcos_p2,turno,lanzamientos_totales,n1,n2,lanzamientos1,lanzamientos2,efectivitat1,efectivitat2,puntuacion_total1,puntuacion_total2);}
                else if (players==2){partida_p1_vs_IA(dim,barcos,lvl,players,s1,s2,barcos_p1,barcos_p2,turno,lanzamientos_totales,n1,n2,lanzamientos1,lanzamientos2,efectivitat1,efectivitat2,puntuacion_total1,puntuacion_total2);}
                else if (players==1){partida_IA_vs_IA(dim,barcos,players,lvl,s1,s2,barcos_p1,barcos_p2,turno,lanzamientos_totales,n1,n2,lanzamientos1,lanzamientos2,efectivitat1,efectivitat2,puntuacion_total1,puntuacion_total2);}
                break;
            case 3: return -1;break;
            case 4: return 1;break;
            case 5: records();break;
            case 6: return 0;}
            return 0;}
