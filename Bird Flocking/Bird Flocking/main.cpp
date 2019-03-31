
#include<iostream>
#include <cstdlib>
#include <stdint.h>
#include <cstdio>
#include <string.h>

//#include "Bird.h"
//#include "parser.h"
#include "Allegro.h"
#define R 118
#define G 230
#define B 254

#define PRUEBA

#ifndef PRUEBA

#define MAXOPTIONS 7	//maximo de argumentos a ingresar



static int parseCallBack(const char*, const char*, void*);



typedef struct
{
	int birds_num;
	double eyeSight;
	int	 randomJiggleLimit;

}Data_t;


int main(int argc, char const *argv[])
{
	Data_t userData = { 0,0,0 };
	
	//parsing command line
	if (argc == MAXOPTIONS)
	{
		
		if ((parseCmdLine(argc, argv, parseCallBack, &userData)) == ERROR)
		{
			printf("Data entry error.\n");

			return 0; //there was an error, abort
		}
		printf("Data entry success.\n");
	}
	else
	{
		printf("Data entry error.\n");

		return 0; //there was an error, abort
	}









	
}




static int parseCallBack(const char* key, const char* value, void* userData)
{
	
	//checking if key is valid
	if (key != NULL) //es opcion
	{
		if (!(strcmp(key, "birds")))
		{
			if ((atoi(value) > 0) && (atoi(value) <= MAX_BIRDS))
			{
				((Data_t*)userData)->birds_num = atoi(value);
				return true;
			}
			else
			{
				printf("Ingrese la cantidad de birds entre 1 y %d\n", MAX_BIRDS);
				return false;
			}


		}
		else if (!(strcmp(key, "eyeSight")))
		{
			if ((atof(value) >= EYESIGHT_MIN) && (atof(value) <= EYESIGHT_MAX))
			{
				((Data_t*)userData)->eyeSight = atof(value);
				return true;
			}
			else
			{
				printf("Ingrese el eyeSight entre %d y %d\n", EYESIGHT_MIN, EYESIGHT_MAX);
				return false;
			}
		}
		else if (!(strcmp(key, "randomJiggleLimit")))
		{
			if ((atoi(value) >= R_JIGGLE_MIN) && (atoi(value) <= R_JIGGLE_MAX))
			{
				((Data_t*)userData)->randomJiggleLimit = atoi(value);
				return true;
			}
			else
			{
				printf("Ingrese el randomJiggleLimit entre %d y %d\n", R_JIGGLE_MIN, R_JIGGLE_MAX);
				return false;
			}
		}
		else
		{

			return false;
		}
	}

}

#endif // !PRUEBA

#ifdef PRUEBA
/*
int main(void)
{
	AllegroDisplay * aldisplay = (AllegroDisplay *)malloc(sizeof(AllegroDisplay));
	aldisplay->initAllegroDisplay("textfont.ttf", 70, 100, "bird.png");
	aldisplay->setDisplayColor(R, G, B);
	aldisplay->updateBird(50, 35, 1.0);
	aldisplay->updateDisplay();
	char c = getchar();
	aldisplay->destroyAllegroDisplay();
	free(aldisplay);

}
*/
int main(void)
{

}

#endif // PRUEBA






