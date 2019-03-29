#include "Position.h"


/*  Constructores  */

Position::Position()
{
	x = 0.0;
	y = 0.0;

	max_x = 0.0;
	max_y = 0.0;
}

Position::Position(double x_, double y_, double max_x_, double max_y_)
{
	x = x_;
	y = y_;

	max_x = max_x_;
	max_y = max_y_;


}


/*   Getters   */

double Position::get_x() { return x; }

double Position::get_y() { return y; }

double Position::get_max_x() { return max_x; }

double Position::get_max_y() { return max_y;  }


/*  Setters  */

void Position::set_x(double x_) { x = x_; }
void Position::set_y(double y_) { y = y_; }
void Position::set_max_x(double max_x_) { max_x = max_x_; }
void Position::set_max_y(double max_y_) { max_y = max_y_; }


