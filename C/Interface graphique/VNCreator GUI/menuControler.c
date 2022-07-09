#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "menuControler.h"
#include "menuView.h"
#include "menuModel.h"

  /*Lancement du programme en affichant le menu principal, puis elle laisse le choix à l'utilisateur de naviguer entre les différents champs(Play, Options, Quit) grâce au pavé directionnel ou sa souris et choisir d'accéder au champ qu'il veut en faisant "Entrée" ou en cliquant dessus. 
   s = variable de la structure "Settings", données des paramètres.*/
void launchMenu(Settings *s)
{
   int highlight_index=0, f_quit_main_menu=FALSE, f_quit_list_vn_menu=FALSE, text_color=s->text_color, nb_champ_menu=0;
   float text_speed=s->text_speed;
   char* main_menu[NB_CHAMP_MENU];
   char* settings_menu[NB_CHAMP_MENU];
   char* list_vn_menu[NBMAX_VN];
   
   if (!__struct_global.f_window_is_already_created)
   {
   	initStructGlobal();
   	initMainWindow(&highlight_index);
   	__struct_global.f_window_is_already_created=TRUE;	
   }
   initMainMenu(main_menu, &highlight_index);
   
   //Permet de garder l'utiisateur dans le menu principal tant qu'il n'a pas choisi de lancer une partie ou quitter le programme
	do{
		highlight_index=0, nb_champ_menu=NB_CHAMP_MENU;
		
		displayMenu(__struct_global.main_menu->box);
		waitInputMenu();
		
		switch(highlight_index)
	 	{
		  	//L'utilisateur veut accéder au champ "Play"
		  	case 0: 
		  		
		  		highlight_index=0, nb_champ_menu=0;
		  		
		  		hideMenu(__struct_global.main_menu->box);
		  		initListVNMenu(list_vn_menu, &nb_champ_menu);
		  		initListVNMenuBox(list_vn_menu, nb_champ_menu, &highlight_index);
	  			displayMenu(__struct_global.list_vn_menu->box);
	  			
	  			do{
			  		waitInputMenu();

			  		//Si l'utilisateur a choisi de créer un nouveau Visual Novel
			  		if (highlight_index==1)
			  		{
			  			char* new_vn_name_directory=(char*) malloc(255);
			  			enterNewVNname(new_vn_name_directory);
			  			
			  			//Si l'utiisateur a appuyé sur le bouton "Create"
			  			if (__struct_global.b_isSelected)
			  			{	
			  				createVN(new_vn_name_directory);
			  				__struct_global.b_isSelected=FALSE;
			  			}
			  			
			  			free(new_vn_name_directory), new_vn_name_directory=NULL;
			  		}
			  		
			  		//Si l'utilisateur a choisi d'accéder au champ "Return" pour revenir au menu principal
			  		else if (highlight_index==2)
			  		{
			  			f_quit_list_vn_menu=TRUE;
			  			hideMenu(__struct_global.list_vn_menu->box);
			  			freeMenu(list_vn_menu, nb_champ_menu);
			  			destroyMenu(__struct_global.list_vn_menu->box);
			  			free(__struct_global.list_vn_menu), __struct_global.list_vn_menu=NULL;
			  		}
			  		
			  		//Si l'utilisateur a choisi un Visual Novel à jouer
			  		else if (highlight_index==0) 
			  		{
			  			
			  			//Si l'utiisateur a choisi un visual novel à jouer
			  			if (__struct_global.vn_isSelected)
			  			{
			  				s->vn_folder_name=gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(__struct_global.list_vn_menu->combo_box_text));
			  				s->flag_is_allocated=TRUE;
			  				f_quit_list_vn_menu=TRUE;
				  			f_quit_main_menu=TRUE;
				  			hideMenu(__struct_global.list_vn_menu->box);
				  			freeMenu(list_vn_menu, nb_champ_menu);
				  			destroyMenu(__struct_global.list_vn_menu->box);
				  			free(__struct_global.list_vn_menu), __struct_global.list_vn_menu=NULL;
				  			
				  			nb_champ_menu=NB_CHAMP_MENU;
				  			freeMenu(main_menu, nb_champ_menu);
				  			hideMenu(__struct_global.main_menu->box);
				  			destroyMenu(__struct_global.main_menu->box);
							free(__struct_global.main_menu), __struct_global.main_menu=NULL;
			  				__struct_global.vn_isSelected=FALSE;
			  			}
			  			
			  		}
			  	}while(f_quit_list_vn_menu!=TRUE);
		  		break;
		  
		  	//L'utilisateur veut accéder au champ "Options"
		  	case 1:
		  
		  		highlight_index=0, nb_champ_menu=NB_CHAMP_MENU;
		  		
		  		hideMenu(__struct_global.main_menu->box);
		  		initSettingsMenu(settings_menu, &text_speed, &text_color, &highlight_index);
		  		displayMenu(__struct_global.settings_menu->box);
				waitInputMenu();
				
		  		setSettings(&*s, text_speed, text_color);
		  		hideMenu(__struct_global.settings_menu->box);
		  		destroyMenu(__struct_global.settings_menu->box);
		  		freeMenu(settings_menu, nb_champ_menu);
		  		free(__struct_global.settings_menu), __struct_global.settings_menu=NULL;
		  		break;
		  	
		  	//L'utiisateur veut accéder au champ "Quit"
		  	case 2: 
				if (s->flag_is_allocated==TRUE)//Si VNFolder a reçu un malloc, alors la mémoire RAM alloué sera libérée
				{
					g_free(s->vn_folder_name), s->vn_folder_name=NULL;
				}
				hideMenu(__struct_global.main_menu->box);
				freeMenu(main_menu, nb_champ_menu);
				destroyMenu(__struct_global.main_menu->box);
				free(__struct_global.main_menu), __struct_global.main_menu=NULL;
				exitProgram(NULL, NULL);
			  	break;
		}
	}while(f_quit_main_menu!=TRUE);
}

	/*permet d'accéder à la fonction intSettings.
	s = variable de la structure "Settings" qui va contenir les données des paramètres et qui vont être envoyés à intSettings.*/ 
void initializeSettings(Settings *s)
{
	intSettings(&*s);
}

	/*Permet d'accéder à la fonction initView.*/
void initializeView(int argc, char** argv)
{
	initView(argc, argv);
}

	/*Permet de quitter le programme.*/
void exitProgram(GtkWidget *widget, gpointer user_data)
{
	free(__struct_global.format_menu_label), __struct_global.format_menu_label=NULL;
	free(__struct_global.format_text_color), __struct_global.format_text_color=NULL;
	free(__struct_global.format_character_name), __struct_global.format_character_name=NULL;
	free(__struct_global.format_dia_text), __struct_global.format_dia_text=NULL;
	exit(1);
	(void)widget;
	(void)user_data;
}
