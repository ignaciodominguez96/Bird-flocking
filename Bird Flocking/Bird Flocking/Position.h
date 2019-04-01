#pragma once

#ifndef POSITION_H
#define POSITION_H


class Position 
{
	public:
		Position(); //constructor implicito

		Position(double x, double y, double max_x, double max_y);

		double get_x();
		double get_y();
		double get_real_time_x();
		double get_real_time_y();
		double get_next_x();
		double get_next_y();
		double get_max_x();
		double get_max_y();

		void set_x(double x_);
		void set_y(double y_);
		void set_real_time_x(double x_);
		void set_real_time_y(double y_);
		void set_next_x(double x_);
		void set_next_y(double y_);
		void set_max_x(double max_x_);
		void set_max_y(double max_y_);


	private:
		double x;
		double y;

		double real_time_x;
		double real_time_y;

		double next_x;
		double next_y;

		double max_x; 
		double max_y; //#error "ver si no conviene poner en un define"

			


};


#endif // !POSITION_H
