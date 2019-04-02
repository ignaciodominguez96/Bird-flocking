
/*
TP3
INGRESAR POR LINEA DE COMANDO: Bird -birds x -eyeSight y -randomJiggleLimit z -mode w
Con las teclas 1 y 2, se puede cambiar al modo 1 y al modo 2 respectivamente.
Para incrementar o decrementar eyesight, randomjigglelimit o velocity, se presionan las teclas E , R o V
y luege se presiona la tecla "up" si se quiere incrementar el valor o la tecla "down" si se busca descrementarla.
*/
#include<iostream>
#include <cstdlib>
#include <stdint.h>
#include <cstdio>
#include <string.h>
#include <string>

#include <cstring>
#include <fstream>


#include "Bird.h"
#include "parser.h"
#include "Allegro.h"
#include "Random.h"
#define HEIGHT 70
#define WIDTH 100
#define R 118
#define G 230
#define B 254
#define STEP 0.5

#define ABSOLUTE(x) ( ( ((x) >= 0)? (x) : ((x) * (-1)) ) )

//#define PRUEBA

#ifndef PRUEBA

#define MAXOPTIONS 9	//maximo de argumentos a ingresar



static int parseCallBack(const char*, const char*, void*);

enum modes { mode1 = 1, mode2};

typedef struct
{
	int birds_num;
	double eyeSight;
	double	 randomJiggleLimit;
	int mode;

}Data_t;


int main(int argc, char const *argv[])
{
	Data_t * userData = (Data_t*)malloc((sizeof(Data_t)));

	srand(time(NULL));
	
	/*parsing command line*/ 

	// INGRESAR POR LINEA DE COMANDO: Bird -birds x -eyeSight y -randomJiggleLimit z -mode w

	if (argc == MAXOPTIONS)
	{
		
		if ((parseCmdLine(argc, argv, parseCallBack, userData)) == ERROR)
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
	

	Bird * bird = new Bird[userData->birds_num];
	
	

	AllegroDisplay * aldisplay = new AllegroDisplay;
	aldisplay->initAllegroDisplay("textfont.ttf", HEIGHT , WIDTH , "bird.png");
	aldisplay->initTimer();

	bool quit = false;
	//double r_jiggle_limit = R_JIGGLE_MAX/2;
	int i;
	int key = -1;
	bool restart = true;
	double j = 0.0;
	double x, y;
	while (!quit)
	{	
		if (restart)	//si se modifico el modo
		{
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
				//bird[i].set_rjiggle(randIntBetween(userData->randomJiggleLimit*-1, userData->randomJiggleLimit)); //no deberia ir en rad?
				bird[i].set_rjiggle(userData->randomJiggleLimit);
				bird[i].pos.set_max_x(WIDTH);
				bird[i].pos.set_max_y(HEIGHT);
				bird[i].pos.set_x(randDoubleBetween(0.0, WIDTH));
				bird[i].pos.set_y(randDoubleBetween(0.0, HEIGHT));
				bird[i].pos.set_real_time_x(bird[i].pos.get_x());
				bird[i].pos.set_real_time_y(bird[i].pos.get_y());
				bird[i].set_direction_angle_actual(randDoubleBetween(PI*-1, PI));
				/*bird[i].set_max_pos(WIDTH, HEIGHT);
				bird[i].set_pos(randDoubleBetween(0.0, WIDTH), randDoubleBetween(0.0, HEIGHT));*/
				bird[i].move();
			}
			aldisplay->setDisplayColor(R, G, B);
			aldisplay->printMode(userData->mode);
			aldisplay->updateDisplay();
			i = 0;
			//rest
			while (i < 50)
			{
				if (aldisplay->getNextEvent() == timer_)
					i++;
			}
			restart = false;
		}
	
		switch (aldisplay->getNextEvent())		//manejo de eventos del allegro.
		{
			case timer_:
				aldisplay->setDisplayColor(R, G, B);
				for (i = 0; i < userData->birds_num; i++)
				{
					//find real time x,y
					double dist_x = bird[i].pos.get_next_x() - bird[i].pos.get_x();
					if (ABSOLUTE(dist_x) >= VELOCITY_MAX)
					{
						dist_x =  dist_x - WIDTH ;
						x = bird[i].pos.get_real_time_x() + dist_x * STEP;
						if (x > WIDTH)
							x -= WIDTH;
						if (x < 0.0)
							x += WIDTH;
					}
					else
					{
						x = bird[i].pos.get_real_time_x() + dist_x * STEP;
					}

					double dist_y = bird[i].pos.get_next_y() - bird[i].pos.get_y();
					if (ABSOLUTE(dist_y) >= VELOCITY_MAX)
					{
						dist_y = dist_y - HEIGHT ;
						y = bird[i].pos.get_real_time_y() + dist_y * STEP;
						if (y > HEIGHT)
							y -= HEIGHT;
						if (y < 0.0)
							y += HEIGHT;
					}
					else
					{
						y = bird[i].pos.get_real_time_y() + dist_y * STEP;
					}
					

					bird[i].pos.set_real_time_x(x);
					bird[i].pos.set_real_time_y(y);
					//draw bird on display
					aldisplay->updateBird(bird[i].pos.get_real_time_x(), bird[i].pos.get_real_time_y(), bird[i].get_direction_angle_actual());
					
				}
				//https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/compiler-error-c2360?f1url=https%3A%2F%2Fmsdn.microsoft.com%2Fquery%2Fdev15.query%3FappId%3DDev15IDEF1%26l%3DEN-US%26k%3Dk(C2360)%26rd%3Dtrue&view=vs-2017
				//print eyesight, rdmjglimit, valocity values on display
				{
					std::string str = std::to_string(bird[0].get_eyesight());
					str = "Eyesight= " + str;
					const char * c = str.c_str();
					aldisplay->printText(c, 0);

					str = std::to_string(bird[0].get_rjiggle());
					str = "RandomJiggleLimit= " + str;
					c = str.c_str();
					aldisplay->printText(c, 1);

					if (userData->mode == mode1)
					{
						str = std::to_string(bird[0].get_velocity());
						str = "Velocity= " + str;
						c = str.c_str();
						aldisplay->printText(c, 2);
					}
				}
				
				aldisplay->updateDisplay();
				
				j += STEP;
				//si ya termino de moverse una unidad, actualiza su siguiente posicion.
				if (j >= 1)
				{
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].pos.set_x(bird[i].pos.get_next_x());
						bird[i].pos.set_y(bird[i].pos.get_next_y());
					}
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].calculate_new_direction(bird,userData->birds_num);
					}
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].set_direction_angle_actual(bird[i].get_direction_angle_next()); //get angle next
						//bird[i].set_rjiggle(randIntBetween(0, r_jiggle_limit));
					}
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].move();
					}
					j = 0.0;
				}
				break;
			case quit_:
				quit = true;
				break;
			case mode1_:
				if (userData->mode != mode1)
				{
					userData->mode = mode1;
					restart = true;
				}
				break;
			case mode2_:
				if (userData->mode != mode2)
				{
					userData->mode = mode2;
					restart = true;
				}
				break;
			case eyesight_:
				key = eyesight_;
				break;
			case rjiggle_:
				key = rjiggle_;
				break;
			case velocity_:
				key = velocity_;
				break;
			case up_:
				switch (key)
				{
				case eyesight_:
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].increment_eyesight();
					}
					break;
				case rjiggle_:
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].increment_randomjigglelimit();
					}
					break;
				case velocity_:
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].increment_velocity();
					}
					break;
				}
				break;
			case down_:
				switch (key)
				{
				case eyesight_:
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].decrement_eyesight();
					}
					break;
				case rjiggle_:
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].decrement_randomjigglelimit();
					}
					break;
				case velocity_:
					for (i = 0; i < userData->birds_num; i++)
					{
						bird[i].decrement_velocity();
					}
					break;
				}
				break;		
		}
		
	}
	//destroy
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
				//printf("%d\n", ((Data_t*)userData)->birds_num);
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
				//printf("%f\n", ((Data_t*)userData)->eyeSight);
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
			if ((atoi(value) >= R_JIGGLE_MIN) && (atof(value) <= R_JIGGLE_MAX))
			{
				((Data_t*)userData)->randomJiggleLimit = atof(value);
				//printf("%f\n", ((Data_t*)userData)->randomJiggleLimit);
				
				return true;
			}
			else
			{
				printf("Ingrese el randomJiggleLimit entre %d y %f\n", R_JIGGLE_MIN, R_JIGGLE_MAX);
				return false;
			}
		}
		else if (!(strcmp(key, "mode")))
		{
			if ((atoi(value) == mode1))
			{
				((Data_t*)userData)->mode = atoi(value);
				

				return true;
			}
			else if ((atoi(value) == mode2))
			{
				((Data_t*)userData)->mode = atoi(value);


				return true;
			}
			else
			{
				printf("Ingrese el modo 1 o el modo 2 \n");
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
	aldisplay->updateBird(50, 35, -1);
	
	std::string str = std::to_string(2.01);
	str = "Eyesight= " + str; 
	const char * c = str.c_str();
	aldisplay->printText(c, 0);
	aldisplay->printText(c, 1);

	
	
		str = std::to_string(0.12);
		str = "RandomJiggleLimit= " + str;
		c = str.c_str();
		aldisplay->printText(c, 1);
	

	aldisplay->updateDisplay();
	char b = getchar();
	aldisplay->destroyAllegroDisplay();
	free(aldisplay);

}



#endif // PRUEBA






