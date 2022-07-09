#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "grille.h"


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

void waitinputgrille(int *highlight_x, int *highlight_y, int *input, char (*grille)[NBMAX_CASE])
{
	curs_set(0);
   noecho(); 
   keypad(stdscr, TRUE);
	*input=getch();
	if (*input==KEY_UP)
	{
		*highlight_x=*highlight_x-1;
		if (*highlight_x<0)
		{
			*highlight_x=NBMAX_LIGNE-1;
		}
	}	
	else if (*input==KEY_DOWN)
	{
		*highlight_x=*highlight_x+1;
		if (*highlight_x>NBMAX_LIGNE-1)
		{
			*highlight_x=0;
		}
	}
	else if (*input==KEY_LEFT)
	{
		*highlight_y=*highlight_y-1;
		if (*highlight_y<0)
		{
			*highlight_y=NBMAX_CASE-1;
		}
	}
	else if (*input==KEY_RIGHT)
	{
		*highlight_y=*highlight_y+1;
		if (*highlight_y>NBMAX_CASE-1)
		{
			*highlight_y=0;
		}
	}
	else if (*input==ENTER)
	{
		keypad(stdscr, FALSE);
		if (grille[*highlight_x][*highlight_y]=='0')
		{
			grille[*highlight_x][*highlight_y]='X';
		}
		else if (grille[*highlight_x][*highlight_y]=='X')
		{
			grille[*highlight_x][*highlight_y]='0';
		}
	}
}

void intgrille(char (*grille)[NBMAX_CASE])
{
	int i=0, j=0;
	
	for (i = 0; i < 15; i++, j=0)
	{
		while (j<15)
		{
			grille[i][j]='0';
			j++;
		}
	}
}

void display(char (*grille)[NBMAX_CASE], const int highlight_x, const int highlight_y)
{
	int index_ligne=0, index_case=0;
	
	attron(COLOR_PAIR(0));
   printw("=== GRILLE ===\n");
   attroff(COLOR_PAIR(0));
   for (index_ligne = 0; index_ligne < 15; index_ligne++, index_case=0) 
   {
   	while (index_case<15)
   	{
   		if (index_ligne==highlight_x && index_case==highlight_y)
   		{
				attron(COLOR_PAIR(6));
				printw("%c", grille[index_ligne][index_case]);
				attroff(COLOR_PAIR(6));
   		}
			else 
			{
				attron(COLOR_PAIR(0));
				printw("%c", grille[index_ligne][index_case]);
				attroff(COLOR_PAIR(0));
			}
			index_case++;
   	}
   	printw("\n");	
   } 
}

int main ()
{
	char grille[NBMAX_LIGNE][NBMAX_CASE];
	int input=0, highlight_x=0, highlight_y=0;
	intgrille(grille);
	initInterface();
	while (input!=KEY_BACKSPACE)
	{
		display(grille, highlight_x, highlight_y);
		waitinputgrille(&highlight_x, &highlight_y, &input, grille);
		clear();
		refresh();
	}
	endwin();
	
	return 0;
}
