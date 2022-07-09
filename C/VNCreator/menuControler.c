#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "menuControler.h"
#include "menuView.h"
#include "menuModel.h"



void launchMenu(Settings *s)
{
   /*Lancement du programme en affichant le menu principal, puis elle laisse le choix à l'utilisateur de naviguer entre les différents champs(Play, Options, Quit) grâce au pavé directionnel et choisir d'accéder au champ qu'il veut en faisant "Entrée". 
   s = variable de la structure "Settings", données des paramètres.*/
   int highlight_index=0, quit_main_menu=FALSE, quit_list_vn_menu=FALSE, text_speed=s->text_speed, text_color=s->text_color, keyboard_input=0, nb_champ_menu=0;
   char* main_menu[NB_CHAMP_MENU];
   char* settings_menu[NB_CHAMP_MENU];
   char* list_vn_menu[NBMAX_VN];
   
   initInterface();
	do{
		highlight_index=0, keyboard_input=0, nb_champ_menu=NB_CHAMP_MENU;
		
		intMainMenu(main_menu);
		while (keyboard_input!=ENTER)//Le menu principal est affiché et la possibilité est donné à l'utilisateur de naviguer entre les différents champs tant que celui-ci n'a pas décidé d'accéder à un champ en tapant sur "Entrée"
		{
			displayMenu(main_menu, highlight_index, text_color, nb_champ_menu);
			waitInputMenu(&highlight_index, &keyboard_input, nb_champ_menu);
			clear();
			refresh();
		}
		switch(highlight_index)
	 	{
		  	case 0: //L'utilisateur veut accéder au champ "Play"
		  		do{
			  		highlight_index=0, keyboard_input=0, nb_champ_menu=0;
			  		
			  		intListVNMenu(list_vn_menu, &nb_champ_menu);
			  		while (keyboard_input!=ENTER)//Le menu list_vn est affiché et la possibilité est donné à l'utilisateur de naviguer entre les différents champs tant que celui-ci n'a pas décidé d'accéder à un champ en tapant sur "Entrée"
			  		{
			  			displayMenu(list_vn_menu, highlight_index, text_color, nb_champ_menu);
				  		waitInputMenu(&highlight_index, &keyboard_input, nb_champ_menu);
				  		clear();
						refresh();
			  		}
			  		if (highlight_index==nb_champ_menu-2)//Si l'utilisateur a choisi de créer un nouveau Visual Novel
			  		{
			  			char* new_vn_name_directory=(char*) malloc(255);
			  			enterNewVNname(text_color, new_vn_name_directory);
			  			createVN(new_vn_name_directory);
			  			clear();
			  			refresh();
			  			free(new_vn_name_directory), new_vn_name_directory=NULL;
			  		}
			  		else if (highlight_index==nb_champ_menu-1)//Si l'utilisateur a choisi d'accéder au champ "Return" pour revenir au menu principal
			  		{
			  			quit_list_vn_menu=TRUE;
			  			freeMenu(list_vn_menu, nb_champ_menu);
			  		}
			  		else//Si l'utilisateur a choisi un Visual Novel à jouer
			  		{
			  			s->vn_folder_name=(char*) malloc(255);
			  			
			  			s->flag_is_allocated=TRUE;
			  			strcpy(s->vn_folder_name, list_vn_menu[highlight_index]);
			  			quit_list_vn_menu=TRUE;
			  			quit_main_menu=TRUE;
			  			freeMenu(list_vn_menu, nb_champ_menu);
			  			
			  			nb_champ_menu=NB_CHAMP_MENU;
			  			freeMenu(main_menu, nb_champ_menu);
			  		}
			  	}while(quit_list_vn_menu!=TRUE);
		  		break;
		  	case 1: //L'utilisateur veut accéder au champ "Options"
		  		highlight_index=0, keyboard_input=0, nb_champ_menu=NB_CHAMP_MENU;
		  		
		  		while (keyboard_input!=ENTER)//Le menu des paramètres est affiché et la possibilité est donnée à l'utilisateur de naviguer entre les différents champs et modifier les paramètres tant que celui-ci n'a pas décidé d'appuyer sur "Entrée" pour appliquer les nouveaux paramètres
		  		{
		  			intSettingsMenu(settings_menu, text_speed, text_color);
		  			displayMenu(settings_menu, highlight_index, text_color, nb_champ_menu);
		  			waitInputSettingsMenu(&highlight_index, &keyboard_input, &text_speed, &text_color, nb_champ_menu);
		  			clear();
		  			refresh();
		  		}
		  		setSettings(&*s, text_speed, text_color);
		  		freeMenu(settings_menu, nb_champ_menu);
		  		break;
		  	case 2: //L'utiisateur veut accéder au champ "Quit"
				if (s->flag_is_allocated==TRUE)//Si VNFolder a reçu un malloc, alors la mémoire RAM alloué sera libérée
				{
					free(s->vn_folder_name), s->vn_folder_name=NULL;
				}
				freeMenu(main_menu, nb_champ_menu);
				endwin();
				exit(1);
			  	break;
		  	default:
			  	break;
		}
	}while(quit_main_menu!=TRUE);//Tant que quit_main_menu n'est pas égale à TRUE, on ne quittera pas le menu principal.
}

void initializeSettings(Settings *s)
{
	/*permet d'accéder à la fonction intSettings.
	s = variable de la structure "Settings" qui va contenir les données des paramètres et qui vont être envoyés à intSettings.*/ 
	intSettings(&*s);
}
