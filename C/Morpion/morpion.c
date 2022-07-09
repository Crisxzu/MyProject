#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "morpion.h"


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

void waitinputgrille(int *highlight_x, int *highlight_y, int *input, int *turn, char (*grille)[NBMAX_CASE])
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
		if (*turn==0)
		{
			grille[*highlight_x][*highlight_y]='0';
			*turn=1;
		}
		else if (*turn==1)
		{
			grille[*highlight_x][*highlight_y]='X';
			*turn=0;
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
			grille[i][j]=32;
			j++;
		}
	}
}

void display(char (*grille)[NBMAX_CASE], const int highlight_x, const int highlight_y, char** player, const int turn)
{
	int index_ligne=0, index_case=0;
	
	attron(COLOR_PAIR(0));
   printw("=== MORPION GAME ===\n");
   printw("== %s ==\n", player[turn]);
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
void checkvictory(char (*grille)[NBMAX_CASE], int *success)
{
	int index_ligne=0, index_case=0, check_type=0, match=0, quitcheck=FALSE, quit=FALSE, actual_ligne=0, actual_case=0;
	for (actual_ligne = 0; actual_ligne < NBMAX_LIGNE && *success==FALSE; actual_ligne++, actual_case=0)
	{
		do 
		{
			check_type=0, quitcheck=FALSE;
			do
			{
				quit=FALSE, index_ligne=actual_ligne, index_case=actual_case, match=0;
				
				switch(check_type)
				{
					case 0:
						while (match<MATCHFORVICTORY && quit==FALSE && index_case+1<NBMAX_CASE)
						{
							if (grille[index_ligne][index_case]=='0' || grille[index_ligne][index_case]=='X')
							{
								if (grille[index_ligne][index_case]==grille[index_ligne][index_case+1])
								{
									match++;
									index_case++;
								}
								else
								{
									quit=TRUE;
								}
							}
							else
							{
								quit=TRUE;
							}
						}
						if (match==MATCHFORVICTORY-1)
						{
							*success=TRUE;
							quitcheck=TRUE;
						}
						else
						{
							check_type++;
						}
						break;
					case 1:
						while (match<MATCHFORVICTORY && quit==FALSE && index_case+1<NBMAX_CASE && index_ligne+1<NBMAX_LIGNE)
						{
							if (grille[index_ligne][index_case]=='0' || grille[index_ligne][index_case]=='X')
							{
								if (grille[index_ligne][index_case]==grille[index_ligne+1][index_case+1])
								{
									match++;
									index_case++;
									index_ligne++;
								}
								else
								{
									quit=TRUE;
								}
							}
							else
							{
								quit=TRUE;
							}
						}
						if (match==MATCHFORVICTORY-1)
						{
							*success=TRUE;
							quitcheck=TRUE;
						}
						else
						{
							check_type++;
						}
						break;
					case 2:
						while (match<MATCHFORVICTORY && quit==FALSE && index_ligne+1<NBMAX_LIGNE)
						{
							if (grille[index_ligne][index_case]=='0' || grille[index_ligne][index_case]=='X')
							{
								if (grille[index_ligne][index_case]==grille[index_ligne+1][index_case])
								{
									match++;
									index_ligne++;
								}
								else
								{
									quit=TRUE;
								}
							}
							else
							{
								quit=TRUE;
							}
						}
						if (match==MATCHFORVICTORY-1)
						{
							*success=TRUE;
							quitcheck=TRUE;
						}
						else
						{
							check_type++;
						}
						break;
					case 3:
						while (match<MATCHFORVICTORY && quit==FALSE && index_case-1>=0 && index_ligne+1<NBMAX_LIGNE)
						{
							if (grille[index_ligne][index_case]=='0' || grille[index_ligne][index_case]=='X')
							{
								if (grille[index_ligne][index_case]==grille[index_ligne+1][index_case-1])
								{
									match++;
									index_case--;
									index_ligne++;
								}
								else
								{
									quit=TRUE;
								}
							}
							else
							{
								quit=TRUE;
							}
						}
						if (match==MATCHFORVICTORY-1)
						{
							*success=TRUE;
							quitcheck=TRUE;
						}
						else
						{
							check_type++;
						}
						break;
					default:
						quitcheck=TRUE;
						break;
				}
			} while (quitcheck==FALSE);
			actual_case++;
		}while(actual_case<15 && *success==FALSE);
	}	
}

void displayMenu(char** ChampMenu, const int highlight_index, const int nb_ChampMenu, const int turn)
{
	int Champ=0;
	
	attron(COLOR_PAIR(0));
   printw("== VICTORY FOR PLAYER %d ==\n", turn);
   attroff(COLOR_PAIR(0));
   for (Champ = 0; Champ < nb_ChampMenu; Champ++)
   {
   	if (Champ==highlight_index)
   	{
   		attron(COLOR_PAIR(6));
			printw("%s\n", ChampMenu[Champ]);
			attroff(COLOR_PAIR(6));
   	}
   	else
   	{
   		attron(COLOR_PAIR(0));
   		printw("%s\n", ChampMenu[Champ]);
   		attroff(COLOR_PAIR(0));
   	}
   } 
}

void waitinputMenu(int *highlight_index, int *input, const int nb_ChampMenu)
{
   curs_set(0);
   noecho(); 
   keypad(stdscr, TRUE);
	*input=getch();
	if (*input==KEY_UP)
	{
		*highlight_index=*highlight_index-1;
		if (*highlight_index<0)
		{
			*highlight_index=nb_ChampMenu-1;
		}
	}	
	else if (*input==KEY_DOWN)
	{
		*highlight_index=*highlight_index+1;
		if (*highlight_index>nb_ChampMenu-1)
		{
			*highlight_index=0;
		}
	}
	else if (*input==ENTER)
	{
		keypad(stdscr, FALSE);
	}	
}

int main ()
{
	char grille[NBMAX_LIGNE][NBMAX_CASE];
	char* player[]={"TURN PLAYER 1: 0", "TURN PLAYER 2: X"};
	char* Menu[]={"Play again", "Quit game"};
	int input=0, highlight_x=0, highlight_y=0, turn=0, success=FALSE, quitgame=FALSE, highlight_index=0, nb_ChampMenu=2;
	initInterface();
	do
	{
		input=0, highlight_x=0, highlight_y=0, turn=0, success=FALSE, highlight_index=0;
		intgrille(grille);
		
		while (input!=KEY_BACKSPACE && success==FALSE)
		{
			display(grille, highlight_x, highlight_y, player, turn);
			waitinputgrille(&highlight_x, &highlight_y, &input, &turn, grille);
			clear();
			refresh();
			checkvictory(grille, &success);
		}
		
		if (success==TRUE)
		{
			input=0;
			if (turn==0)
			{
				turn=2;
			}
			while (input!=ENTER)
			{
				displayMenu(Menu, highlight_index, nb_ChampMenu, turn);
				waitinputMenu(&highlight_index, &input, nb_ChampMenu);
				clear();
				refresh();
			}
			if (highlight_index==1)
			{
				quitgame=TRUE;
			}
		}
	} while (quitgame==FALSE);
	
	endwin();
	
	return 0;
}
