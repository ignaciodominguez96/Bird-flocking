#pragma once


#ifndef BIRD_H
#define BIRD_H

#include "Position.h"
#include "typedefs.h"

#define EYESIGHT_MAX 5
#define EYESIGHT_MIN 1
#define MAX_BIRDS 10	//maximo de pajaros

#define VELOCITY_MAX 5
#define VELOCITY_MIN 1

#define R_JIGGLE_MAX 3.14
#define R_JIGGLE_MIN 10



// Declaraciones funciones auxiliares 
double calculate_distance(Position * p1, Position * p2);


class Bird
{
	public:

		//constructores
		Bird();

		Bird(uint velocity_, double eyesight_, double rjiggle_, uint pos_x, uint pos_y, uint height, uint width);

		Position pos;

		//getters
		double	get_direction_angle_actual(void);
		double	get_direction_angle_next(void);
		double	get_eyesight(void);
		double	get_rjiggle(void);
		uint	get_velocity(void);
		Position*	get_pos(void);


		//setters

		void set_direction_angle_actual(double direction_angle_actual_);
		void set_direction_angle_next(double direction_angle_next_);
		void set_rjiggle(double rijggle_);
		void set_eyesight(double eyesight_);
		void set_velocity(uint velocity_);
		void set_pos(Position* pos_);
		/*
		void set_pos(double x, double y);
		void set_max_pos(double x, double y);
		*/


		//metodos especiales
		void move(void);
		void calculate_new_direction(Bird * birds, uint bird_count);
		bool is_in_eyesight(Bird * other_bird);

		void increment_eyesight(void);
		void decrement_eyesight(void);
		void increment_velocity(void);
		void decrement_velocity(void);


	private:
		double direction_angle_actual;
		double direction_angle_next;
		double rjiggle;
		double eyesight;

		uint velocity;
	


};






#endif // !BIRD_H
