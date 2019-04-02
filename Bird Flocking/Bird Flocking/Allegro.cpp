#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Allegro.h"




AllegroDisplay::AllegroDisplay()
{
	display = NULL;
	font = NULL;
	font2 = NULL;
	bird = NULL;
	event_queue = NULL;
	timer = NULL;
}

bool AllegroDisplay::initAllegroDisplay(const char * textfont, int h, int w, const char * birdimage)
{
	if (!al_init()) { //Primera funcion a llamar antes de empezar a usar allegro.
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}

	if (!al_install_mouse()) {//initialize mouse.
		fprintf(stderr, "failed to initialize the mouse!\n");
		return false;
	}

	if (!al_install_keyboard()) {//initialize keyboard.
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return false;
	}

	timer = al_create_timer(TIMER / FPS); //crea el timer pero NO empieza a correr
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return false;
	}

	event_queue = al_create_event_queue();//create event queue.
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_timer(timer);
		return false;
	}

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

	font = al_load_ttf_font(textfont, TEXTSIZE, 0); //HAY CREAR UN FONT PARA CADA TAMAÑO DE LETRA :( 
	if (!font) {
		fprintf(stderr, "Could not load text font.\n");
		return false;
	}
	font2 = al_load_ttf_font(textfont, MODETEXTSIZE, 0);
	if (!font2) {
		fprintf(stderr, "Could not load text font.\n");
		return false;
	}

	display = al_create_display(w*UNIT, h*UNIT); // Intenta crear display de fallar devuelve NULL

	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return false;
	}
	al_init_image_addon();
	bird = al_load_bitmap(birdimage); //create birds bitmap.

	if (!bird) {
		fprintf(stderr, "failed to create leds bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return false;
	}

	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)

	//Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola a medida que vayan sucediendo
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); //REGISTRAMOS EL TIMER
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO

	return true;
}

void AllegroDisplay::destroyAllegroDisplay(void)
{
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(bird);
}

void AllegroDisplay::initTimer(void)
{
	al_start_timer(timer);
}

void AllegroDisplay::setDisplayColor(unsigned char r, unsigned char g, unsigned char b)
{
	al_clear_to_color(al_map_rgb(r, g, b)); 
}

void AllegroDisplay::updateBird(double x, double y, double angle)
{
	al_draw_scaled_rotated_bitmap(bird, CX, CY, x*UNIT, y*UNIT, BIRDSCALE, BIRDSCALE, angle, ALLEGRO_FLIP_HORIZONTAL);
}

void AllegroDisplay::updateDisplay(void)
{
	al_flip_display();
}

enum event AllegroDisplay::getNextEvent(void)
{
	ALLEGRO_EVENT ev;
	al_get_next_event(event_queue, &ev);
	switch (ev.type)
	{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			return quit_;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_1: case ALLEGRO_KEY_PAD_1:
				return mode1_;
				break;

			case ALLEGRO_KEY_2: case ALLEGRO_KEY_PAD_2:
				return mode2_;
				break;
			case ALLEGRO_KEY_Q:
				return quit_;
				break;

			case ALLEGRO_KEY_E:
				return eyesight_;
				break;
			
			case ALLEGRO_KEY_R:
				return rjiggle_;
				break;

			case ALLEGRO_KEY_V:
				return velocity_;
				break;
			case ALLEGRO_KEY_UP:
				return up_;
				break;
			case ALLEGRO_KEY_DOWN:
				return down_;
				break;
			}
			return null_;
			break;
		case ALLEGRO_EVENT_TIMER:
			return timer_;
			break;
	}
	return null_;
}

void AllegroDisplay::printText(const char* text, int line)
{
	al_draw_text(font, al_map_rgb(255, 0, 0), 0, line * SPACE, ALLEGRO_ALIGN_LEFT, text);
}

void AllegroDisplay::printMode(int mode)
{
	switch (mode)
	{
	case 1:
		al_draw_text(font2, al_map_rgb(255, 0, 0), 50.0*UNIT, 35.0*UNIT, ALLEGRO_ALIGN_CENTRE, "MODE 1");
		break;
	case 2:
		al_draw_text(font2, al_map_rgb(255, 0, 0), 50.0*UNIT, 35.0*UNIT, ALLEGRO_ALIGN_CENTRE, "MODE 2");
		break;
	}
}