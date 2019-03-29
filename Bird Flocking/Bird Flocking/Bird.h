#pragma once


#ifndef BIRD_H
#define BIRD_H

#include "Position.h"
#include "typedefs.h"

class Bird
{
	public:

		//constructores
		Bird();

		Bird(uint velocity_, uint eyesight_, uint rjiggle_, uint pos_x, uint pos_y, uint height, uint width);

		//getters
		double	get_direction_angle_actual(void);
		double	get_direction_angle_next(void);
		uint	get_eyesight(void);
		uint	get_rjiggle(void);
		uint	get_velocity(void);
		Position*	get_pos(void);



		//metodos especiales
		void move(void);


	private:
		double direction_angle_actual;
		double direction_angle_next;
		uint rjiggle;
		uint eyesight;

		uint velocity;
		Position* pos;


};






#endif // !BIRD_H
