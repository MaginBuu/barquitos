#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "proc.h"

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

int disparar(int dim, int table[][10], int px, int py, int *mida_barco){
	bool vertical=false, horizontal=false, completo=true;
	int i=0, j=0, puntuacion=0;

	if(table[py][px]==0){table[py][px]=1;*mida_barco=0;puntuacion=1;}
	if(table[py][px]==2){
		table[py][px]=3;
		if((table[py][px+1]==2 && px!=dim-1) || (table[py][px-1]==2 && px!=0) || (table[py][px+1]==3 && px!=dim-1) || (table[py][px-1]==3 && px!=0)){horizontal=true;}
		if((table[py+1][px]==2 && py!=dim-1) || (table[py-1][px]==2 && py!=0) || (table[py-1][px]==3 && py!=0) || (table[py+1][px]==3 && py!=dim-1)){vertical=true;}
		// barco de 1
		if(vertical==false && horizontal==false){table[py][px]=4; *mida_barco=1; puntuacion=4;}
		// otros barcos
		else if(horizontal==true){
			if(table[py][px-1]==3 && px!=0){i++;
				if(table[py][px-2]==2 && px!=1){completo=false;}
				else if(table[py][px-2]==3 && px!=1){i++;
					if(table[py][px-3]==3 && px!=3){i++;}
					else if(table[py][px-3]==2 && px!=3){completo=false;}}}
			if(table[py][px-1]==2 && px!=0){completo=false;}
			if(table[py][px+1]==3 && px!=dim-1){j++;
				if(table[py][px+2]==2 && px!=dim-2){completo=false;}
				else if(table[py][px+2]==3 && px!=dim-2){j++;
					if(table[py][px+3]==3 && px!=dim-3){j++;}
					else if(table[py][px+3]==2 && px!= dim-3){completo=false;}}}
			if(table[py][px+1]==2 && px!=dim-1){completo=false;}
			*mida_barco=i+j+1;
			if(completo==true){
				puntuacion=4;
				table[py][px]=4;
				while(i>0){
					table[py][px-i]=4;
					i--;}
				while(j>0){
					table[py][px+j]=4;
					j--;}}
			else{table[py][px]=3;puntuacion=3;}}

		else if(vertical==true){
			if(table[py-1][px]==3 && py!=0){i++;
				if(table[py-2][px]==2 && py!=1){completo=false;}
				else if(table[py-2][px]==3 && py!=1){i++;
					if(table[py-3][px]==3 && py!=2){i++;}
					else if(table[py-3][px]==2 && py!=3){completo=false;}}}
			if(table[py-1][px]==2 && py!=0){completo=false;}
			if(table[py+1][px]==3 && py!=dim-1){j++;
				if(table[py+2][px]==2 && py!=dim-2){completo=false;}
				else if(table[py+2][px]==3 && py!=dim-2){j++;
					if(table[py+3][px]==3 && py!=dim-3){j++;}
					else if(table[py+3][px]==2 && py!=dim-3){completo=false;}}}
			if(table[py+1][px]==2 && py!=dim-1){completo=false;}
			*mida_barco=i+j+1;
			if(completo==true){
				puntuacion=4;
				table[py][px]=4;
				while(i>0){
					table[py-i][px]=4;
					i--;}
				while(j>0){
					table[py+j][px]=4;
					j--;}}
			else{table[py][px]=3;puntuacion=3;}}
		}
		return puntuacion;}

void colocar_barcos_aleatoriamente(int dim, int table[][10]){
	int b1=0, b2=0, b3=0, b4=0, b5=0, b6=0, b7=0, b8=0, b9=0, b10=0, py, px, i, j, z=0, x=0;
	bool horizontal;

	while((b10!=2 || b9!=2 || b8!=2 || b7!=2 || b6!=2 || b5!=2 || b4!=2 || b3!=2 || b2!=2 || b1!=2) && z<10000){
	b10=0;b9=0;b8=0;b7=0;b6=0;b5=0;b4=0;b3=0;b2=0;b1=0;x=0;

  	for (i = 0; i < dim; ++i)
 	{
  		for (j = 0; j < dim; ++j)
  		{
  			table[i][j]=0;}}

  		while(b10!=2 && x<100000){
			px=rand()%dim;
	    	py=rand()%dim;
	    	i=rand()%2;
	    	if(i==0){horizontal=true;}
	    	else{horizontal=false;}
	   		if(horizontal == true && table[py][px]!=2 && table[py][px+1]!=2 && table[py][px+2]!=2 && table[py][px+3]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+1][px+2]!=2 && table[py][px+4]!=2 && table[py-1][px+2]!=2 && table[py-1][px+3]!=2 && table[py+1][px+3]!=2 && table[py-1][px+4]!=2 && table[py+1][px+4]!=2){
	    		b10=2;
	    		table[py][px] = 2;
	    		table[py][px+1] = 2;
	    		table[py][px+2] = 2;
	    		table[py][px+3] = 2;}
	   		else if(horizontal == false && table[py][px]!=2 && table[py+1][px]!=2 && table[py+2][px]!=2 && table[py+3][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+4][px]!=2 && table[py+2][px-1]!=2 && table[py+2][px+1]!=2 && table[py+3][px-1]!=2 && table[py+3][px+1]!=2 && table[py+4][px-1]!=2 && table[py+4][px+1]!=2){
	    		b10=2;
	    		table[py][px] = 2;
	    		table[py+1][px] = 2;
	    		table[py+2][px] = 2;
	    		table[py+3][px] = 2;}
	    		x++;}

    	// barco 9
	    while(b9!=2 && x<100000){
	    	px=rand()%dim;
	    	py=rand()%dim;
	    	i=rand()%2;
	    	if(i==0){horizontal=true;}
	    	else{horizontal=false;}
	   		if(horizontal == true && table[py][px]!=2 && table[py][px+1]!=2 && table[py][px+2]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+1][px+2]!=2 && table[py][px+3]!=2 && table[py-1][px+2]!=2 && table[py-1][px+3]!=2 && table[py+1][px+3]!=2){
	    		b9=2;
	    		table[py][px] = 2;
	    		table[py][px+1] = 2;
	    		table[py][px+2] = 2;}
	   		else if(horizontal == false && table[py][px]!=2 && table[py+1][px]!=2 && table[py+2][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+3][px]!=2 && table[py+2][px-1]!=2 && table[py+2][px+1]!=2 && table[py+3][px-1]!=2 && table[py+3][px+1]!=2){
	    		b9=2;
	    		table[py][px] = 2;
	    		table[py+1][px] = 2;
		    	table[py+2][px] = 2;}
		    	x++;}

		    // barco 8
		while(b8!=2 && x<100000){
	   		px=rand()%dim;
	   		py=rand()%dim;
	   		i=rand()%2;
	   		if(i==0){horizontal=true;}
	   		else{horizontal=false;}
			if(horizontal == true && table[py][px]!=2 && table[py][px+1]!=2 && table[py][px+2]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+1][px+2]!=2 && table[py][px+3]!=2 && table[py-1][px+2]!=2 && table[py-1][px+3]!=2 && table[py+1][px+3]!=2){
	   			b8=2;
	   			table[py][px] = 2;
	   			table[py][px+1] = 2;
	   			table[py][px+2] = 2;}
			else if(horizontal == false && table[py][px]!=2 && table[py+1][px]!=2 && table[py+2][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+3][px]!=2 && table[py+2][px-1]!=2 && table[py+2][px+1]!=2 && table[py+3][px-1]!=2 && table[py+3][px+1]!=2){
	   			b8=2;
	   			table[py][px] = 2;
	   			table[py+1][px] = 2;
	   			table[py+2][px] = 2;}
	   			x++;}

	   		// barco 7
		while(b7!=2 && x<100000){
			px=rand()%dim;
	    	py=rand()%dim;
	    	i=rand()%2;
	    	if(i==0){horizontal=true;}
	    	else{horizontal=false;}
			if(horizontal == true && table[py][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+1][px+2]!=2 && table[py][px+2]!=2 && table[py-1][px+2]!=2){
	        	b7=2;
	        	table[py][px] = 2;
	        	table[py][px+1] = 2;}
	    	else if(horizontal == false && table[py][px]!=2 && table[py+1][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+2][px]!=2 && table[py+2][px-1]!=2 && table[py+2][px+1]!=2){
	        	b7=2;
	        	table[py][px] = 2;
	        	table[py+1][px] = 2;}
	        	x++;}

	        // barco 6
	    while(b6!=2 && x<100000){
	    	px=rand()%dim;
	       	py=rand()%dim;
	       	i=rand()%2;
	       	if(i==0){horizontal=true;}
	       	else{horizontal=false;}
			if(horizontal == true && table[py][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+1][px+2]!=2 && table[py][px+2]!=2 && table[py-1][px+2]!=2){
	        	b6=2;
	        	table[py][px] = 2;
	        	table[py][px+1] = 2;}
	    	else if(horizontal == false && table[py][px]!=2 && table[py+1][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+2][px]!=2 && table[py+2][px-1]!=2 && table[py+2][px+1]!=2){
	        	b6=2;
	        	table[py][px] = 2;
	        	table[py+1][px] = 2;}
	        	x++;}

	       	// barco 5
	    while(b5!=2 && x<100000){
	    	px=rand()%dim;
	       	py=rand()%dim;
	       	i=rand()%2;
	       	if(i==0){horizontal=true;}
	       	else{horizontal=false;}
			if(horizontal == true && table[py][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+1][px+2]!=2 && table[py][px+2]!=2 && table[py-1][px+2]!=2){
	        	b5=2;
	        	table[py][px] = 2;
	        	table[py][px+1] = 2;}
	    	else if(horizontal == false && table[py][px]!=2 && table[py+1][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2 && table[py+2][px]!=2 && table[py+2][px-1]!=2 && table[py+2][px+1]!=2){
	        	b5=2;
	        	table[py][px] = 2;
	        	table[py+1][px] = 2;}
	        	x++;}

	        // barco 4
	    while(b4!=2 && x<100000){
	    	px=rand()%dim;
	    	py=rand()%dim;
	    	if(table[py][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2&& table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2){
	    		b4=2;
	    		table[py][px] = 2;}
	    	x++;}

	    		// barco 3
	    while(b3!=2 && x<100000){
	    	px=rand()%dim;
	    	py=rand()%dim;
	    	if(table[py][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2&& table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2){
	    		b3=2;
	    		table[py][px] = 2;}
	    	x++;}

	    		// barco 2
	    while(b2!=2 && x<100000){
	    	px=rand()%dim;
	    	py=rand()%dim;
	    	if(table[py][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2&& table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2){
	    		b2=2;
	    		table[py][px] = 2;}
	    	x++;}

	    		// barco 1
	    while(b1!=2 && x<100000){
	    	px=rand()%dim;
	    	py=rand()%dim;
	    	if(table[py][px]!=2 && table[py][px+1]!=2 && table[py+1][px+1]!=2 && table[py+1][px]!=2&& table[py-1][px]!=2 && table[py][px-1]!=2 && table[py-1][px-1]!=2 && table[py-1][px+1]!=2 && table[py+1][px-1]!=2){
	    		b1=2;
	    		table[py][px] = 2;}
	    x++;}
	z++;}

	if(z==10000){printf("ERROR\n");}}


void colocar_barcos_manualmente(int dim, int table[][10])
{
  int ch, px=0, py=0, i, j, b1=0, b2=0, b3=0, b4=0, b5=0, b6=0, b7=0, b8=0, b9=0, b10=0;
  bool horizontal=true;
  srand(time(NULL));

  for (i = 0; i < dim; ++i)
  {
    for (j = 0; j < dim; ++j)
    {
      table[i][j]=0;
    }
  }
  system("cls");

  do{

    if(b5==1 || b6==1 || b7==1 || b8==1 || b9==1 || b10==1){printf("TAB=girar\n\n");}
    for (i = 0; i < dim; ++i)
    {
      for (j = 0; j < dim; ++j)
      {
        if (px==j && py==i && (b1!=1 && b2!=1 && b3!=1 && b4!=1 && b5!=1 && b6!=1 && b7!=1 && b8!=1 && b9!=1 && b10!=1)){
          if (table[i][j]==0){printf(" [0] ");}
          if (table[i][j]==2){printf(" [2] ");}
        }
                    /*mostar los barcos dentro del tablero*/

                            /* barcos 1, 2, 3 y 4*/
            else if((b1==1 || b2==1 || b3==1 || b4==1) && px==j && py==i){printf(" [2] ");}

                            /*barcos 5, 6 y 7*/
        else if((b5==1 || b6==1 || b7==1) && px==j && py==i && horizontal==true){printf(" [2  ");}
            else if((b5==1 || b6==1 || b7==1) && px==j-1 && py==i && horizontal==true){printf("  2] ");}
            else if((b5==1 || b6==1 || b7==1) && px==j && py==i && horizontal==false){printf(" [2] ");}
            else if((b5==1 || b6==1 || b7==1) && px==j && py==i-1 && horizontal==false){printf(" [2] ");}

                            /*barcos 8 y 9*/
        else if((b8==1 || b9==1) && px==j && py==i && horizontal==true){printf(" [2  ");}
            else if((b8==1 || b9==1) && px==j-1 && py==i && horizontal==true){printf("  2  ");}
            else if((b8==1 || b9==1) && px==j-2 && py==i && horizontal==true){printf("  2] ");}
            else if((b8==1 || b9==1) && px==j && py==i && horizontal==false){printf(" [2] ");}
            else if((b8==1 || b9==1) && px==j && py==i-1 && horizontal==false){printf(" [2] ");}
            else if((b8==1 || b9==1) && px==j && py==i-2 && horizontal==false){printf(" [2] ");}

                            /*barco 10*/
        else if((b10==1) && px==j && py==i && horizontal==true){printf(" [2  ");}
            else if((b10==1) && px==j-1 && py==i && horizontal==true){printf("  2 ");}
            else if((b10==1) && px==j-2 && py==i && horizontal==true){printf("   2 ");}
            else if((b10==1) && px==j-3 && py==i && horizontal==true){printf("   2] ");}
            else if((b10==1) && px==j && py==i && horizontal==false){printf(" [2] ");}
            else if((b10==1) && px==j && py==i-1 && horizontal==false){printf(" [2] ");}
            else if((b10==1) && px==j && py==i-2 && horizontal==false){printf(" [2] ");}
            else if((b10==1) && px==j && py==i-3 && horizontal==false){printf(" [2] ");}


        else printf("  %i  ",table[i][j]);
      }

      printf("\n\n");
    }


    /* escribir los barcos,
    bx=0 = barco no usado, bx=1 = poniendo barco bx=2 = barco usado*/

    printf("  BARCOS:\n\n");

            /*barco 1*/
    if(b1==0 && (py!=dim || px!=0)){printf("    [2]");}
    else if(b1==0 && py==dim && px==0){printf("  =>[2]");}
    else if(b1!=0 && py==dim && px==0){printf("  =>[-]");}
    else {printf("    [-]");}


               /*barco 2*/
    if(b2==0 && (py!=dim || px!=1)){printf("       [2]");}
    else if(b2==0 && py==dim && px==1){printf("     =>[2]");}
    else if(b2!=0 && py==dim && px==1){printf("     =>[-]");}
    else{printf("       [-]");}

               /*barco 3*/
    if(b3==0 && (py!=dim || px!=2)){printf("       [2]");}
    else if(b3==0 && py==dim && px==2){printf("     =>[2]");}
    else if(b3!=0 && py==dim && px==2){printf("     =>[-]");}
    else{printf("       [-]");}

               /*barco 4*/
    if(b4==0 && (py!=dim || px!=3)){printf("       [2]\n");}
    else if(b4==0 && py==dim && px==3){printf("     =>[2]\n");}
    else if(b4!=0 && py==dim && px==3){printf("     =>[-]\n");}
    else{printf("       [-]\n");}

            /*barco 5*/
    if(b5==0 && (py!=dim+1 || px!=0)){printf("    [2 2]");}
    else if(b5==0 && py==dim+1 && px==0){printf("  =>[2 2]");}
    else if(b5!=0 && py==dim+1 && px==0){printf("  =>[- -]");}
    else{printf("    [- -]");}

            /*barco 6*/
    if(b6==0 && (py!=dim+1 || px!=1)){printf("     [2 2]");}
    else if(b6==0 && py==dim+1 && px==1){printf("   =>[2 2]");}
    else if(b6!=0 && py==dim+1 && px==1){printf("   =>[- -]");}
    else{printf("     [- -]");}

            /*barco 7*/
    if(b7==0 && (py!=dim+1 || px!=2)){printf("     [2 2]\n");}
    else if(b7==0 && py==dim+1 && px==2){printf("   =>[2 2]\n");}
    else if(b7!=0 && py==dim+1 && px==2){printf("   =>[- -]\n");}
    else{printf("     [- -]\n");}

            /*barco 8*/
    if(b8==0 && (py!=dim+2 || px!=0)){printf("    [2 2 2]");}
    else if(b8==0 && py==dim+2 && px==0){printf("  =>[2 2 2]");}
    else if(b8!=0 && py==dim+2 && px==0){printf("  =>[- - -]");}
    else{printf("    [- - -]");}

            /*barco 8*/
    if(b9==0 && (py!=dim+2 || px!=1)){printf("   [2 2 2]\n");}
    else if(b9==0 && py==dim+2 && px==1){printf(" =>[2 2 2]\n");}
    else if(b9!=0 && py==dim+2 && px==1){printf(" =>[- - -]\n");}
    else{printf("   [- - -]\n");}

            /*barco 10*/
    if(b10==0 && (py!=dim+3 || px!=0)){printf("    [2 2 2 2]\n");}
    else if(b10==0 && py==dim+3 && px==0){printf("  =>[2 2 2 2]\n");}
    else if(b10!=0 && py==dim+3 && px==0){printf("  =>[- - - -]\n");}
    else{printf("    [- - - -]\n");}

    ch = getch();
                        /*programacion barcos*/

                /*cambiar sentido barcos*/
    if(ch == 9 && (b5 == 1 || b6 == 1 || b7 == 1 || b8==1 || b9==1 || b10==1)){
    if(horizontal==false){horizontal=true;}
    else{horizontal=false;}}

                            /*barco 1*/
    if(ch==13){
      if (py == dim && px==0 && b1 == 0){b1=1; px=0; py=0;}
      else if (b1 == 1 && table[py][px]!=2 && (table[py][px+1]!=2 || px==dim) && (table[py+1][px+1]!=2 || py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2 || py==dim-1)){
          b1++;
          table[py][px] = 2;
          px=0; py=0;}

                            /*barco 2*/
      else if (py == dim && px==1 && b2 == 0){b2=1; px=0; py=0;}
      else if (b2 == 1 && table[py][px]!=2 && (table[py][px+1]!=2 || px==dim) && (table[py+1][px+1]!=2 || py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2 || py==dim-1)){
          b2++;
          table[py][px] = 2;
          px=0; py=0;}

                            /*barco 3*/
      else if (py == dim && px==2 && b3 == 0){b3=1; px=0; py=0;}
      else if (b3 == 1 && table[py][px]!=2 && (table[py][px+1]!=2 || px==dim) && (table[py+1][px+1]!=2 || py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2 || py==dim-1)){
          b3++;
          table[py][px] = 2;
          px=0; py=0;}

                            /*barco 4*/
      else if (py == dim && px==3 && b4 == 0){b4=1; px=0; py=0;}
      else if (b4 == 1 && table[py][px]!=2 && (table[py][px+1]!=2 || px==dim) && (table[py+1][px+1]!=2 || py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2 || py==dim-1)){
          b4++;
          table[py][px] = 2;
          px=0; py=0;}

                            /*barco 5*/
      else if (py == dim+1 && px==0 && b5 == 0){b5=1; px=0; py=0;}
      else if (b5 == 1  && horizontal == true && table[py][px]!=2 && (table[py][px+1]!=2 || px==dim-1) && (table[py+1][px+1]!=2  || py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2 || py==dim-1) && (table[py+1][px+2]!=2 || py==dim-1) && (table[py][px+2]!=2 || px==dim-2) && (table[py-1][px+2]!=2 || py==0)){
          b5++;
          table[py][px] = 2;
          table[py][px+1] = 2;
          px=0; py=0;}
      else if (b5 == 1 && horizontal == false && table[py][px]!=2 && (table[py+1][px]!=2 || py==dim-1) && (table[py][px+1]!=2 || px==dim-1) && (table[py+1][px+1]!=2 || px==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2  || px==0) && (table[py-1][px+1]!=2 || px==dim-1) && (table[py+1][px-1]!=2  || px==0) && (table[py+2][px]!=2 || py==dim-2) && (table[py+2][px-1]!=2 || px==0) && (table[py+2][px+1]!=2 || px==dim-1)){
          b5++;
          table[py][px] = 2;
          table[py+1][px] = 2;
          px=0; py=0;}

                            /*barco 6*/
      else if (py == dim+1 && px==1 && b6 == 0){b6=1; px=0; py=0;}
      else if (b6 == 1 && horizontal == true && table[py][px]!=2 && (table[py][px+1]!=2 || px==dim-1) && (table[py+1][px+1]!=2  || py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2 || py==dim-1) && (table[py+1][px+2]!=2 || py==dim-1) && (table[py][px+2]!=2 || px==dim-2) && (table[py-1][px+2]!=2 || py==0)){
          b6++;
          table[py][px] = 2;
          table[py][px+1] = 2;
          px=0; py=0;}
      else if (b6 == 1 && horizontal == false && table[py][px]!=2 && (table[py+1][px]!=2 || px==dim-1) && (table[py][px+1]!=2 || px==dim-1) && (table[py+1][px+1]!=2 || px==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2  || px==0) && (table[py-1][px+1]!=2 || px==dim-1) && (table[py+1][px-1]!=2  || px==0) && (table[py+2][px]!=2 || py==dim-2) && (table[py+2][px-1]!=2 || px==0) && (table[py+2][px+1]!=2 || px==dim-1)){
          b6++;
          table[py][px] = 2;
          table[py+1][px] = 2;
          px=0; py=0;}

                            /*barco 7*/
      else if (py == dim+1 && px==2 && b7 == 0){b7=1; px=0; py=0;}
      else if (b7 == 1 && horizontal == true && table[py][px]!=2 && (table[py][px+1]!=2 || px==dim-1) && (table[py+1][px+1]!=2  || py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2 || py==dim-1) && (table[py+1][px+2]!=2 || py==dim-1) && (table[py][px+2]!=2 || px==dim-2) && (table[py-1][px+2]!=2 || py==0)){
          b7++;
          table[py][px] = 2;
          table[py][px+1] = 2;
          px=0; py=0;}
      else if (b7 == 1 && horizontal == false && table[py][px]!=2 && (table[py+1][px]!=2 || py==dim-1) && (table[py][px+1]!=2 || px==dim-1) && (table[py+1][px+1]!=2 || px==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2  || px==0) && (table[py-1][px+1]!=2 || px==dim-1) && (table[py+1][px-1]!=2  || px==0) && (table[py+2][px]!=2 || py==dim-2) && (table[py+2][px-1]!=2 || px==0) && (table[py+2][px+1]!=2 || px==dim-1)){
          b7++;
          table[py][px] = 2;
          table[py+1][px] = 2;
          px=0; py=0;}

                                    /*barco 8*/
      else if (py == dim+2 && px==0 && b8 == 0){b8=1; px=0; py=0;}
      else if (b8 == 1 && horizontal == true && table[py][px]!=2 && (table[py][px+1]!=2 || px==dim-1) && (table[py][px+2]!=2 || px==dim-2) && (table[py+1][px+1]!=2 ||  py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2  || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2  || py==dim-1) && (table[py+1][px+2]!=2 || py==dim-1) && (table[py][px+3]!=2 || px==dim-3) && (table[py-1][px+2]!=2 || py==0) && (table[py-1][px+3]!=2 || py==0)&& (table[py+1][px+3]!=2 || py==dim-1)){
          b8++;
          table[py][px] = 2;
          table[py][px+1] = 2;
          table[py][px+2] = 2;
          px=0; py=0;}
      else if (b8 == 1 && horizontal == false && table[py][px]!=2 && (table[py+1][px]!=2 && py!=dim-2) && table[py+2][px]!=2 && (table[py][px+1]!=2 || px==dim-1) && (table[py+1][px+1]!=2 || px==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || px==0) && (table[py-1][px+1]!=2 || px==dim-1 || py==0) && (table[py+1][px-1]!=2 || px==0) && (table[py+3][px]!=2 || py==dim-2) && (table[py+2][px-1]!=2 || px==0) && (table[py+2][px+1]!=2 || px==dim-1) && (table[py+3][px-1]!=2 || py==dim-2 || px==0) && (table[py+3][px+1]!=2 || px==dim-1 || py==dim-2)){
          b8++;
          table[py][px] = 2;
          table[py+1][px] = 2;
          table[py+2][px] = 2;
          px=0; py=0;}

                                            /*barco 9*/
      else if (py == dim+2 && px==1 && b9 == 0){b9=1; px=0; py=0;}
      else if (b9 == 1 && horizontal == true && table[py][px]!=2 && table[py][px+1]!=2 && table[py][px+2]!=2 && (table[py+1][px+1]!=2 ||  py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2  || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2  || py==dim-1) && (table[py+1][px+2]!=2 || py==dim-1) && (table[py][px+3]!=2 || px==dim-3) && (table[py-1][px+2]!=2 || py==0) && (table[py-1][px+3]!=2 || py==0)&& (table[py+1][px+3]!=2 || py==dim-1)){
          b9++;
          table[py][px] = 2;
          table[py][px+1] = 2;
          table[py][px+2] = 2;
          px=0; py=0;}
      else if (b9 == 1 && horizontal == false && table[py][px]!=2 && table[py+1][px]!=2 && table[py+2][px]!=2 && (table[py][px+1]!=2 || px==dim-1) && (table[py+1][px+1]!=2 || px==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || px==0) && (table[py-1][px+1]!=2 || px==dim-1 || py==0) && (table[py+1][px-1]!=2 || px==0) && (table[py+3][px]!=2 || py==dim-2) && (table[py+2][px-1]!=2 || px==0) && (table[py+2][px+1]!=2 || px==dim-1) && (table[py+3][px-1]!=2 || py==dim-2 || px==0) && (table[py+3][px+1]!=2 || px==dim-1 || py==dim-2)){
          b9++;
          table[py][px] = 2;
          table[py+1][px] = 2;
          table[py+2][px] = 2;
          px=0; py=0;}

                                                    /*barco 10*/
      else if (py == dim+3 && px==0 && b10 == 0){b10=1; px=0; py=0;}
      else if (b10 == 1 && horizontal == true && table[py][px]!=2 && table[py][px+1]!=2 && table[py][px+2]!=2 && table[py][px+3]!=2 && (table[py+1][px+1]!=2 || py==dim-1) && (table[py+1][px]!=2 || py==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || px==0 || py==0) && (table[py-1][px+1]!=2 || py==0) && (table[py+1][px-1]!=2 || py==dim-1 || px==0) && (table[py+1][px+2]!=2 || py==dim-1) && (table[py][px+4]!=2 || px==dim-3) && (table[py-1][px+2]!=2 || py==0) && (table[py-1][px+3]!=2 || py==0) && (table[py+1][px+3]!=2 || py==dim-1) && (table[py-1][px+4]!=2 || py==0 || px==dim-3) && (table[py+1][px+4]!=2 || py==dim-1 || px==dim-3)){
          b10++;
          table[py][px] = 2;
          table[py][px+1] = 2;
          table[py][px+2] = 2;
          table[py][px+3] = 2;
          px=0; py=0;}
      else if (b10 == 1 && horizontal == false && table[py][px]!=2 && table[py+1][px]!=2 && table[py+2][px]!=2 && table[py+3][px]!=2 && (table[py][px+1]!=2 || py==dim-1) && (table[py+1][px+1]!=2 || px==dim-1) && (table[py-1][px]!=2 || py==0) && (table[py][px-1]!=2 || px==0) && (table[py-1][px-1]!=2 || px==0 || py==0) && (table[py-1][px+1]!=2 || py==0 || px==dim-1) && (table[py+1][px-1]!=2 || px==0) && (table[py+4][px]!=2 || py==dim-3) && (table[py+2][px-1]!=2 || px==0) && (table[py+2][px+1]!=2 || px==dim-1) && (table[py+3][px-1]!=2 || px==0) && (table[py+3][px+1]!=2 || px==dim-1) && (table[py+4][px-1]!=2 || px==0 || py==dim-3) && (table[py+4][px+1]!=2 || py==dim-3 || px==dim-1)){
          b10++;
          table[py][px] = 2;
          table[py+1][px] = 2;
          table[py+2][px] = 2;
          table[py+3][px] = 2;
          px=0; py=0;}}

    else{    /*teclas de direccion*/
      if ( ch == 0 || ch == 224 ){ch = 256 + getch();}
      if ( ch == ARROW_UP ){py-=1;}
      if ( ch == ARROW_DOWN ){py+=1;}
      if ( ch == ARROW_LEFT ){px-=1;}
      if ( ch == ARROW_RIGHT ){px+=1;}


          /*limites del tablero*/
      if (b1==1 || b2==1 || b3==1 || b4==1 || b5==1 || b6==1 || b7==1 || b8==1 || b9==1 || b10==1){
          if(horizontal==true){
            if (px<0 && (b1==1||b2==1||b3==1||b4==1)){px=dim-1;}
            else if(px<0 && (b5==1||b6==1||b7==1)){px=dim-2;}
            else if(px<0 && (b8==1||b9==1)){px=dim-3;}
            else if(px<0 && (b10==1)){px=dim-4;}
            else if (px>dim-1 && (b1==1||b2==1||b3==1||b4==1)){px=0;}
            else if (px>dim-2 && (b5==1||b6==1||b7==1)){px=0;}
            else if (px>dim-3 && (b8==1||b9==1)){px=0;}
            else if (px>dim-4 && (b10==1)){px=0;}
            else if (py<0){py=dim-1;}
            else if (py>dim-1){py=0;}}
          else{
            if(py<0 && (b1==1||b2==1||b3==1||b4==1)){py=dim-1;}
            else if(py>dim-1 && (b1==1||b2==1||b3==1||b4==1)){py=0;}
            else if(py<0 && (b5==1||b6==1||b7==1)){py=dim-2;}
            else if(py>dim-2 && (b5==1||b6==1||b7==1)){py=0;}
            else if(py<0 && (b8==1||b9==1)){py=dim-3;}
            else if(py>dim-3 && (b8==1||b9==1)){py=0;}
            else if(py<0 && (b10==1)){py=dim-4;}
            else if(py>dim-4 && (b10==1)){py=0;}
            else if (px<0){px=dim-1;}
            else if (px>dim-1){px=0;}}}

      else{
      if (px<0 && py<dim){px=dim-1;}
      else if(px<0 && py==dim){px=3;}
      else if(px<0 && py==dim+1){px=2;}
      else if(px<0 && py==dim+2){px=1;}
      else if(px<0 && py==dim+3){px=0;}
      if (px>dim-1 && py<dim){px=0;}
      else if(px>3 && py==dim){px=0;}
      else if(px>2 && py==dim+1){px=0;}
      else if(px>1 && py==dim+2){px=0;}
      else if(px>0 && py==dim+3){px=0;}
      if (py<0){py=dim+3;}
      if (py>dim+3){py=0;}}}

    system("cls");


  }while(b1!=2 || b2!=2 || b3!=2 || b4!=2 || b5!=2 || b6!=2 || b7!=2 || b8!=2 || b9!=2 || b10!=2);}