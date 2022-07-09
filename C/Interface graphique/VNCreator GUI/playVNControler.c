#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "playVNControler.h"
#include "playVNModel.h"	
#include "playVNView.h"


	/*Permet de jouer le Visual Novel, celui choisi par l'utilisateur en affichant un menu qui va lui permettre de choisir entre créer une nouvelle partie ou en charger une ou encore de revenir au menu principal. L'utiisateur aura aussi la possibilité au cours de sa partie d'ajouter des dialogues et de les modifier, de créer un nouveau background ou un nouvelle photo de profil pour un personnage et de faire des choix s'il y en a.
	s = variable de la structure "Settings" contenant les différentes données des paramètres ainsi que le nom du Visual Novel à jouer*/
void playVN(Settings *s)
{
	
	Dialogue dia;
	
	dia.length_currentRoute=0;
	dia.i_currentBranch=0;
	dia.dia_text=(char*) malloc(1000);
	dia.background_pixbuf=NULL;
	dia.profile_picture_pixbuf=NULL;
	dia.character_name=(char*) malloc(1000);
	
	int text_color=s->text_color, highlight_index=0, nb_champ_menu=0, keyboard_input=0, endofVN=FALSE, highlight_choice=0, choice_is_detected=FALSE, nb_choice=0, flag_is_allocated[NBMAX_DIA], nb_actions=0, quit_menu_ingame=FALSE, f_playgame=FALSE;	
	float text_speed=s->text_speed;
	char* vn_folder_name=(char*) malloc(255); char* choice_menu[NBMAX_CHOICE]; char* currentRoute[NBMAX_DIA]; char* user_actions[NBMAX_ACTIONS]; char* menu_ingame[NB_CHAMP_MENU_INGAME];
	
	strcpy(vn_folder_name, s->vn_folder_name);
	intMenuInGame(menu_ingame, &highlight_index, vn_folder_name);
	
	 //Permet de garder l'utiisateur dans le menu in game tant qu'il n'a pas choisi de lancer une partie ou de revenir au menu principal
	do
	{
		dia.length_currentRoute=0, dia.i_currentBranch=0, nb_choice=0, nb_actions=0, choice_is_detected=FALSE, endofVN=FALSE;
		highlight_index=0, keyboard_input=0, nb_champ_menu=NB_CHAMP_MENU_INGAME, f_playgame=FALSE;
		
		displayMenuForPlayVN(__struct_global.menu_ingame->box);
		waitInputMenuForPlayVN();

		switch(highlight_index)
		{
			//L'utiisateur veut accéder au champ "Newgame"
			case 0:
				intFlagIsAllocated(flag_is_allocated);
				f_playgame=TRUE;
				hideMenuForPlayVN(__struct_global.menu_ingame->box);
				break;
			
			//L'utiisateur veut accéder au champ "Loadgame"
			case 1:
				highlight_index=0, nb_champ_menu=NB_CHAMP_LOADGAME_MENU;
				char* loadgame_menu[NB_CHAMP_LOADGAME_MENU];
				
				initLoadGameMenuDialog(loadgame_menu, nb_champ_menu, &highlight_index);
				displayMenuForPlayVN(__struct_global.dialog_menu->dialog);
				waitInputMenuForPlayVN();
				
				//Si l'utiisateur choisit une sauvegarde sur laquelle charger sa partie
				if (highlight_index!=5)
				{
					loadGame(currentRoute, &dia.length_currentRoute, &dia.i_currentBranch, user_actions, &nb_actions, highlight_index, loadgame_menu, vn_folder_name);
					
					//Si l'utiisateur a choisi une slot sur laquelle se trouve une sauvegarde
					if (__struct_global.slot_isSelected)
					{
						loadFlagIsAllocated(flag_is_allocated, dia.length_currentRoute);
						f_playgame=TRUE;
						__struct_global.slot_isSelected=FALSE;
					}
				}
				hideMenuForPlayVN(__struct_global.menu_ingame->box);
				hideMenuForPlayVN(__struct_global.dialog_menu->dialog);
				destroyMenuForPlayVN(__struct_global.dialog_menu->dialog);
				freeMenuForPlayVN(loadgame_menu, nb_champ_menu);
				free(__struct_global.dialog_menu), __struct_global.dialog_menu=NULL;
				break;
			
			//L'utiisateur veut accéder au champ "Return"
			case 2:
				quit_menu_ingame=TRUE;
				hideMenuForPlayVN(__struct_global.menu_ingame->box);
				destroyMenuForPlayVN(__struct_global.menu_ingame->box);
				free(vn_folder_name), vn_folder_name=NULL;
				freeMenuForPlayVN(menu_ingame, nb_champ_menu);
				free(__struct_global.menu_ingame), __struct_global.menu_ingame=NULL;
				break;
		}
		
		
		//Si l'utiisateur a choisi de lancer une partie soit en choisissant de faire une nouvelle partie ou de charger une partie
		if (f_playgame==TRUE)
		{
			highlight_index=0, keyboard_input=0;
			
			initVNView(text_color, &keyboard_input);
			
			//Permet de garder l'utiisateur dans l'interface de jeu tant que celui-ci n'a pas décidé de quitter en appuyabt sur la touche "Q"
			while (keyboard_input!=KEY_Q)
			{
				loadDia(vn_folder_name, &dia, currentRoute, &endofVN, &choice_is_detected, choice_menu, &nb_choice, highlight_choice, flag_is_allocated, user_actions, &nb_actions, keyboard_input);
				displayDia(vn_folder_name, &dia, highlight_index, text_color, endofVN, text_speed);
				waitInputDia(&highlight_index, &keyboard_input, &dia, endofVN);
				
				//Si l'utilisateur appuie sur la touche "D", il pourra éditer le dialogue qui est actuellement affiché ou créer un dialogue si celui-ci se trouve au niveau "THE END" du Visual Novel
				if (keyboard_input==KEY_D)
				{
					choice_is_detected=FALSE;
					editDia(vn_folder_name, dia.length_currentRoute, currentRoute, dia.i_currentBranch);	
				}
				
				//Si l'utilisateur appuie sur la touche "P", il pourra créer ajouter une nouvelle image
				else if (keyboard_input==KEY_P)
				{
					choice_is_detected=FALSE;
					addImage(vn_folder_name);
				}
				
				//Si l'utilisateur appuie sur la touche "S", il pourra sauvegarder sur une slot de sauvegarde
				else if (keyboard_input==KEY_S)
				{
					char* savegame_menu[NB_CHAMP_SAVEGAME_MENU];
					
					nb_champ_menu=NB_CHAMP_SAVEGAME_MENU;
					highlight_choice=0;
					intSaveGameMenu(savegame_menu, nb_champ_menu, &highlight_choice);
					displayMenuForPlayVN(__struct_global.dialog_menu->dialog);
					waitInputMenuForPlayVN();
					
					//Si l'utiisateur choisit une slot sur laquelle sauvegarder sa partie
					if (highlight_choice!=5)
					{
						saveGame(currentRoute, dia.length_currentRoute, dia.i_currentBranch, user_actions, nb_actions, highlight_choice, savegame_menu, vn_folder_name);					
					}
					
					hideMenuForPlayVN(__struct_global.dialog_menu->dialog);
					destroyMenuForPlayVN(__struct_global.dialog_menu->dialog);
					freeMenuForPlayVN(savegame_menu, nb_champ_menu);
					free(__struct_global.dialog_menu), __struct_global.dialog_menu=NULL;
					choice_is_detected=FALSE;
				}
				
				//Si l'utilisateur choisit de faire "Next" alors qu'on se trouve à une partie du Visual Novel où il faut faire des choix
				else if (choice_is_detected==TRUE && keyboard_input==KEY_RIGHT)
				{
				
					highlight_choice=0;
					displayChoiceMenu(choice_menu, &highlight_choice, nb_choice, &keyboard_input);
					
					//Si l'utiisateur a fait un choix
					if (__struct_global.f_choice_is_made==TRUE)
					{
						getUserActions(&nb_actions, user_actions, highlight_choice, choice_menu);
						__struct_global.f_choice_is_made=FALSE;	
					}
					freeMenuForPlayVN(choice_menu, nb_choice);
				}
			}
			hideMenuForPlayVN(__struct_global.vn_view->overlay_container_for_background);
			gtk_window_remove_accel_group(GTK_WINDOW(__struct_global.main_window), __struct_global.vn_view->accel_group);
			destroyMenuForPlayVN(__struct_global.vn_view->overlay_container_for_background);
			free(__struct_global.vn_view), __struct_global.vn_view=NULL;
			freeCurrentRoute(&dia, currentRoute, user_actions, nb_actions);
			setFlagIsAllocated(flag_is_allocated);
		}
	} while (quit_menu_ingame!=TRUE);
	freeDia(&dia);
}

