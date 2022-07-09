/* time example */
#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <curses.h>
#include "helw.h"

void initInterface()
{
	//Initialisation de l'interface qui va servir à afficher les différents menus du programme, et les différentes couleurs de texte
	initscr();
   start_color();
   init_pair(0,COLOR_WHITE,COLOR_WHITE);
   init_pair(1,COLOR_BLUE,COLOR_BLACK);
   init_pair(2,COLOR_CYAN,COLOR_BLACK);
   init_pair(3,COLOR_RED,COLOR_BLACK);
   init_pair(4,COLOR_MAGENTA,COLOR_BLACK);
   init_pair(5,COLOR_YELLOW,COLOR_BLACK);
   init_pair(6,COLOR_GREEN,COLOR_WHITE);
}

void display(char* string, const int index)
{
	addch(string[index]);
}

int main ()
{
	clock_t oldtime, current_time;
	int getsometime=FALSE, index=0;
	char string[]="Je suis le meilleur programmeur du monde !";

	initInterface();
	
	do
	{
		
		getsometime=FALSE;
		
		
		display(string, index);
		index++;
		oldtime=clock();
		while (getsometime!=TRUE)
		{
			current_time=clock()-oldtime;
			if (current_time>=50000)
			{
				getsometime=TRUE;
			}
		}
		refresh();
	} while (string[index]!='\0');
	
	endwin();
	
	/*time_t timer;
	struct tm y2k = {0};
	double seconds;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 122; y2k.tm_mon = 3; y2k.tm_mday = 5;

	time(&timer); 

	seconds = difftime(timer,mktime(&y2k));

	printf ("%.f seconds since April 5, 2022 12:00 AM in the current timezone\n", seconds);*/
	

	return 0;
}
