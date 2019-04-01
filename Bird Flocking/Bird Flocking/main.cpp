
#include<iostream>
#include <cstdlib>
#include <stdint.h>
#include <cstdio>
#include <string.h>

#include "Bird.h"
#include "parser.h"
#include "Allegro.h"
#include "Random.h"
#define HEIGHT 70
#define WIDTH 100
#define R 118
#define G 230
#define B 254
#define RUNNINGSPEED 0.000000001
#define STEP 0.01

//#define PRUEBA

#ifndef PRUEBA

#define MAXOPTIONS 7	//maximo de argumentos a ingresar



static int parseCallBack(const char*, const char*, void*);

enum modes { mode1 = 1, mode2};

typedef struct
{
	int birds_num;
	double eyeSight;
	int	 randomJiggleLimit;
	int mode;

}Data_t;


int main(int argc, char const *argv[])
{
	Data_t * userData = (Data_t*)malloc((sizeof(Data_t)));

	srand(time(NULL));
	
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
	

	//aca empieza la simulacion
	Bird * bird = new Bird[userData->birds_num];
	AllegroDisplay * aldisplay = new AllegroDisplay;
	aldisplay->initAllegroDisplay("textfont.ttf", HEIGHT , WIDTH , "bird.png");
	aldisplay->initTimer();

	bool quit = false;
	double r_jiggle_limit = R_JIGGLE_MAX;
	int i;
	//set velocity depending on mode
	switch (userData->mode)
	{
		case mode1:
			for (i = 0; i < userData->birds_num; i++)
			{
				bird[i].set_velocity(VELOCITY_MIN);
			}
			break;
		case mode2:
			for (i = 0; i < userData->birds_num; i++)
			{
				bird[i].set_velocity(randIntBetween(VELOCITY_MIN, VELOCITY_MAX));
			}
			break;
	}

	//set eyesight, rjiggle, max pos, pos
	for (i = 0; i < userData->birds_num; i++)
	{
		bird[i].set_eyesight(userData->eyeSight); //hay un casteo implicito (double)->(uint)
		bird[i].set_rjiggle(randIntBetween(0, r_jiggle_limit)); //no deberia ir en rad?
		bird[i].set_max_pos(WIDTH, HEIGHT);
		bird[i].set_pos(randDoubleBetween(0.0, WIDTH), randDoubleBetween(0.0, HEIGHT));
	}

	int j = 0;
	while (!quit)
	{
		switch (aldisplay->getNextEvent())
		{
		case timer_:


		}
		
	}

	aldisplay->setDisplayColor(R, G, B);
	aldisplay->updateBird(50, 35, 1.0);
	aldisplay->updateDisplay();
	char c = getchar();
	aldisplay->destroyAllegroDisplay();
	delete[] aldisplay;
	delete[] bird;







	
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



#endif // PRUEBA






