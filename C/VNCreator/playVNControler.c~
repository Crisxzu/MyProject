#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "playVNControler.h"
#include "playVNModel.h"	
#include "playVNView.h"


void playVN(Settings *s)
{
	/*Permet de jouer le Visual Novel, celui choisi par l'utilisateur en affichant un menu qui va lui permettre de choisir entre créer une nouvelle partie ou en charger une ou encore de revenir au menu principal. L'utiisateur aura aussi la possibilité au cours de sa partie d'ajouter des dialogues et de les modifier, de créer un nouveau background ou un nouvelle photo de profil pour un personnage et de faire des choix s'il y en a.
	s = variable de la structure "Settings" contenant les différentes données des paramètres ainsi que le nom du Visual Novel à jouer*/
	
	Dialogue dia;
	
	dia.length_currentRoute=0;
	dia.i_currentBranch=0;
	dia.dia_text=(char*) malloc(1000);
	dia.background=(char*) malloc(1000);
	dia.profile_picture=(char*) malloc(1000);
	dia.character_name=(char*) malloc(1000);
	
	int text_color=s->text_color, highlight_index=0, nb_champ_menu=0, keyboard_input=0, endofVN=FALSE, highlight_choice=0, choice_is_detected=FALSE, nb_choice=0, flag_is_allocated[NBMAX_DIA], nb_actions=0, quit_menu_ingame=FALSE, go_to_next_prev_dia=FALSE, return_to_menu_ingame=FALSE;
	float text_speed=s->text_speed;
	char* vn_folder_name=(char*) malloc(255); char* next_prev_dia[NB_NEXT_PREV_DIA]; char* choice_menu[NBMAX_CHOICE]; char* currentRoute[NBMAX_DIA]; char* user_actions[NBMAX_ACTIONS]; char* menu_ingame[NB_CHAMP_MENU_INGAME];
	
	strcpy(vn_folder_name, s->vn_folder_name);
	do
	{
		dia.length_currentRoute=0, dia.i_currentBranch=0, nb_choice=0, nb_actions=0, choice_is_detected=FALSE, endofVN=FALSE;
		do
		{
			highlight_index=0, keyboard_input=0, nb_champ_menu=NB_CHAMP_MENU_INGAME, go_to_next_prev_dia=FALSE, return_to_menu_ingame=FALSE;
			
			intMenuInGame(menu_ingame);
			while (keyboard_input!=ENTER)//Le menu playVN est affiché et la possibilité est donnée à l'utiisateur de naviguer entre les différents champs tant que celui-ci n'en a pas choisi un en tapant sur "Entrée"
			{
				displayMenuForPlayVN(menu_ingame, highlight_index, text_color, nb_champ_menu, vn_folder_name);
				waitInputMenuForPlayVN(&highlight_index, &keyboard_input, nb_champ_menu);
				clear();
				refresh();
			}
			
			freeMenuForPlayVN(menu_ingame, nb_champ_menu);

			switch(highlight_index)
			{
				case 0://L'utiisateur veut accéder au champ "Newgame"
					intFlagIsAllocated(flag_is_allocated);
					go_to_next_prev_dia=TRUE;
					break;
				case 1://L'utiisateur veut accéder au champ "Loadgame"
					highlight_index=0, keyboard_input=0;
					char* loadgame_menu[NB_CHAMP_LOADGAME_MENU];
					
					intLoadGameMenu(loadgame_menu, &nb_champ_menu, vn_folder_name);
					while (keyboard_input!=ENTER)//Un menu est affiché avec ses différents champs possibles et la possibilité est donnée à l'utilisateur de naviguer entre ces choix tant que celui-ci n'en a pas choisi un en appuyant sur la touche "Entrée"
					{
						displayMenuForPlayVN(loadgame_menu, highlight_index, text_color, nb_champ_menu, vn_folder_name);
						waitInputMenuForPlayVN(&highlight_index, &keyboard_input, nb_champ_menu);
						clear();
						refresh();
					}
					if (highlight_index==nb_champ_menu-1)//Si l'utiisateur choisit d'accéder au champ "Return" pour revenir au menu playVN
					{
						return_to_menu_ingame=TRUE;
					}
					else//Si l'utiisateur choisit une sauvegarde sur laquelle charger sa partie
					{
						loadGame(currentRoute, &dia.length_currentRoute, &dia.i_currentBranch, user_actions, &nb_actions, highlight_index, loadgame_menu, vn_folder_name);
						loadFlagIsAllocated(flag_is_allocated, dia.length_currentRoute);
						go_to_next_prev_dia=TRUE;
					}
					freeMenuForPlayVN(loadgame_menu, nb_champ_menu);
					break;
				case 2://L'utiisateur veut accéder au champ "Return"
					quit_menu_ingame=TRUE;
					free(vn_folder_name), vn_folder_name=NULL;
					break;
				default:
					break;
			}
		}while(return_to_menu_ingame==TRUE);//Si return_to_menu_ingame = TRUE, alors le menu playVN va être de nouveau affiché
		
		
		if (go_to_next_prev_dia==TRUE)//Si l'utiisateur a choisi de lancer une partie soit en choisissant de faire une nouvelle partie ou de charger une partie
		{
			highlight_index=0, keyboard_input=0;
			
			intNextPrevDia(next_prev_dia);
			nb_champ_menu=NB_NEXT_PREV_DIA;
			idlok(stdscr, TRUE);
			while (keyboard_input!=KEY_Q)//Le dialogue est affiché et la possibilité est donné à l'utilisateur de naviguer entre les différents dialogues du Visual Novel. Pour quitter et revenir au menu playVN, il faut qu'il appuie sur la touche "Q"
			{
				loadDia(vn_folder_name, &dia, currentRoute, &endofVN, &choice_is_detected, choice_menu, &nb_choice, highlight_choice, flag_is_allocated, user_actions, &nb_actions, keyboard_input);
				displayDia(next_prev_dia, vn_folder_name, &dia, highlight_index, text_color, nb_champ_menu, endofVN, text_speed);
				waitInputDia(&highlight_index, &keyboard_input, nb_champ_menu, &dia, endofVN);

				if (keyboard_input==KEY_D)//Si l'utilisateur appuie sur la touche "D", il pourra éditer le dialogue qui est actuellement affiché ou créer un dialogue si celui-ci se trouve au niveau "THE END" du Visual Novel
				{
					choice_is_detected=FALSE;
					editDia(vn_folder_name, dia.length_currentRoute, currentRoute, dia.i_currentBranch);	
				}
				else if (keyboard_input==KEY_B)//Si l'utilisateur appuie sur la touche "B", il pourra créer un nouveau décor
				{
					choice_is_detected=FALSE;
					clear();
					refresh();
					createBackground(vn_folder_name, text_color);
				}
				else if (keyboard_input==KEY_P)//Si l'utilisateur appuie sur la touche "P", il pourra créer une nouvelle photo de profil
				{
					choice_is_detected=FALSE;
					clear();
					refresh();
					createProfilePicture(vn_folder_name, text_color);
				}
				else if (keyboard_input==KEY_S)//Si l'utilisateur appuie sur la touche "S", il pourra sauvegarder sur une slot de sauvegarde
				{
					char* savegame_menu[NB_CHAMP_SAVEGAME_MENU];
					
					nb_champ_menu=NB_CHAMP_SAVEGAME_MENU;
					clear();
					refresh();
					highlight_choice=0;
					intSaveGameMenu(savegame_menu);
					while (keyboard_input!=ENTER)//Un menu est affiché avec ses différents champs possibles et la possibilité est donnée à l'utilisateur de naviguer entre ces choix tant que celui-ci n'en a pas choisi un en appuyant sur la touche "Entrée"
					{
						displayMenuForPlayVN(savegame_menu, highlight_choice, text_color, nb_champ_menu, vn_folder_name);
						waitInputMenuForPlayVN(&highlight_choice, &keyboard_input, nb_champ_menu);
						clear();
						refresh();
					}
					saveGame(currentRoute, dia.length_currentRoute, dia.i_currentBranch, user_actions, nb_actions, highlight_choice, savegame_menu, vn_folder_name);
					freeMenuForPlayVN(savegame_menu, nb_champ_menu);					
					nb_champ_menu=NB_NEXT_PREV_DIA;
				}
				else if (choice_is_detected==TRUE && keyboard_input==KEY_RIGHT)//Si l'utilisateur choisit de faire "Next" alors qu'on se trouve à une partie du Visual Novel où il faut faire des choix
				{
					clear();
					refresh();
					highlight_choice=0;
					while (keyboard_input!=ENTER)//Un menu est affiché avec les différents choix possibles et la possibilité est donnée à l'utilisateur de naviguer entre ces choix tant que celui-ci n'en a pas choisi un en appuyant sur la touche "Entrée"
					{
						displayMenuForPlayVN(choice_menu, highlight_choice, text_color, nb_choice, vn_folder_name);
						waitInputMenuForPlayVN(&highlight_choice, &keyboard_input, nb_choice);
						clear();
						refresh();
					}
					getUserActions(&nb_actions, user_actions, highlight_choice, choice_menu);
					freeMenuForPlayVN(choice_menu, nb_choice);
				}
				clear();
				refresh();
			}
			freeMenuForPlayVN(next_prev_dia, nb_champ_menu);
			freeCurrentRoute(&dia, currentRoute, user_actions, nb_actions);
			setFlagIsAllocated(flag_is_allocated);
			idlok(stdscr, FALSE);
		}
	} while (quit_menu_ingame!=TRUE);//Tant que quit_menu_ingame n'est pas égale à TRUE, on ne quittera pas le menu playVN.
	freeDia(&dia);
}

