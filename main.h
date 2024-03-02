#ifndef MAIN_H
#define MAIN_H

#include "pch.h"

SDL_Window*		window   = NULL;
SDL_Renderer*	renderer = NULL;

// draw images textures
SDL_Texture*	solidTexture_font;
SDL_Texture*	text_font;
SDL_Rect			solidRect_font;
TTF_Font*		gFont = NULL;

SDL_Event e;

//--------

#define MAX_NUM_JOYSTICKS 4
// analog stick dead zone
const int           JOYSTICK_DEAD_ZONE = 8000; // deadzone
SDL_Joystick*       Joystick = NULL;    // joystick
SDL_GameController* Controller = NULL;

SDL_GameControllerAxis gca;

SDL_Haptic* haptic = NULL;
SDL_HapticEffect effect;
int effect_id;

// image texture
//LTexture image1[4];
LTexture img;

//--------

#define TAHOMA "c:/z/_MI/data/font/consolab.ttf"
					
#endif // MAIN_H
