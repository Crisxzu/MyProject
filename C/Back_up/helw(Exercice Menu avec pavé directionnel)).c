#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

#include "helw.h"


void options(char** ChampMenu, int highlight_index)
{
   int i=0;
   printw("== Options ==\n");
   for (i = 0; i < nb_ChampMenuPrincipal; i++)
   {
   	if (i==highlight_index)
   	{
   		attron(COLOR_PAIR(1));
			printw("%s\n", ChampMenu[i]);
			attroff(COLOR_PAIR(1));
   	}
   	else
   	{
   		printw("%s\n", ChampMenu[i]);
   	}
   }
}

int main()
{
  int key, highlight_index=0; char* ChampMenu[nb_ChampMenuPrincipal]={"Play", "Option", "Quit"};
  initscr();
  start_color();
  init_pair(1,COLOR_GREEN,COLOR_WHITE);
  init_pair(2,COLOR_BLUE,COLOR_WHITE);
  init_pair(3,COLOR_RED,COLOR_WHITE);
  curs_set(0);
  noecho(); 
  keypad(stdscr, TRUE);
  options(ChampMenu, highlight_index);  
  while (1)
  {
  		key=getch();
  		if (key==KEY_UP)
  		{
  			highlight_index--;
  			if (highlight_index<0)
  			{
  				highlight_index=2;
  			}
  			clear();refresh();
  			options(ChampMenu, highlight_index);
  		}	
  		else if (key==KEY_DOWN)
  		{
  			highlight_index++;
  			if (highlight_index>2)
  			{
  				highlight_index=0;
  			}
  			clear();refresh();
  			options(ChampMenu, highlight_index);
  		}		
  		else if (key==ENTER)
  		{
  			keypad(stdscr, FALSE); 
  			break;
  		}
  }
  endwin();
  return 0;
}
