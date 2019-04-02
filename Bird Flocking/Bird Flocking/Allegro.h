#pragma once

#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs
#define TIMER 10.0
#define FPS 300.0
#define TEXTSIZE 50
#define MODETEXTSIZE 200
#define UNIT 20
#define CX 76
#define CY 38
#define BIRDSCALE 0.17
#define SPACE TEXTSIZE

enum event {null_ , timer_ , quit_ , mode1_ , mode2_ , eyesight_ , rjiggle_ ,velocity_ , up_, down_};

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
		enum event getNextEvent(void);
		void printText(const char* text, int line);
		void printMode(int mode);
		
	private:
		ALLEGRO_DISPLAY* display;
		ALLEGRO_FONT* font;
		ALLEGRO_FONT* font2;
		ALLEGRO_BITMAP* bird;
		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER *timer;

};

#endif // !ALLEGRO_H

