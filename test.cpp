#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "main.h"
#include "test.h"

#include "pch.h"

#pragma warning(disable:4996)
#pragma warning(disable:4101)
#pragma warning(disable:4505)

bool FF = 0;

#define FPS 33

int window_width = 1920;
int window_height = 1080;
int fontscale = 20*2;

static bool running_within;
static int do_once = 0;
bool front = false;
bool back = true;

enum index {START_PAGE,
				
				INDEX_1, INDEX_2, INDEX_3, INDEX_4, INDEX_5, INDEX_6, INDEX_7, INDEX_8, INDEX_9, INDEX_10,
				INDEX_11,INDEX_12,INDEX_13,INDEX_14,INDEX_15,INDEX_16,INDEX_17,INDEX_18,INDEX_19,INDEX_20,
				INDEX_21,INDEX_22,INDEX_23,INDEX_24,INDEX_25,INDEX_26,INDEX_27,INDEX_28,INDEX_29,INDEX_30,
				INDEX_31,INDEX_32,INDEX_33,INDEX_34,INDEX_35,INDEX_36,INDEX_37,INDEX_38,INDEX_39,INDEX_40,
				INDEX_41,INDEX_42,INDEX_43,INDEX_44,INDEX_45,INDEX_46,INDEX_47,INDEX_48,INDEX_49,INDEX_50,
				INDEX_51,INDEX_52,INDEX_53,INDEX_54,INDEX_55,INDEX_56,INDEX_57,INDEX_58,INDEX_59,INDEX_60,
				INDEX_61,INDEX_62,INDEX_63,INDEX_64,INDEX_65,INDEX_66,INDEX_67,INDEX_68,INDEX_69,INDEX_70,
				INDEX_71,INDEX_72,INDEX_73,INDEX_74,INDEX_75,INDEX_76,INDEX_77,INDEX_78,INDEX_79,INDEX_80,
				INDEX_81,INDEX_82,INDEX_83,INDEX_84,INDEX_85,INDEX_86,INDEX_87,INDEX_88,INDEX_89,INDEX_90,
				INDEX_91,INDEX_92,INDEX_93,INDEX_94,INDEX_95,INDEX_96,INDEX_97,INDEX_98,INDEX_99,INDEX_100,
				
				END_PAGE};

int current_index = INDEX_1;
bool flip = back;

int num_of_newlines = 0;

#define NCOL WHITE

internal void draw_index_card(int num_lines, std::string s1, std::string s2, std::string s3, std::string s4, std::string s5, std::string s6){
	int x = window_width/2;
	int y = window_height/2;
	
	
	
	if(num_lines == 1)
	{
		drawFontSolid(1,1,0, x,y, s1.c_str(), NCOL,TAHOMA,fontscale);
	}
	else if(num_lines == 2)
	{
		drawFontSolid(1,1,0, x,y-fontscale+(fontscale/2), s1.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(fontscale/2),           s2.c_str(), NCOL,TAHOMA,fontscale);
	}
	else if(num_lines == 3)
	{
		drawFontSolid(1,1,0, x,y-fontscale, s1.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y,           s2.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+fontscale, s3.c_str(), NCOL,TAHOMA,fontscale);
	}
	else if(num_lines == 4)
	{
		drawFontSolid(1,1,0, x,y-(fontscale/2)-(fontscale), s1.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y-(fontscale/2),             s2.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(fontscale/2),             s3.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(fontscale/2)+(fontscale), s4.c_str(), NCOL,TAHOMA,fontscale);
	}
	else if(num_lines == 5)
	{
		drawFontSolid(1,1,0, x,y-(fontscale*2), s1.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y-fontscale,     s2.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y,               s3.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+fontscale,     s4.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(fontscale*2), s5.c_str(), NCOL,TAHOMA,fontscale);
	}
	else if(num_lines == 6)
	{
		drawFontSolid(1,1,0, x,y-(fontscale/2)-(fontscale*2), s1.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y-(fontscale/2)-(fontscale),   s2.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y-(fontscale/2),               s3.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(fontscale/2),               s4.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(fontscale/2)+(fontscale),   s5.c_str(), NCOL,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(fontscale/2)+(fontscale*2), s6.c_str(), NCOL,TAHOMA,fontscale);
	}
	else
	{
		printf("error\n");
	}
}
internal void draw_title(std::string title){
	drawFontSolid(0,0,0, 0+10,0, title.c_str(), 0,128,255,255, TAHOMA,fontscale);
}
internal void icon(){

	SDL_Surface *surface;     // Declare an SDL_Surface to be filled in with pixel data from an image file
	Uint16 pixels[16*16] = {  // ...or with raw pixel data:
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
		0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
		0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
		0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
		0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
		0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
		0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
		0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
		0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
		0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
		0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
		0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
		0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
		0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
		0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
		0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
		0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
		0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
		0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
		0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
		0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
		0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
	};
	surface = SDL_CreateRGBSurfaceFrom(pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000);

	SDL_SetWindowIcon(window, surface);
	
}

bool Minimized;
int minimize_once = 0;

internal void fullscreen(){
	if(FF)
	{
		window_width = 800;
		window_height = 600;
		fontscale = 20;
		SDL_SetWindowSize(window,window_width,window_height);
		//SDL_SetWindowPosition(window,x_pos,y_pos);
		//SDL_SetWindowFullscreen(window,0);//SDL_WINDOW_FULLSCREEN, SDL_WINDOW_FULLSCREEN_DESKTOP or 0
	}
	else
	{
		window_width = 1920;
		window_height = 1080;
		fontscale = 20*2;
		SDL_SetWindowSize(window,window_width,window_height);
		//SDL_SetWindowPosition(window,0,0);
		//SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	
}
internal void minimized(){
	if(Minimized == 1 && minimize_once == 0)
	{
		SDL_MinimizeWindow(window);
		minimize_once = 1;
	}
	if(Minimized == 0 && minimize_once == 1)
	{
		SDL_MinimizeWindow(window);
		minimize_once = 0;
	}
}
internal void createwindow(){

	int window_x_pos = 900;
	int window_y_pos = 450;
	window_x_pos = 0;
	window_y_pos = 0;
	
	char title[100] = "Index Card - Learning Helper"; // set title of window
	
	if(do_once == 0)
	{
		destroy_Window();
		icon();
#if FULLSCREEN == 0
		init_Window(title,"0",window_x_pos,window_y_pos, window_width,window_height, 0,1); // fullscreen not stretched, not glitchy
#elif FULLSCREEN == 1
		init_Window(title,"0",window_x_pos,window_y_pos, window_width,window_height, 0,0); //window mode
		//init_Window(title,x_pos,y_pos, width,height, 2,0); //window fullscreen resolution stretched, glitchy
#endif
	}
	do_once = 1;

}
internal void input(){
	while(POLLEVENT)
	{
		if(QUIT){exit(0);}
		if(DOWNPRESS)
		{
			
			if(ESCAPE)  {exit(0);}
			
			if(DOWN)    {current_index--;flip=true; }
			if(UP)      {current_index++;flip=true; }
			if(LEFT)    {current_index--;flip=true; }
			if(RIGHT)   {current_index++;flip=true; }
			
			if(SPACE)   {flip=!flip;                }

			if(PAGEUP)  {current_index += 10;       }
			if(PAGEDOWN){current_index -= 10;       }
			
			if(HOME)    {current_index = END_PAGE;  }
			if(END)     {current_index = START_PAGE;}
			
			if(ONE)     {current_index = INDEX_1;   }
			if(THREE)   {current_index = INDEX_15;  }
			if(FIVE)    {current_index = INDEX_25;  }
			if(SEVEN)   {current_index = INDEX_40;  }
			if(ZERO)    {current_index = INDEX_50;  }
			
			if(F12_KEY) {FF=!FF;}
			
			if(P_KEY) {}
		}
		if(UPPRESS){}
		if(MOUSEWHEEL)
		{
			if(e.wheel.y > 0){ current_index++;}
			if(e.wheel.y < 0){ current_index--;}
		}
		
		if(LEFTMOUSEBUTTON)     {}
		if(RIGHTMOUSEBUTTON)    {}
		if(MIDDLEMOUSEBUTTON)   {Minimized = !Minimized;}
	}
	
}
internal void glyph_data(){
	// int minx, maxx, miny, maxy, advance;
	// if(TTF_GlyphMetrics(gFont, 'g', &minx, &maxx, &miny, &maxy, &advance)==-1)
	// {
	// 	printf("Error %s\n",TTF_GetError());
	// }
	// else
	// {
	// 	printf("minx %d", minx);
	// }
	
}
internal void draw(){
	int scale = 25;
	int size = 0;
	int x = window_width/2;
	int y = window_height/2;
	int w = scale;
	int h = scale;
	int centertype = 0;
	int heighttype = 0;
	int fontstyle = 4;

	// GET INPUT-FILE
	std::ifstream input("..//src/file3.txt");
	
	std::string line;
	int file_num_lines = 0;
	std::string str_ar[1000];

	// WRITE FILE TO STRING
	while(std::getline(input,line))
	{
		std::stringstream ss(line);
		//std::getline(ss, str_ar[file_num_lines], ':');
		std::getline(ss, str_ar[file_num_lines]);
		file_num_lines++;
	}

	// DRAW LIMIT BOUNDS OF INDEX
	if(current_index <= START_PAGE)
	{
		int off = 40;
		drawFontSolid(1,1,0, x,y, "l/r arrow keys - moves l/r flashcards  ", MAGENTA,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(off), "pgup pgdn - moves up 10, dn 10 flashcards", MAGENTA,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(off*2), "home end - moves to 1st flashcard, last flashcard", MAGENTA,TAHOMA,fontscale);
		drawFontSolid(1,1,0, x,y+(off*3), "spacebar - flips flashcard", MAGENTA,TAHOMA,fontscale);
		current_index = START_PAGE;
	}
	if(current_index >= END_PAGE)
	{
		drawFontSolid(1,1,0, x,y, "end", MAGENTA,TAHOMA,fontscale);
		current_index = END_PAGE;
	}
	
	// DRAW CURRENT INDEX CARD NUMBER
	char buff[30];
	drawFontSolid(1,1,0, 100,50, itoa(current_index,buff,10), CYAN,TAHOMA,fontscale);

	
	// DRAW FRONT AND BACK, FONT
	if(flip) drawFontSolid(1,1,0, 100+1500,50, "front_", CYAN,TAHOMA,fontscale);
	else     drawFontSolid(1,1,0, 100+1500,50, "back_",  CYAN,TAHOMA,fontscale);
	

	int max_number_of_lines = file_num_lines;
	bool bool_front = 0;
	bool bool_back = 0;
	// int number_of_back_loops = 0;
	// int number_of_front_loops = 0;
	int current_index_front = 0;
	int current_index_back = 0;
	
	int total_number_of_index_cards = 0;
	int number_of_lines = 0;
	
	int max_number_of_lines_in_index_front[100];
	int max_number_of_lines_in_index_back[100];
	
	std::string str_front[1000];
	for(int i = 0; i < max_number_of_lines; i++)
	{
		if(str_ar[i] == "#Front") total_number_of_index_cards++; // counts number of index cards in the file
	}
	for(int i = 0; i < max_number_of_lines; i++)
	{
		if(str_ar[i] == "#Front")
		{
			i++;
			bool_front = true;
		}
		
		if(str_ar[i] == "#/Front")
		{
			bool_front = false;
			current_index_front++;
			max_number_of_lines_in_index_front[current_index_front] = number_of_lines;
			number_of_lines = 0;
		}
		if(bool_front)
		{
			number_of_lines++;
		}

		
		if(str_ar[i] == "#Back")
		{
			i++;
			bool_back = true;
		}
		if(str_ar[i] == "#/Back")
		{
			bool_back = false;
			current_index_back++;
			max_number_of_lines_in_index_back[current_index_back] = number_of_lines;
			number_of_lines = 0;
		}
		if(bool_back)
		{
			number_of_lines++;
		}
	}
	
	current_index_front = 0;
	current_index_back = 0;

	for(int i = 0; i < max_number_of_lines; i++)
	{
		if(str_ar[i] == "#Front")
		{
			i++; // skips "#Front"  line
			bool_front = true; // sets bool_front true
		}
		if(str_ar[i] == "#/Front")
		{
			bool_front = false; // sets bool_front false
			current_index_front++; // loops index cards
			number_of_lines = 0;
		}
		if(bool_front)
		{
			if(flip)
			{
				if(current_index == current_index_front+1) // loops index cards
				{
					drawFontSolid(1,1,0, x, y+(fontscale*number_of_lines)-((fontscale*max_number_of_lines_in_index_front[current_index_front+1])/2),  str_ar[i].c_str(), CYAN,TAHOMA,fontscale);
					//drawFillRect( x,y+(fontscale*number_of_lines)-((fontscale*max_number_of_lines_in_index_front[current_index_front+1])/2), 10,10, 0,0,0,0, 0);
				}
				number_of_lines++;
			}
		}

		if(str_ar[i] == "#Back")
		{
			i++;
			bool_back = true;
		}
		if(str_ar[i] == "#/Back")
		{
			bool_back = false;
			current_index_back++;
			number_of_lines = 0;
		}
		if(bool_back)
		{
			if(!flip)
			{
				if(current_index == current_index_back+1)
				{
					drawFontSolid(1,1,0, x, y+(fontscale*number_of_lines)-((fontscale*max_number_of_lines_in_index_back[current_index_back+1])/2),  str_ar[i].c_str(), CYAN,TAHOMA,fontscale);
					//drawFillRect(x, y+(fontscale*number_of_lines)-((fontscale*max_number_of_lines_in_index_back[current_index_back+1])/2), 10,10, 0,0,0,0, 0);
				}
				number_of_lines++;
			}
		}
	}
	
}
extern "C" GAME_UPDATE_AND_RENDER(GameUpdateAndRender){
	running_within = true;
	
	fullscreen();
	minimized();
	
	createwindow();	
	input();
	
	// sdl
	SDL_SetRenderDrawColor(renderer,0,64,64,255);
	SDL_RenderClear(renderer);

	draw();
	
	SDL_Delay(1000/FPS);
	SDL_RenderPresent(renderer);
}
