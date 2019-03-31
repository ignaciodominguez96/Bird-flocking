#pragma once

#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs

class AllegroDisplay
{
	public:
		//constructores
		AllegroDisplay();


		//metodos especiales
		bool initAllegroDisplay(const char * textfont, int h, int w, const char * birdimage);
		void destroyAllegroDisplay(void);
		void initTimer(void);
		void setDisplayColor(unsigned char r, unsigned char g, unsigned char b);
		void updateBird(double x, double y, double angle);
		void updateDisplay(void);
		
	private:
		ALLEGRO_DISPLAY* display;
		ALLEGRO_FONT* font;
		ALLEGRO_BITMAP* bird;
		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER *timer;

};

#endif // !ALLEGRO_H

