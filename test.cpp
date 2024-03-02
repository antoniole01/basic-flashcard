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

// window // 0 -- right, 1 -- middle, 2 -- left

#define WIN RI

bool FF = 0;

#define FPS 33

int window_width = 1920;
int window_height = 1080;
int fontscale = 20*2;

static int do_once = 0;
bool front = false;
bool back = true;
static bool centerwindow = false;

static bool show_index[100] = {1};

int maximu_index_cards[255];//1000];

int index_card_first   = -1;
int index_card_current = 0;
int index_card_last    = 256;//1001;

// FileSave FileLoad System

std::ifstream file_load;
std::ofstream file_save;

std::string file_num;

static int total_number_of_index_cards = 0;
int total_cards = 0;
static int max_cards = 0;


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

int current_index;// = INDEX_1;
bool flip = back;
static int loop_once = 0;

int num_of_newlines = 0;

#define NCOL TE

internal std::string int_to_string(int value);
internal char * int_to_char(int value);
internal const char * int_t_c(int value);

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
		\
		\
		
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

// Fullscreen : Sets Windows Fullscreen on Windowed Mode
internal void fullscreen(){
	
	int fontS = 15;
	if(FF){
		window_width = 800;
		window_height = 600;
		fontscale = fontS;
		SDL_SetWindowSize(window,window_width,window_height);
	}
	else{ // Windows is Not in Fullscreen
		window_width = 1920;
		window_height = 1080;
		fontscale = fontS*2;
		SDL_SetWindowSize(window,window_width,window_height);
	}
}

// Minimized : Minimizes on Middle Mouse Button Click
bool Minimized;
int minimize_once = 0;

internal void minimized(){
	if(Minimized == 1 && minimize_once == 0){
		SDL_MinimizeWindow(window);
		minimize_once = 1;
	}
	if(Minimized == 0 && minimize_once == 1){
		SDL_MinimizeWindow(window);
		minimize_once = 0;
	}
}

int window_x_pos = 0;
internal void createwindow(){
	
	if(!centerwindow)window_x_pos = 0;//900; // leftwindow
	else window_x_pos = 1920;                // centerwindow
	
	int window_y_pos = 0;//450;
	char title[100] = "Index Card 2 - Learning Helper"; // set title of window
	if(do_once == 0){
		destroy_Window();
		icon();
		init_Window(title,"0",window_x_pos,window_y_pos, window_width,window_height, 0,1); // fullscreen not stretched, not glitchy
		if(!centerwindow){}
		else SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	do_once = 1;
}

internal void current_index_show(int input){

	switch(input){
		case(0):{
			if(show_index[current_index] == true){
				current_index--;
				flip=true;
			}
			else{
				current_index--;
				flip=true;
			}
		}return;
		case(1):{
			if(show_index[current_index] == true){
				current_index++;
				flip=true;
			}
			else{
				current_index++;
				flip=true;
			}
		}return;
		//LEFT
		case(2):{
			do{
				current_index--;
				flip=true;
			}while(show_index[current_index] == true);
		}return;
		//RIGHT
		case(3):{
			do{
				current_index++;
				flip=true;
			}while(show_index[current_index] == true);
			if(show_index[max_cards-1] == true) current_index = 0;
		}return;
	}
}

bool p_down = false;
bool ctrl_down = false;
bool o_down = false;
bool ctrl_o_cube = false;
bool one_down = false;
bool two_down = false;
bool three_down = false;

int fname = 1;

static bool card_was_learned = false;
bool withinBounds = false;

internal void input(){
	while(POLLEVENT){
		if(QUIT){exit(0);}
		if(DOWNPRESS){
			
			if(ESCAPE)   {
				file_save.open("..//src//p1.dat");                                      // saves file on escape // open file
				file_save << fname << " " << flip << " " << current_index << std::endl; // saves - file, flip, and current index

				for(int i = 0; i < 100; i++){
					file_save << show_index[i] << " ";
				}
				file_save.close();
				exit(0);
			}
			
			if(UP)       {flip=!flip;}
			if(DOWN){
				show_index[current_index] = true;
				do{
					current_index++;
				}while(show_index[current_index] == true);
				if(show_index[current_index] == false && current_index == max_cards) current_index = 0;
			}
			if(LEFT)     {current_index_show(2);}
			if(RIGHT)    {current_index_show(3);}
			if(SPACE)    {flip=!flip;           }
			
			if(BACKSPACE){
				show_index[current_index] =! show_index[current_index];
				//if(show_index[current_index+1] == false){}
				current_index++;
			}
			
			if(PAGEUP)   {current_index += 10;}
			if(PAGEDOWN) {current_index -= 10;}
			
			if(HOME)     {current_index = START_PAGE;}
			if(END)      {current_index = END_PAGE;  }
			
			if(ONE)      {one_down = true; current_index = INDEX_1;}
			if(TWO)      {two_down = true; current_index = INDEX_1;}
			if(THREE)    {three_down = true; /*current_index = INDEX_15;*/}
			if(FIVE)     {current_index = INDEX_25;}
			if(SEVEN)    {current_index = INDEX_40;}
			if(ZERO)     {current_index = INDEX_50;}
			
			if(F12_KEY)  {FF=!FF;}
			
			if(LCTRL)    {ctrl_down = true;}
			if(O_KEY)    {o_down = true;   }
			if(P_KEY)    {p_down = true;   }
			if(I_KEY)    {                                                              // on "I" key save file
				file_save.open("..//src//p1.dat");
				file_save << fname << " " << flip << " " << current_index << std::endl;

				for(int i = 0; i < 100; i++){
					file_save << show_index[i] << " ";
				}
				file_save.close();
				printf("data saved.\n");
			}
			
			if(ONE_NUMPAD||M_KEY     ){current_index = START_PAGE+1;}                                     // 1 - start page
			if(TWO_NUMPAD||COMMA     ){                                                                   // 2 - memorized
				show_index[current_index] = true;
				do{
					current_index++;
				}while(show_index[current_index] == true);
				if(show_index[current_index] == false && current_index == max_cards) current_index = 0;
			}
			
			if(THREE_NUMPAD||PERIOD  ){current_index = max_cards;}                                        // df3 - end
			if(FOUR_NUMPAD ||J_KEY   ){current_index_show(2);}                                            // 4 - left  <-
			if(FIVE_NUMPAD ||K_KEY   ){flip=!flip;}                                                       // 5 - flip
			if(SIX_NUMPAD  ||L_KEY   ){current_index_show(3);}                                            // 6 - right ->
			if(EIGHT_NUMPAD||I_KEY   ){do_once=0;centerwindow=!centerwindow;}                             // 8 - centerwindow
			if(PERIOD_NUMPAD         ){                                                                   // . - save
				file_save.open("..//src//p1.dat");
				file_save << fname << " " << flip << " " << current_index << std::endl;

				for(int i = 0; i < 100; i++){
					file_save << show_index[i] << " ";
				}
				file_save.close();
				exit(0);
			}
			
			if(SEVEN_NUMPAD   ){}
			if(NINE_NUMPAD    ){}
			if(NUMLOCK_NUMPAD	){}
			if(DIVIDE_NUMPAD  ){}
			if(MULTIPLY_NUMPAD){}
			if(MINUS_NUMPAD	){}
			if(PLUS_NUMPAD		){}
			if(ENTER_NUMPAD	){}
		}
		if(UPPRESS){
			if(LCTRL)    {ctrl_down  = false;}
			if(ONE)      {one_down   = false;}
			if(TWO)      {two_down   = false;}
			if(THREE)    {three_down = false;}
			if(O_KEY)    {o_down     = false;}
			
			if(EQUALS) {
				fname++;
				loop_once = 0;
				max_cards = 0;
			}
			if(MINUS)  {
				fname--;
				loop_once = 0;
				max_cards = 0;
			}
			
			if(P_KEY){ p_down = false; }
			if(BACKQUOTE){                                                 // ~ - reset memorized cards
				for(int i = 0; i <= 100; i++){
					show_index[i] = false;
				}
			}
			
			if(TWO_NUMPAD)  {            //card learned
				card_was_learned = true;
			}
			if(SEVEN_NUMPAD||U_KEY){
				fname--;
				loop_once = 0;
				max_cards = 0;
			}
			if(NINE_NUMPAD||O_KEY) {
				fname++;
				loop_once = 0;
				max_cards = 0;
			}
			if(NUMLOCK_NUMPAD	){
				for(int i = 0; i <= 100; i++){                           // set to index to 0
					show_index[i] = false;
				}
				current_index = 0;
			}
			
			if(ONE_NUMPAD     ){}
			if(THREE_NUMPAD   ){}
			if(FOUR_NUMPAD    ){}
			if(FIVE_NUMPAD    ){}
			if(SIX_NUMPAD     ){}
			if(EIGHT_NUMPAD   ){}
			if(DIVIDE_NUMPAD	){}
			if(MULTIPLY_NUMPAD){}
			if(MINUS_NUMPAD	){}
			if(PLUS_NUMPAD		){}
			if(ENTER_NUMPAD	){}
			if(PERIOD_NUMPAD	){}
		}
	}

	// MOUSE BUTTON CONTROLLS
	if(MOUSEMOTION){
		int x, y;
		SDL_GetMouseState(&x,&y);
		if(x >= 400 && x <= 1500 &&
			y >= 250 && y <= 800){
			withinBounds = true;
			//printf("inside\t");
		}
		else withinBounds = false;
	}
	
	if(MOUSEWHEEL){
		if(e.wheel.y > 0){ current_index_show(2);}
		if(e.wheel.y < 0){ current_index_show(3);}
	}// mouse wheel
	
	bool isdown = false;
	static int pressedonce = 0;
	if(MOUSEBUTTONDOWN){
		if(LEFTMOUSEBUTTON)     {
			isdown = true;
			pressedonce = 0;
		}
		if(RIGHTMOUSEBUTTON){flip=!flip;}
	}
	if(MOUSEBUTTONUP){
		if(LEFTMOUSEBUTTON)     {
			
			// int x, y;
			// SDL_GetMouseState(&x,&y);
			// if(x >= 400 && x <= 1500 &&
			// 	y >= 250 && y <= 800 &&
			// 	isdown == false && pressedonce == 0)
			// 	if(withinBounds == true){
			// 		flip=!flip;
			// 	}
			// pressedonce++;
		}
		if(RIGHTMOUSEBUTTON)    {}
		if(MIDDLEMOUSEBUTTON)   {Minimized = !Minimized;}
	}
}

internal std::string int_to_string(int value){
	char buffer[5000];
	std::string s = itoa(value, buffer, 10);
	return s;
}

#pragma warning(disable:4172)
internal char * int_to_char(int value){
	std::string buffer = "";
	char str[1024];
	buffer += itoa(value, str, 10);
	return str;
}

internal const char * int_t_c(int value){
	// 1ST ATTEMPT, WORKS IN MAIN, BUT DOESN'T WORK IN FUNCTION(IDK), MAYBE MEMORY IS SHUFFLED?
	std::stringstream strs;
	strs << value;
	std::string temp_str = strs.str();
	char const *pchar = temp_str.c_str();
	return pchar;
}

// Prints String to the Console Window

internal void drawpl(std::string sentence){
	std::stringstream ss(sentence);
	std::string to;
	std::string sa[10];
	internal int i = 0;
	while(std::getline(ss,to,'\n')){
		sa[i] = to;
		//std::cout << i << ":\t" << sa[i] << std::endl;
		i++;
	}
	//printf("%i\n",i);
}

// Index Card Info
internal void index_card_overlay_info(){
	char buff[30];
	
	drawFillRect(40,20,1920-80,1080-35,  10,10,40,10,  0);
	
	// Background
	if(flip) drawFillRect(40,20,1920-80,1080-35,  10,10,40,10,  0); // blue bg
	else     drawFillRect(40,20,1920-80,1080-35,  40,10,10,10,  0); // red bg
	
	// Draw Current Index Card Number
	drawFontSolid(1,1,0, 100,50, itoa(current_index,buff,10), CYAN,TAHOMA,fontscale, 40,40,40,125); // Index #
	
	// Draw Front and Back -Label
	if(flip) drawFontSolid(1,1,0, 1920/2,1080-60, "FRONT", 0,0,150,255,TAHOMA,fontscale*3);     // FRONT
	else     drawFontSolid(1,1,0, 1920/2,1080-60, "BACK",  255,100,100,100,TAHOMA,fontscale*3); // BACK


	// Draw Cards Studied(Memorized)
	int num_memorized = 0;
	for(int i = 1; i < 100; i++){                       // index[i] ++
		if(show_index[i] == true)num_memorized++;
	}
	std::string ns = int_to_string(num_memorized) + " of " + int_to_string(max_cards-1) + " Studied";
	if(num_memorized == max_cards-1)
		drawFontSolid(1,1,0,1920-240,60, "-- Study Complete -- ",GREEN,TAHOMA,fontscale); // Quantity
	else
		drawFontSolid(1,1,0, 1920-220,60, ns.c_str(),  0,125,125,255,TAHOMA,fontscale); // Quantity

	drawFontSolid(1,1,0, 100,100, "test",  0,125,125,255,TAHOMA,fontscale); // Quantity
	

	
}

static int doit = 0;
static bool f1 = false;
static bool f2 = false;
static bool f3 = false;

// fileslist
const int max_files = 16;

SDL_Point getsize(SDL_Texture *texture){
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	return size;
}

internal void draw(){

	
	int x = window_width/2;
	int y = window_height/2;
	
	// Load Input File
	// Languages // Jap // Kor // Fre // 

	std::string filename;
	
	int maxfiles[max_files];
	
	std::string buffer;
	std::string lline;
	while(file_load >> fname){}

	if(fname <= 1)fname = 1;
	if(fname >= max_files)fname = max_files;

	// TODO: Change max_files after adding more fileslist
	switch(fname){
		case 1:filename = "..//src//exam10.txt";         file_num = "1";break;
		case 2:filename = "..//src//nursing.txt";        file_num = "2";break;
		case 3:filename = "..//src//jap.txt";            file_num = "3";break;
		case 4:filename = "..//src//kor.txt";            file_num = "4";break;
		case 5:filename = "..//src//chi.txt";            file_num = "5";break;
		case 6:filename = "..//src//fre.txt";            file_num = "6";break;
		case 7:filename = "..//src//bio.txt";            file_num = "7";break;
		case 8:filename = "..//src//b-ap.txt";           file_num = "8";break;
		case 9:filename = "..//src//nursing-terms.txt";  file_num = "9";break;
		case 10:filename = "..//src//nursing-terms2.txt";file_num = "10";break;
		case 11:filename = "..//src//nursing-terms3.txt";file_num = "11";break;
		case 12:filename = "..//src//anatomy.txt";       file_num = "12";break;
		case 13:filename = "..//src//ap-study.txt";      file_num = "13";break;
		case 14:filename = "..//src//ori-ins-fun.txt";   file_num = "14";break;
		case 15:filename = "..//src//exam 3.txt";        file_num = "15";break;
		case 16:filename = "..//src//exam 4.txt";        file_num = "16";break;
		default:break;
	}

	std::ifstream input(filename);
	std::string line;
	int file_num_lines = 0; // set file_number_lines = 0

	//TODO: Can get Overflow for string size Error
	std::string str_ar[5000];
	
	// Write Content of File into String
	while(std::getline(input,line)){
		std::stringstream ss(line);
		std::getline(ss, str_ar[file_num_lines]); // Stores SS(stringstream) Into str_ar
		file_num_lines++; // "File_Num_Lines" - Gets Maximum Number Of Lines in File
	}

	// Count number of (indexes)"~" in the File
	int tmp_max_number_of_lines = file_num_lines;
	if(loop_once == 0){
		for(int i = 0; i < tmp_max_number_of_lines; i++){
			if(str_ar[i].substr(0,2) == " ~"){
				max_cards++;
			}
		}
		loop_once++;
	}
	
	// Index Set Limit Bounds --
	// Display Start Keyboard Console-Command Info
	// Display Last Info
	if(current_index < START_PAGE){
		std::string infolnp =
			"l/r - move l/r flashcards"
			"pgup pgdn - moves up 10, dn 10 flashcards"
			"home end - moves to 1st flashcard, last flashcard"
			"spacebar - flips flashcard";
		static int doonce = 0;
		if(doonce == 0){/*drawpl(infolnp);*/}
		doonce++;
		current_index = START_PAGE;
	}
	
	if(current_index >= max_cards-1){ // End Page -- Draw "End"
		// Only prints "End"
		//drawFontSolid(1,1,0, x,y, "end", MAGENTA,TAHOMA,fontscale);
		current_index = max_cards-1;
	}

	// Draws Index Overlay Info
	index_card_overlay_info();

	int max_number_of_lines = file_num_lines; // max number of lines -- lines from file
	bool bool_front = 0;
	bool bool_back = 0;
	int current_index_front = 0;
	int current_index_back = 0;
	
	int number_of_lines = 0;

	// max size of lines
	int max_number_of_lines_in_index_front[1000];
	int max_number_of_lines_in_index_back[1000];
	int total_cards = 0;

	// Goes Through the File and Gives Index Array of Number of Lines
	// in Front & Back of Index to Front_Array & Back_Array
	// Stores Number of Lines in Index Back & Front for Font Rendering
	//std::cout << system("CLS") << std::endl;
	
	for(int i = 0; i < max_number_of_lines; i++){ // Goes Through the Whole File
		if(str_ar[i].substr(0,2) == "**"){i+=2;} // Skip Main Title "*" // Dont Need this bcs Search
		if(str_ar[i].substr(0,2) == " ~"){ //if(str_ar[i].find(" ~") == std::string::npos){
			bool_back = false;
			i++; // skips "#Front" line
			bool_front = true; // sets bool_front true
			total_cards++;
		}
		if(bool_front){ // number_of_lines in front -- number of lines is reset on #/Front
			number_of_lines++; // Gives me the Number of Lines in Front
		}
		if(str_ar[i] == "" && bool_front == true){
			bool_front = false; // Stops Counting Number of Lines in #Front Sets False
			max_number_of_lines_in_index_front[current_index_front] = number_of_lines; // Parses Array of Number of -Front Idx -Lines
			current_index_front++; // Goes To Next Array to Store -NumberOfLines-
			number_of_lines = 0; // Resets Number for Back Array

			i++;
			bool_back = true;
		}
		if(bool_back){
			number_of_lines++;
		}
		if(str_ar[i] == "" && bool_back == true){
			bool_back = false;
			current_index_back++;
			max_number_of_lines_in_index_back[current_index_back] = number_of_lines; // Parses Array of Number of -Back Idx -Lines
			number_of_lines = 0;
		}
		total_number_of_index_cards = total_cards+1;
	}

	current_index_front = 0; //reset value
	current_index_back  = 0; //reset value

	// Renders Index Card Text & Aligns to Previous -ForLoop Height
	for(int i = 0; i < max_number_of_lines; i++){
		if(i == max_number_of_lines){}
		if(str_ar[i].substr(0,2) == "**"){i+=2;} // Skip Main Title // Don't Need this bcs Search
		if(str_ar[i].substr(0,2) == " ~"){ //if(str_ar[i].find(" ~") == std::string::npos){
			bool_back = false;
			i++; // skips "#Front"  line
			bool_front = true; // sets bool_front true
			number_of_lines = 0;
		}
		if(str_ar[i] == "" && bool_front == true){
			bool_front = false;
			current_index_front++;
			number_of_lines = 0;

			i++;
			bool_back = true;
		}

		int fi = 0; // font indentation
		int fix = x - 400; // font indentation x_position

		if(bool_front){ // If bool_front -true Draw Front Index Text
			if(flip){
				number_of_lines++;
				int y_new_pos = (y+(fontscale*(number_of_lines-1)))-(((fontscale*(max_number_of_lines_in_index_front[current_index_front]-1))/2)-20);
				// Draw Main Index Title
				if(current_index == 0){
					drawFontSolid(fi,1,0, fix-500, y+(fontscale*1)-100, str_ar[0].c_str(), CYAN,TAHOMA,fontscale*2);
				}
				if(current_index == current_index_front+1){ // loops index cards
					// Prints Front Index -Text
					drawFontSolid(fi,1,0, fix, y_new_pos, str_ar[i].c_str(), CYAN,TAHOMA,fontscale);
				}
			}
		}
		
		if(str_ar[i].substr(0,2) == "" && bool_back == true){
			bool_back = false;
			current_index_back++;
			number_of_lines = 0;
		}
		
		if(bool_back){ // If bool_back -true Draw Back Index Text
			if(!flip){
				number_of_lines++;
				int y_new_pos = (y+(fontscale*(number_of_lines-1)))-(((fontscale*(max_number_of_lines_in_index_back[current_index_back+1]-1))/2)-20);
				// Draw Main INdex 
				if(current_index == 0){
					//drawFontSolid(1,1,0, x, y+(fontscale*1)-100, str_ar[0].c_str(), CYAN,TAHOMA,fontscale*2);
				}
				if(current_index == current_index_back+1){
					// Prints Back Index -Text
					drawFontSolid(fi,1,0, fix, y_new_pos, str_ar[i].c_str(), CYAN,TAHOMA,fontscale);
				}
			}
		}
	}

	// Draws Current Filename and Number
	
	int extension = 4; // ext characer 4 ".ext"
	int directory = 9; // dir character 9 "..//src//"
	std::string new_filename = filename.substr(directory,filename.length()-directory-extension);// Trims Filename
	
	drawFontSolid(0,1,0, 80,1080-50-50, file_num.c_str(), 70,70,70,255,TAHOMA,fontscale);         // Draws FileNum
	drawFontSolid(0,1,0, 80,1080-50, new_filename.c_str(), 70,70,70,255,TAHOMA,fontscale);      // Draws FileDirectory
	
	// Center Square Align
	//if(ctrl_down == true && o_down == true){ ctrl_o_cube = !ctrl_o_cube;                          }
	if(ctrl_o_cube){                         drawFillRect(1920/2,1080/2, 4,4, 255,255,255,255,0); }
	
	//drawFillRect(400,250,1500-400,800-250, 50,50,50,100,0); // Square DGrey Rectangle Over Text

	// if(card_was_learned == true){
	// 	int show = 0;
	// 	if(show <= 1000){
	// 		drawFillRect(        1400+300-100,650+300-50,200,100, 0,155,0,255,0);
	// 		drawFontSolid(1,1,0, 1400+300,    650+300,   "Studied",0,125,125,255,TAHOMA,fontscale);
	// 		show++;
	// 		card_was_learned = false;
	// 	}
	// }

	// which is on the control tab of settings if you don't have pedals playback could be controlled using system wide hotkeycs

	//int cx = SDL_QueryTexture(solidRectu)
	//int cx = getsize(text_font);
	//printf("gt: \t%i ",getsize(text_font).x);
	//img.render((window_width/2)-((getsize(text_font).x)/100),window_height/2,5,5);

	file_save.close();
	file_load.close();
}

bool loadMedia(){
	bool success = true;
	if(!img.loadFromFile("..//src//bg.png")){
		printf("Failed!!!\n");
		success = false;
	}
	return success;
}

extern "C" GAME_UPDATE_AND_RENDER(GameUpdateAndRender){

	static int load_once = 0;
	if(load_once == 0){
		file_load.open("..//src//p1.dat");
		if(file_load.is_open()){
			file_load >> fname >> flip >> current_index;
			for(int i = 0; i < 100; i++){                   // load file 
				file_load >> show_index[i];
			}
		}
		else{
			printf("error\n");
		}
		load_once++;
	}
	
	fullscreen();
	minimized();
	
	createwindow();
	input();
	
	SDL_SetRenderDrawColor(renderer,0,64,64,255);
	SDL_RenderClear(renderer);

	//loadMedia();

	// Draw
	draw();


	img.free();
	
	SDL_Delay(1000/FPS);
	SDL_RenderPresent(renderer);
}
