#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <curses.h>
#include "helw.h"

int main ()
{
	int input=0;
		                                                                                                                                                                                                                                                                                                                                                    		initscr();
	start_color();
	init_pair(1,COLOR_GREEN,COLOR_WHITE);
	init_pair(2,COLOR_BLUE,COLOR_WHITE);
	init_pair(3,COLOR_RED,COLOR_WHITE);
	curs_set(0);
	noecho();
	
	keypad(stdscr, TRUE);
	input=getch();
	endwin();
	printf("%d", input);
	return 0;
}
