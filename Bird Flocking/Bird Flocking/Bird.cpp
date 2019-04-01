


#define _USE_MATH_DEFINES
#include <math.h>
#include "Bird.h"
#include "Random.h"




#define PI M_PI
#define PI_RAD (PI/180.0)

#define ABSOLUTE(x) ( ( (x >= 0)? x : (x * (-1)) ) )







/*  Constructores  */

Bird
::Bird()
{
	direction_angle_actual = 0.0;
	direction_angle_next = 0.0;
	rjiggle = 0;
	eyesight = 0;

	velocity = 0;
	pos->set_x(0.0);
	pos->set_y(0.0);
	pos->set_max_x(0.0);
	pos->set_max_y(0.0);

}

Bird
::Bird(uint velocity_, double eyesight_, uint rjiggle_, uint pos_x, uint pos_y, uint height, uint width)
{
	rjiggle = rjiggle_;
	eyesight = eyesight_;

	velocity = velocity_;
	pos->set_x(pos_x);
	pos->set_y(pos_y);
	pos->set_max_x((double) width);
	pos->set_max_y((double) height);

}

/*  Getters   */

double	Bird::get_direction_angle_actual(void) { return direction_angle_actual; }
double	Bird::get_direction_angle_next(void) { return direction_angle_next; }
double	Bird::get_eyesight(void) { return eyesight; }
uint	Bird::get_rjiggle(void) { return rjiggle; }
uint	Bird::get_velocity(void) { return velocity; }
Position*	Bird::get_pos(void) { return pos; }


/*  Setters */


void Bird::set_direction_angle_actual(double direction_angle_actual_) { direction_angle_actual = direction_angle_actual_; }
void Bird::set_direction_angle_next(double direction_angle_next_) { direction_angle_next = direction_angle_next_; }
void Bird::set_rjiggle(uint rijggle_) { rjiggle = rijggle_; }
void Bird::set_eyesight(double eyesight_) { eyesight = eyesight_; }
void Bird::set_velocity(uint velocity_) { velocity = velocity_; }
void Bird::set_pos(Position* pos_) { pos = pos_; }
/*
void Bird::set_pos(double x, double y)
{
	pos->set_x(x);
	pos->set_y(y);
}
void Bird::set_max_pos(double x, double y)
{
	pos->set_max_x(x);
	pos->set_max_y(y);
}
*/




/* Metodos especiales */

void Bird::move(void)
{
	double direction = direction_angle_actual;

	double delta_x = cos(direction*PI_RAD)* ((double)velocity);
	double delta_y = sin(direction*PI_RAD)* ((double)velocity);

	pos->set_x(pos->get_x() + delta_x);
	pos->set_y(pos->get_y() + delta_y);

	double new_x = pos->get_x();
	double new_y = pos->get_y();

	double limit_x = pos->get_max_x();
	double limit_y = pos->get_max_y();

	if (new_x < 0)
	{
		//new_x = limit_x;
		new_x += limit_x;
	}

	if (new_x > limit_x)
	{
		//new_x = 0;
		new_x -= limit_x;	
	}

	if (new_y < 0)
	{
		//new_y = limit_y;
		new_y += limit_y;
	}

	if (new_y > limit_y)
	{
		//new_y = 0;
		new_y -= limit_y;
	}

	pos->set_next_x(new_x);
	pos->set_next_y(new_y);
	/*
	pos->set_x(new_x);
	pos->set_y(new_y);
	*/

}


void Bird::calculate_new_direction(Bird * birds, uint bird_count)
{
	double sum = 0;

	int cant_birds_in_range = 0;

	for (uint i = 0; i < bird_count; i++)
	{
		if (is_in_eyesight(birds+i) )
		{
			sum += (birds + i)->get_direction_angle_actual();
			cant_birds_in_range++;
		}
	}

	double new_angle_direction = get_direction_angle_actual();

	if (cant_birds_in_range > 1)
	{
		double random = ABSOLUTE(get_rjiggle());
		new_angle_direction = (sum/cant_birds_in_range) + randDoubleBetween(random*-1, random);
		set_direction_angle_next(new_angle_direction);

	}

	
}


bool Bird::is_in_eyesight(Bird * other_bird)
{
	bool is_in_eyesight = false;
	if (calculate_distance(get_pos(), other_bird->get_pos() ) <=  get_eyesight())
		is_in_eyesight = true;
	
	return is_in_eyesight;

}



void Bird::increment_eyesight(void)
{
	eyesight++;

	if (eyesight >= EYESIGHT_MAX)
		eyesight = EYESIGHT_MAX;
	
}

void Bird::decrement_eyesight(void)
{
	eyesight--;

	if (eyesight <= EYESIGHT_MIN)
		eyesight = EYESIGHT_MIN;
}

void Bird::increment_velocity(void)
{
	velocity++;

	if (velocity >= VELOCITY_MAX)
		velocity = VELOCITY_MAX;

}

void Bird::decrement_velocity(void)
{
	velocity--;

	if (velocity <= VELOCITY_MIN)
		velocity = VELOCITY_MIN;

}


/*  Funciones auxiliares  */

double calculate_distance(Position * p1, Position * p2)
{
	double distance = 0.0;

	double aux = pow((p1->get_x() - p2->get_x()), 2) + pow((p1->get_y() - p2->get_y()), 2);

	distance = sqrt(aux);

	return distance;
}