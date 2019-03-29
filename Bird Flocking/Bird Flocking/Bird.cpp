#include "Bird.h"

#define _USE_MATH_DEFINE

#include <math.h>


#define PI M_PI
#define PI_RAD (PI/180.0)

/*  Constructores  */

Bird
::Bird()
{
	direction_actual = 0.0;
	direction_next = 0.0;
	rjiggle = 0;
	eyesight = 0;

	velocity = 0;
	pos->set_x(0.0);
	pos->set_y(0.0);
	pos->set_max_x(0.0);
	pos->set_max_y(0.0);

}

Bird
::Bird(uint velocity_, uint eyesight_, uint rjiggle_, uint pos_x, uint pos_y, uint height, uint width)
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
uint	Bird::get_eyesight(void) { return eyesight; }
uint	Bird::get_rjiggle(void) { return rjiggle; }
uint	Bird::get_velocity(void) { return velocity; }
Position*	Bird::get_pos(void) { return pos; }

/* Metodos especiales */

void
Bird::move(void)
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
		new_x = limit_x;
	}

	if (new_x > limit_x)
	{
		new_x = 0;
	}

	if (new_y < 0)
	{
		new_y = limit_y;
	}

	if (new_y > limit_y)
	{
		new_y = 0;
	}

	pos->set_x(new_x);
	pos->set_y(new_y);
	

}
