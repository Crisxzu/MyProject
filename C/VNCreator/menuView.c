#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "menuView.h"


void displayMenu(char** Menu, const int highlight_index, const int text_color, const int nb_champ_menu)
{
	/*Affiche les différents champs du menu qui est entré en paramètres.
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	Menu = tableau(de string ou char*), champs du menu.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).
	nb_champ_menu = int, nombre total de champs du menu.*/	
	int i_champ=0;
	
	attron(COLOR_PAIR(text_color));
   printw("== Menu ==\n");
   attroff(COLOR_PAIR(text_color));
   for (i_champ = 0; i_champ < nb_champ_menu; i_champ++) //On affiche chaque champ du menu en les affichant un par un jusqu'à les avoir tous affiché
   {
   	if (i_champ==highlight_index)//Si le champ affiché est aussi celui qui est selectionné actuellement par l'utilisateur, il sera affichée vert
   	{
   		attron(COLOR_PAIR(6));
			printw("%s\n", Menu[i_champ]);
			attroff(COLOR_PAIR(6));
   	}
   	else //Sinon, il est simplement affiché avec la couleur de texte choisie dans les paramètres
   	{
   		attron(COLOR_PAIR(text_color));
   		printw("%s\n", Menu[i_champ]);
   		attroff(COLOR_PAIR(text_color));
   	}
   } 
   
}

void waitInputMenu(int *highlight_index, int *keyboard_input, const int nb_champ_menu)
{
	/*Permet à l'utilisateur de se déplacer dans le menu via le pavé directionnel(précisément les touches "HAUT" et "BAS") et de choisir d'accéder à un champ du Menu en faisant "Entrée".
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel ou "Entrée"), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. 
	nb_champ_menu = int, nombre total de champs du menu.*/
   curs_set(0);
   noecho(); 
   keypad(stdscr, TRUE);
	*keyboard_input=getch();
	if (*keyboard_input==KEY_UP)
	{
		*highlight_index=*highlight_index-1;
		if (*highlight_index<0)//Si l'utilisateur appuie sur "HAUT" alors qu'il est déjà tout en haut de la liste des champs, le champ selectionné sera celui qui se trouve en dernière position de la liste.
		{
			*highlight_index=nb_champ_menu-1;
		}
	}	
	else if (*keyboard_input==KEY_DOWN)
	{
		*highlight_index=*highlight_index+1;
		if (*highlight_index>nb_champ_menu-1)//Si l'utilisateur appuie sur "BAS" alors qu'il est déjà tout en bas de la liste des champs, le champ selectionnée sera celui qui se trouve en première position de la liste.
		{
			*highlight_index=0;
		}
	}
	else if (*keyboard_input==ENTER)
	{
		keypad(stdscr, FALSE);
	}	
}


void waitInputSettingsMenu(int *highlight_index, int *keyboard_input, int *text_speed, int *text_color, const int nb_champ_menu)
{
	/*Permet à l'utilisateur de se déplacer dans le menu et de modifier les différents paramètres via le pavé directionnel(précisément les touches "HAUT", "BAS", "GAUCHE" et "DROITE") et de choisir de retourner au menu principal en faisant "Entrée".
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel ou "Entrée"), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. 
	text_speed = int, vitesse de défilement du texte des différents dialogues des Visual Novel, sa valeur sera modifié en fonction des mouvements du pavé directionnel("GAUCHE" et "DROITE").
	text_color = int, couleur du texte des différents menus qui seront affichés*, sa valeur sera modifié en fonction des mouvements du pavé directionnel("GAUCHE" et "DROITE").
	nb_champ_menu = int, nombre total de champs du menu.*/
	curs_set(0);
   noecho(); 
   keypad(stdscr, TRUE);
	*keyboard_input=getch();
	if (*keyboard_input==KEY_UP)
	{
		*highlight_index=*highlight_index-1;
		if (*highlight_index<0)//Si l'utilisateur appuie sur "HAUT" alors qu'il est déjà tout en haut de la liste des champs, le champ selectionné sera celui qui se trouve en dernière position de la liste.
		{
			*highlight_index=nb_champ_menu-1;
		}
	}	
	else if (*keyboard_input==KEY_DOWN)
	{
		*highlight_index=*highlight_index+1;
		if (*highlight_index>nb_champ_menu-1)//Si l'utilisateur appuie sur "BAS" alors qu'il est déjà tout en bas de la liste des champs, le champ selectionnée sera celui qui se trouve en première position de la liste.
		{
			*highlight_index=0;
		}
	}
	else if (*keyboard_input==KEY_LEFT)
	{
		if (*highlight_index==0)//Si le champ selectionné est celui de "Textspeed: X",X qui est égale à la valeur de text_speed, les changements de valeurs que l'utilisateur fera en faisant "GAUCHE" ne seront appliqués qu'au text_speed.
		{
			*text_speed=*text_speed-1;
			if (*text_speed<1)//Si l'utilisateur appuie sur "GAUCHE" alors que la valeur de text_speed était déjà de 1(valeur minimale), alors text_speed prendra une valeur de 10(valeur maximale)
			{
				*text_speed=10;
			}
		}
		else if (*highlight_index==1)//Si le champ selectionné est celui de "Textcolor: Y", où Y est égale à la valeur de text_color, les changements de valeurs que l'utilisateur fera en faisant "GAUCHE" ne seront appliqués qu'au text_color.
		{
			*text_color=*text_color-1;
			if (*text_color<0)//Si l'utilisateur appuie sur "GAUCHE" alors la valeur de text_color était déjà de 0(valeur minimale) soit la couleur "WHITE" Blanc, alors text_color prendra la valeur 5(valeur maximale) soit la couleur "YELLOW" Jaune.
			{
				*text_color=5;
			}
		}
	}
	else if (*keyboard_input==KEY_RIGHT)
	{
		if (*highlight_index==0)//Si le champ selectionné est celui de "Textspeed: X",X qui est égale à la valeur de text_speed, les changements de valeurs que l'utilisateur fera en faisant "DROITE" ne seront appliqués qu'au text_speed.
		{
			*text_speed=*text_speed+1;
			if (*text_speed>10)//Si l'utilisateur appuie sur "DROITE" alors que la valeur de text_speed était déjà de 10(valeur maximale), alors text_speed prendra une valeur de 1(valeur minimale)
			{
				*text_speed=1;
			}
		}
		else if (*highlight_index==1)//Si le champ selectionné est celui de "Textcolor: Y", où Y est égale à la valeur de text_color, les changements de valeurs que l'utilisateur fera en faisant "DROITE" ne seront appliqués qu'au text_color
		{
			*text_color=*text_color+1;
			if (*text_color>5)//Si l'utilisateur appuie sur "DROITE" alors la valeur de text_color était déjà de 5(valeur maximale) soit la couleur "YELLOW" Jaune, alors text_color prendra la valeur 0(valeur minimale) soit la couleur "WHITE" Blanc.
			{
				*text_color=0;
			}
		}
	}
	else if (*keyboard_input==ENTER)
	{
		keypad(stdscr, FALSE);
	}
}

void enterNewVNname(const int text_color, char* new_vn_name_directory)
{
	/*Permet à l'utilisateur d'entrer le nom du nouveau Visual Novel qu'il souhaite créer.
	text_color = int, couleur choisie qui va permettre à la fonction d'afficher le menu avec celle-ci.
	new_vn_name_directory = char* ou string, emplacement du Visual Novel que l'utilisateur souhaite créer.*/
	char* new_vn_name=(char*) malloc(255);
	
	attron(COLOR_PAIR(text_color));
	printw("== Entrez le nom du nouveau Visual Novel ==\n");
	curs_set(1);
	echo();
	getstr(new_vn_name);
	attroff(COLOR_PAIR(text_color));
	
	sprintf(new_vn_name_directory, "VN/%s", new_vn_name);	
	free(new_vn_name), new_vn_name=NULL;
}
