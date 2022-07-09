#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h> 
#include "playVNView.h"

	/*Affiche le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à afficher*/
void displayMenuForPlayVN(GtkWidget *menu_box)
{	
	gtk_widget_show_all(menu_box);
}

	/*Cache le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à cacher*/
void hideMenuForPlayVN(GtkWidget *menu_box)
{
	gtk_widget_hide(menu_box);
}

	/*Détruit le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à détruire*/
void destroyMenuForPlayVN(GtkWidget *menu_box)
{
	gtk_widget_destroy(menu_box);
}

	/*Permet de garder le menu affiché tant que l'utiisateur n'a pas appuyé sur un bouton du menu.*/
void waitInputMenuForPlayVN()
{ 	
 	//Permet de garder le menu affiché tant que l'utiisateur n'a pas appuyé sur un bouton du menu.
 	while (!__struct_global.b_isSelected)
 		gtk_main_iteration();
 	
 	__struct_global.b_isSelected=FALSE;	
}

	/*Affiche le contenu d'un fichier dia( plus concrètement le décor, la photo de profil du personnage qui s'exprime en ce moment même, le nom du personnage et le texte du dialogue en lui-même).
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.
	dia = variable de la structure "Dialogue", données d'un fichier dia 
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).
	endofVN = int marquant la fin du Visual Novel.
	text_speed = float, vitesse de défilement du texte du dialogue. P.S= Pour text_speed=1, un caractère est affiché toutes les 50ms, le calcul se fait comme suit: temps pour l'affichage d'un caractère= 50ms/valeur de text_speed.*/
void displayDia(char *vn_folder_name, Dialogue *dia, const int highlight_index, const int text_color, const int endofVN, const float text_speed)
{	
	int i_char=0, f_can_print_next_char=FALSE;
	clock_t oldtime, current_time;
	char* color_name[6]={"white", "blue", "cyan", "red", "magenta", "yellow"};
	gchar *markup_text=NULL, *utf8=NULL;
	GtkTextIter start, end;
	
	//Si l'utiisateur ne se trouve pas à la fin du Visual Novel, un décor, l'image du personnage, le nom du personnage et le texte du dialogue seront affichés
	if (endofVN==FALSE)
	{
		gtk_image_set_from_pixbuf(GTK_IMAGE(__struct_global.vn_view->background), dia->background_pixbuf);
		gtk_image_set_from_pixbuf(GTK_IMAGE(__struct_global.vn_view->profile_pic), dia->profile_picture_pixbuf);
		markup_text=g_markup_printf_escaped(__struct_global.format_character_name, dia->character_name);
		gtk_label_set_markup(GTK_LABEL(__struct_global.vn_view->character_name_label), markup_text);
		g_free(markup_text), markup_text=NULL;
		
		utf8 = g_locale_to_utf8 (dia->dia_text, -1, NULL, NULL, NULL);
		gtk_text_buffer_get_bounds(__struct_global.vn_view->text_buffer, &start, &end);
		gtk_text_buffer_delete(__struct_global.vn_view->text_buffer, &start, &end);
		hideMenuForPlayVN(__struct_global.vn_view->overlay_container_for_background);
		displayMenuForPlayVN(__struct_global.vn_view->overlay_container_for_background);
		//Le texte du dialogue est affiché caractère par caractère, suivant la vitesse de défilement jusqu'au dernier caractère
		do
		{
			
			f_can_print_next_char=FALSE;
			markup_text=g_markup_printf_escaped(__struct_global.format_dia_text, color_name[text_color], utf8[i_char]);
			gtk_text_buffer_insert_markup(__struct_global.vn_view->text_buffer, &start, markup_text, -1);
			while (gtk_events_pending())
				gtk_main_iteration();

			i_char++;
			oldtime=clock();
			
			//Permet de ne pas passer à l'affichage du caractère suivant tant que le temps d'attente n'est pas passé
			while (f_can_print_next_char==FALSE)
			{
				current_time=clock()-oldtime;
				
				//Si le temps d'attentepour l'affichage d'un caractère s'est écoulé(50000=50ms) alors on peut passer à l'affichage du prochain caractère.
				if (current_time>=(50000/text_speed))
				{
					f_can_print_next_char=TRUE;
				}
			}
			g_free(markup_text), markup_text=NULL;
		} while (utf8[i_char]!='\0');
		
		g_free (utf8), utf8 = NULL;
	}
	
	//Si l'utiisateur se trouve à la fin du Visual Novel, "THE END" sera affiché marquant la fin du Visual Novel que l'utilisateur est en train de jouer
	else
	{
		gtk_image_set_from_pixbuf(GTK_IMAGE(__struct_global.vn_view->background), dia->background_pixbuf);
		gtk_image_set_from_pixbuf(GTK_IMAGE(__struct_global.vn_view->profile_pic), dia->profile_picture_pixbuf);
		markup_text=g_markup_printf_escaped(__struct_global.format_character_name, vn_folder_name);
		gtk_label_set_markup(GTK_LABEL(__struct_global.vn_view->character_name_label), markup_text);
		g_free(markup_text), markup_text=NULL;
		
		utf8 = g_locale_to_utf8 (dia->dia_text, -1, NULL, NULL, NULL);
		gtk_text_buffer_get_bounds(__struct_global.vn_view->text_buffer, &start, &end);
		gtk_text_buffer_delete(__struct_global.vn_view->text_buffer, &start, &end);	
		markup_text=g_markup_printf_escaped(__struct_global.format_text_color, color_name[text_color], utf8);
		gtk_text_buffer_insert_markup(__struct_global.vn_view->text_buffer, &start, markup_text, -1);	
		
	}
}

	/*Permet à l'utilisateur de passer d'un dialogue à un autre via le pavé directionnel(précisément les touches "GAUCHE" et "DROITE", les touches "HAUT" et "BAS" serviront dans le cas où le dialogue affiché est trop grand pour la fenêtre ainsi l'utilisateur pourra voir le reste du texte qui se trouve en bas ou celui qui se trouve en haut).
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. 
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	endofVN = int marquant la fin du Visual Novel.*/
void waitInputDia(int *highlight_index, int *keyboard_input, Dialogue *dia, const int endofVN)
{
   waitInputMenuForPlayVN();
   
   //Si l'utilisateur appuie sur "GAUCHE", il passera au dialogue précédent
	if (*keyboard_input==KEY_LEFT)
	{
		*highlight_index=0;
		dia->length_currentRoute=dia->length_currentRoute-1;
		
		//Si l'utilisateur décide de passer au dialogue précédent alors que le dialogue qui est affiché est déjà le premier dialogue alors il n'y aura aucun changement sur la taille de la route
		if (dia->length_currentRoute<0)
		{
			dia->length_currentRoute=0;
		}
		
		//La valeur de i_currentBranch n'est diminué que si celle-ci est supérieure à 0(valeur minimale)
		if (dia->i_currentBranch>0)
		{
			dia->i_currentBranch=dia->i_currentBranch-1;
		}
	}	
	
	//Si l'utilisateur appuie sur "DROITE", il passera au dialogue suivant.
	else if (*keyboard_input==KEY_RIGHT)
	{
		*highlight_index=1;
		
		//Si l'utilisateur ne se trouve pas déjà à la fin du Visual Novel alors en faisant "DROITE", la taille de route va augmenter pour passer au dialogue suivant. Sinon, elle restera inchangé
		if (endofVN!=TRUE)
		{
			dia->length_currentRoute=dia->length_currentRoute+1;
		}
		
		//La valeur de i_currentBranch  n'est augmenté que si celle-ci est supérieure ou égale 0(valeur minimale)
		if (dia->i_currentBranch>=0)
		{
			dia->i_currentBranch=dia->i_currentBranch+1;
		}
	}
}

	/*Permet à l'utilisateur d'ajouter une nouvelle image que ça soit un background ou une profile_picture.
	vn_folder_name = string ou char*, nom du Visual Novel.*/
void addImage(char *vn_folder_name)
{
	gchar* directory_new_profile_picture_file=NULL, *type_file_name=NULL; 
	char* system_command_name=malloc(255);
	GtkWidget *add_image_dialog=NULL, *content_area=NULL, *selection_file_button=NULL, *combo_box_text=NULL;
	int file_isSelected=FALSE, type_file_isSelected=FALSE;
	
	//Crée une boîte de dialogue pour permettre à l'utiisateur d'ajouter l'image qu'il souhaite
	add_image_dialog=gtk_dialog_new_with_buttons("Choisissez l'image que vous voulez ajouter", GTK_WINDOW(__struct_global.main_window), GTK_DIALOG_MODAL, "Return", GTK_RESPONSE_CANCEL, "Add", GTK_RESPONSE_ACCEPT, NULL);
	content_area=gtk_dialog_get_content_area(GTK_DIALOG(add_image_dialog));
	selection_file_button=gtk_file_chooser_button_new(NULL, GTK_FILE_CHOOSER_ACTION_OPEN);
	combo_box_text=gtk_combo_box_text_new();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo_box_text), "background");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo_box_text), "profilepic");
	gtk_box_pack_start(GTK_BOX(content_area), selection_file_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(content_area), combo_box_text, FALSE, FALSE, 0);
	
	g_signal_connect(G_OBJECT(selection_file_button), "file-set", G_CALLBACK(fileIsSelected), &file_isSelected);
	g_signal_connect(G_OBJECT(combo_box_text), "changed", G_CALLBACK(typeFileIsSeleted), &type_file_isSelected);
	
	//Affiche cette boîte de dialogue
	gtk_widget_show_all(add_image_dialog);
	
	//Si l'utiisateur a appuyé sur le bouton "Add"
	if (gtk_dialog_run(GTK_DIALOG(add_image_dialog))==GTK_RESPONSE_ACCEPT)
	{
		if (file_isSelected==TRUE && type_file_isSelected==TRUE)
		{
			directory_new_profile_picture_file=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(selection_file_button));
			type_file_name=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box_text));
			sprintf(system_command_name, "cp %s VN/%s/img/%s/", directory_new_profile_picture_file, vn_folder_name, type_file_name);
			system(system_command_name);
		}
		
	}
	
	gtk_widget_destroy(add_image_dialog);
	
	free(system_command_name), system_command_name=NULL;
	g_free(directory_new_profile_picture_file), directory_new_profile_picture_file=NULL;
}

	/*Permet de signaler que l'utiisateur a sélectionné un fichier*/
void fileIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *file_isSelected=(int*)user_data;
	
	*file_isSelected=TRUE;
	
	(void)widget;
}

	/*Permet de signaler que l'utiisateur a choisi un type de fichier*/
void typeFileIsSeleted(GtkWidget *widget, gpointer user_data)
{
	int *type_file_isSelected=(int*)user_data;
	
	*type_file_isSelected=TRUE;
	
	(void)widget;
}

	/*Permet à l'utilisateur d'éditer un dialogue et d'accesoirement de créer un nouveau dialogue.
	vn_folder_name = string ou char*, nom du Visual Novel.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
void editDia(char *vn_folder_name, const int length_currentRoute, char** currentRoute, const int i_currentBranch)
{
	FILE *dia_file=NULL;
	char* system_command_name=(char*) malloc(255); char* dia_file_name=(char*) malloc(255);
	
	sprintf(dia_file_name, "VN/%s/%s.dia", vn_folder_name, currentRoute[length_currentRoute]);
	dia_file=fopen(dia_file_name, "r");
	
	//Si le fichier "dia" à éditer existe
	if (dia_file!=NULL)
	{
		sprintf(system_command_name, "gedit %s", dia_file_name);
		system(system_command_name);
	}
	
	//Si le fichier "dia" à éditer n'existe pas, il va être créer
	else
	{
		dia_file=fopen(dia_file_name, "w");
		setDefaultDataInFile(dia_file, currentRoute, length_currentRoute, i_currentBranch);
		sprintf(system_command_name, "gedit %s", dia_file_name);
		system(system_command_name);
	}
	fclose(dia_file), dia_file=NULL;
	free(system_command_name), system_command_name=NULL;
	free(dia_file_name), dia_file_name=NULL;
}

	/*Permet d'insérer dans le nouveau fichier "dia" des données par défaut(Pas de choix, le nom du fichier qui devrait potentiellement le suivre, un emplacement pour insérer le nom du décor, de la photo de profil et du nom du personnage et un emplacement pour insérer un dialogue).
	dia_file = variable FILE, fichier dia.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
void setDefaultDataInFile(FILE *dia_file, char** currentRoute, const int length_currentRoute, const int i_currentBranch)
{
	int length_dia_file_name=0, i_char=0, j_char=0; 
	char* next_dia_file_name=(char*) malloc(255);
	
	length_dia_file_name=(unsigned)strlen(currentRoute[length_currentRoute]);
	i_char=length_dia_file_name-2;
	
	//Si le nom du fichier "dia" qui va permettre de mettre au point le nom du prochain fichier suit un format XXXX, la fonction prendra la valeur d'i_currentBranch et l'augmentera de 1 pour avoir le nom du prochain fichier et aussi le nouvel index de fichier
	if (length_dia_file_name==4)
	{
		sprintf(next_dia_file_name, "%04d", i_currentBranch+1);
	}
	
	//Si le nom du fichier "dia" qui va permettre de mettre au point le nom du prochain fichier suit un autre format, la fonction prendra la valeur d'i_currentBranch et l'augmentera de 1 pour avoir le nouvel index qu'il va attribuer au nom du fichier "dia" pour avoir le nom du prochain fichier
	else if(length_dia_file_name>4)
	{
		char *i_currentBranch_str=(char*) malloc(5);
		
		sprintf(i_currentBranch_str, "%02d", i_currentBranch+1);
		strcpy(next_dia_file_name, currentRoute[length_currentRoute]);
		
		//Attribution du nouvel index au nom du prochain fichier "dia" caractère par caractère jusqu'à ce tous les caractères soient insérés
		while (next_dia_file_name[i_char]!='\0')
		{
			next_dia_file_name[i_char]=i_currentBranch_str[j_char];
			j_char++; i_char++;	
		}
		free(i_currentBranch_str), i_currentBranch_str=NULL;
	}
	fprintf(dia_file, "choice= 0 (goto) %s\nbackground= Insérer le nom d'un fichier image\nprofilepicture= Insérer le nom d'un fichier image\ncharactername= Insérer le nom du personnage\ndialogue= Ecrire le dialogue ici\n\nFormat par défaut, veuillez modifier en fonction de vos besoins.(ce texte est à effacer), nombre de caractères max 415\n", next_dia_file_name);
	free(next_dia_file_name), next_dia_file_name=NULL;
}

	/*Permet d'iniatiliser des champs du menu ingame, les champs "Newgame" pour une nouvelle partie, "Loadgame" pour charger une partie, "Return" pour retourner au menu principal.
	menu_ingame = Tableau de char* ou string, champs du menu ingame.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.
	vn_folder_name = string ou char*, nom du Visual Novel.*/
void intMenuInGame(char** menu_ingame, int *highlight_index, const char *vn_folder_name)
{
	__struct_global.menu_ingame=malloc(sizeof(Menu_ingame));
	gchar *menu_ingame_label_str=NULL;
	
	menu_ingame[0]=(char*) malloc(255);
	menu_ingame[1]=(char*) malloc(255);
	menu_ingame[2]=(char*) malloc(255);
	
	//On initialise les champs du menu
	strcpy(menu_ingame[0], "_Newgame");
	strcpy(menu_ingame[1], "_Loadgame");
	strcpy(menu_ingame[2], "_Return");
	
	//Crée le label du menu
	__struct_global.menu_ingame->label=gtk_label_new(NULL);
	menu_ingame_label_str=g_markup_printf_escaped(__struct_global.format_menu_label, vn_folder_name);
	gtk_label_set_markup(GTK_LABEL(__struct_global.menu_ingame->label), menu_ingame_label_str);
	g_free(menu_ingame_label_str), menu_ingame_label_str=NULL;
	
	//Crée la box qui va contenir les différents éléments du menu
	__struct_global.menu_ingame->box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_set_homogeneous(GTK_BOX(__struct_global.menu_ingame->box), FALSE);
	
	//Crée la box qui va contenir les boutons du menu
	__struct_global.menu_ingame->button_box=gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_box_set_spacing(GTK_BOX(__struct_global.menu_ingame->button_box), 10);
	
	//Crée les boutons du menu
	__struct_global.menu_ingame->newgame_button=gtk_button_new_with_mnemonic(menu_ingame[0]);
	__struct_global.menu_ingame->loadgame_button=gtk_button_new_with_mnemonic(menu_ingame[1]);
	__struct_global.menu_ingame->return_button=gtk_button_new_with_mnemonic(menu_ingame[2]);
	
	//Insère la box qui contenir les éléments du menu dans celle de la fenêtre principal
	gtk_box_pack_start(GTK_BOX(__struct_global.main_box), __struct_global.menu_ingame->box, TRUE, TRUE, 0);
	
	//Insère dans la box du menu le label et la box des boutons
	gtk_box_pack_start(GTK_BOX(__struct_global.menu_ingame->box), __struct_global.menu_ingame->label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.menu_ingame->box), __struct_global.menu_ingame->button_box, TRUE, FALSE, 0);
	
	//Insère dans la box des boutons les différents boutons du menu
	gtk_box_pack_start(GTK_BOX(__struct_global.menu_ingame->button_box), __struct_global.menu_ingame->newgame_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.menu_ingame->button_box), __struct_global.menu_ingame->loadgame_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.menu_ingame->button_box), __struct_global.menu_ingame->return_button, FALSE, FALSE, 0);
	
	//Connecte à chaque bouton du menu une fonction spécifique
	g_signal_connect(G_OBJECT(__struct_global.menu_ingame->newgame_button), "clicked", G_CALLBACK(newgameIsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.menu_ingame->loadgame_button), "clicked", G_CALLBACK(loadgameIsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.menu_ingame->return_button), "clicked", G_CALLBACK(returnIsSelectedForPlayVN), highlight_index);
}

	/*Signale que l'utiisateur a appuyé sur le bouton "Newgame"*/
void newgameIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=0;
	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur le bouton "Loadgame"*/
void loadgameIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=1;
	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur le bouton "Return"*/
void returnIsSelectedForPlayVN(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=2;
	
	(void)widget;
}

	/*Permet d'iniatiliser des champs du menu savegame, les champs "Slot 1", "Slot 2", "Slot 3", "Slot 4", "Slot 5". 
	savegame_menu = Tableau de char* ou string, champs du menu savegame.
	nb_champ_menu = nombre total de champ que le menu aura.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void intSaveGameMenu(char** savegame_menu, const int nb_champ_menu, int *highlight_index)
{	
	__struct_global.dialog_menu=malloc(sizeof(Dialog_menu));
	int i=0;
	
	savegame_menu[0]=(char*) malloc(255);
	savegame_menu[1]=(char*) malloc(255);
	savegame_menu[2]=(char*) malloc(255);
	savegame_menu[3]=(char*) malloc(255);
	savegame_menu[4]=(char*) malloc(255);
	savegame_menu[5]=(char*) malloc(255);
	
	//On initialise les champs du menu
	strcpy(savegame_menu[0], "Slot 1");
	strcpy(savegame_menu[1], "Slot 2");
	strcpy(savegame_menu[2], "Slot 3");
	strcpy(savegame_menu[3], "Slot 4");
	strcpy(savegame_menu[4], "Slot 5");
	strcpy(savegame_menu[5], "Return");
	
	//Crée une boîte de dialogue pour permettre à l'utiisateur de choisir sur quel slot il veut sauvegarder sa partie
	__struct_global.dialog_menu->dialog=gtk_dialog_new_with_buttons("Choisissez sur quel slot sauvegarder la partie", GTK_WINDOW(__struct_global.main_window), GTK_DIALOG_MODAL, NULL, NULL);
	__struct_global.dialog_menu->content_area=gtk_dialog_get_content_area(GTK_DIALOG(__struct_global.dialog_menu->dialog));
	
	//Insère dans la boîte de dialogue les champs de savegame_menu
	while (i<nb_champ_menu)
	{
		__struct_global.dialog_menu->button[i]=gtk_button_new_with_label(savegame_menu[i]);
		gtk_box_pack_start(GTK_BOX(__struct_global.dialog_menu->content_area), __struct_global.dialog_menu->button[i], FALSE, FALSE, 0);
		i++;
	}
	
	//Connecte à chaque bouton du menu une fonction spécifique
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[0]), "clicked", G_CALLBACK(slot1IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[1]), "clicked", G_CALLBACK(slot2IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[2]), "clicked", G_CALLBACK(slot3IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[3]), "clicked", G_CALLBACK(slot4IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[4]), "clicked", G_CALLBACK(slot5IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[5]), "clicked", G_CALLBACK(returnIsSelectedForDialog), highlight_index);
}

	/*Initialise la boîte de dialogue du menu loadgame.
	loadgame_menu = tableau de string ou char*, champs du menu loadgame.
	nb_champ_menu = nombre total de champ que le menu aura.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initLoadGameMenuDialog(char **loadgame_menu, const int nb_champ_menu, int *highlight_index)
{
	
	__struct_global.dialog_menu=malloc(sizeof(Dialog_menu));
	int i=0;
	
	loadgame_menu[0]=(char*) malloc(255);
	loadgame_menu[1]=(char*) malloc(255);
	loadgame_menu[2]=(char*) malloc(255);
	loadgame_menu[3]=(char*) malloc(255);
	loadgame_menu[4]=(char*) malloc(255);
	loadgame_menu[5]=(char*) malloc(255);
	
	//On initialise les champs du menu
	strcpy(loadgame_menu[0], "Slot 1");
	strcpy(loadgame_menu[1], "Slot 2");
	strcpy(loadgame_menu[2], "Slot 3");
	strcpy(loadgame_menu[3], "Slot 4");
	strcpy(loadgame_menu[4], "Slot 5");
	strcpy(loadgame_menu[5], "Return");
	
	//Crée une boîte de dialogue pour permettre à l'utiisateur de choisir sur quel slot il veut charger sa partie
	__struct_global.dialog_menu->dialog=gtk_dialog_new_with_buttons("Choisissez sur quel slot charger la partie", GTK_WINDOW(__struct_global.main_window), GTK_DIALOG_MODAL, NULL, NULL);
	__struct_global.dialog_menu->content_area=gtk_dialog_get_content_area(GTK_DIALOG(__struct_global.dialog_menu->dialog));
	
	//Insère dans la boîte de dialogue les champs de loadgame_menu
	while (i<nb_champ_menu)
	{
		__struct_global.dialog_menu->button[i]=gtk_button_new_with_label(loadgame_menu[i]);
		gtk_box_pack_start(GTK_BOX(__struct_global.dialog_menu->content_area), __struct_global.dialog_menu->button[i], FALSE, FALSE, 0);
		i++;
	}
	
	//Connecte à chaque bouton du menu une fonction spécifique
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[0]), "clicked", G_CALLBACK(slot1IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[1]), "clicked", G_CALLBACK(slot2IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[2]), "clicked", G_CALLBACK(slot3IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[3]), "clicked", G_CALLBACK(slot4IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[4]), "clicked", G_CALLBACK(slot5IsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.dialog_menu->button[5]), "clicked", G_CALLBACK(returnIsSelectedForDialog), highlight_index);

}

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 1 de sauvegarde*/
void slot1IsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=0;
	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 2 de sauvegarde*/
void slot2IsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=1;
	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 3 de sauvegarde*/
void slot3IsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=2;
	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 4 de sauvegarde*/
void slot4IsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=3;
	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 5 de sauvegarde*/
void slot5IsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=4;
	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur le bouton "Return" de la boîte de dialogue*/
void returnIsSelectedForDialog(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=5;
	
	(void)widget;
}

	/*Permet d'iniatiliser l'interface qui va afficher les éléments des dialogues du visual novel.
	text_color = int, couleur du texte des différents dialogues.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel ou "Entrée"), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. */
void initVNView(const int text_color, int *keyboard_input)
{
	__struct_global.vn_view=malloc(sizeof(Vn_view));
	char* color_name[6]={"white", "blue", "cyan", "red", "magenta", "yellow"};
	float height_of_paned_pack1=0.8*WINDOW_HEIGHT, height_of_paned_pack2=0.2*WINDOW_HEIGHT;
	gchar *markup_text=NULL;
	GdkPixbuf *pixbuf=NULL;
	GtkTextIter iter;
	
	//Crée l'overlay qui va contenir le background
	__struct_global.vn_view->overlay_container_for_background=gtk_overlay_new();
	
	//Récupère le background qui va être affiché par défaut et l'insère dans l'overlay qui doit le contenir
	__struct_global.vn_view->background=gtk_image_new_from_pixbuf(pixbuf);
	gtk_container_add(GTK_CONTAINER(__struct_global.vn_view->overlay_container_for_background), __struct_global.vn_view->background);
	
	//Crée le paned qui va permettre de bien positionner d'un côté la box qui afficher la profile_pic et le character_name et de l'autre le text_view
	__struct_global.vn_view->paned=gtk_paned_new(GTK_ORIENTATION_VERTICAL);
	gtk_paned_set_position(GTK_PANED(__struct_global.vn_view->paned), height_of_paned_pack1);
	
	//Crée l'overlay qui va servir de base à la partie haute du paned
	__struct_global.vn_view->overlay_container_for_box=gtk_overlay_new();
	gtk_widget_set_size_request(__struct_global.vn_view->overlay_container_for_box, -1, height_of_paned_pack1);
	
	//Crée la box qui va contenir la profile_pic et le character_name
	__struct_global.vn_view->box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_halign(__struct_global.vn_view->box, GTK_ALIGN_START);
	gtk_widget_set_valign(__struct_global.vn_view->box, GTK_ALIGN_END);
	
	//Récupère la profile_pic qui va être affiché par défaut
	__struct_global.vn_view->profile_pic=gtk_image_new_from_pixbuf(pixbuf);
	
	//Crée le bouton qui va servir à afficher le nom du personnage et y insère un nom par défaut
	__struct_global.vn_view->character_name=gtk_button_new();
	__struct_global.vn_view->character_name_label=gtk_label_new(NULL);
	gtk_widget_set_sensitive(__struct_global.vn_view->character_name, FALSE);
	markup_text=g_markup_printf_escaped(__struct_global.format_character_name, "Inconnu");
	gtk_label_set_markup(GTK_LABEL(__struct_global.vn_view->character_name_label), markup_text);
	g_free(markup_text), markup_text=NULL;
	gtk_container_add(GTK_CONTAINER(__struct_global.vn_view->character_name), __struct_global.vn_view->character_name_label);
	
	//Crée l'élément qui va servir à afficher le texte du dialogue et y insère du texte par défaut
	__struct_global.vn_view->text_view=gtk_text_view_new();
	gtk_widget_set_sensitive(__struct_global.vn_view->text_view, FALSE);
	__struct_global.vn_view->text_buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(__struct_global.vn_view->text_view));
	markup_text=g_markup_printf_escaped(__struct_global.format_text_color, color_name[text_color], "Rien");
	gtk_text_buffer_get_iter_at_line(__struct_global.vn_view->text_buffer, &iter, 0);
	gtk_text_buffer_insert_markup(__struct_global.vn_view->text_buffer, &iter, markup_text, -1);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(__struct_global.vn_view->text_view),GTK_WRAP_WORD);
	gtk_widget_set_size_request(__struct_global.vn_view->text_view, -1, height_of_paned_pack2);
	g_free(markup_text), markup_text=NULL;
	
	//Crée la button_box et les boutons qu'elle va contenir
	__struct_global.vn_view->button_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	__struct_global.vn_view->edit_button=gtk_button_new_from_icon_name("accessories-text-editor", GTK_ICON_SIZE_BUTTON);
	__struct_global.vn_view->add_image_button=gtk_button_new_from_icon_name("insert-image", GTK_ICON_SIZE_BUTTON);
	__struct_global.vn_view->save_button=gtk_button_new_from_icon_name("document-save", GTK_ICON_SIZE_BUTTON);
	gtk_widget_set_halign(__struct_global.vn_view->button_box, GTK_ALIGN_END);
	gtk_widget_set_valign(__struct_global.vn_view->button_box, GTK_ALIGN_END);
	
	//Insère l'interface dans la fenêtre principale
	gtk_box_pack_start(GTK_BOX(__struct_global.main_box), __struct_global.vn_view->overlay_container_for_background, TRUE, TRUE, 0);
	
	//Place au dessus de l'overlay qui contient le background le paned
	gtk_overlay_add_overlay(GTK_OVERLAY(__struct_global.vn_view->overlay_container_for_background), __struct_global.vn_view->paned);
	
	//Insère dans la partie haute et la partie basse du paned leur élément respectif 
	gtk_paned_pack1(GTK_PANED(__struct_global.vn_view->paned), __struct_global.vn_view->overlay_container_for_box, FALSE, FALSE);
	gtk_paned_pack2(GTK_PANED(__struct_global.vn_view->paned), __struct_global.vn_view->text_view, FALSE, FALSE);
	
	//Place au dessus de l'overlay de la première partie du paned la box qui va afficher la profile_pic et le character_name
	gtk_overlay_add_overlay(GTK_OVERLAY(__struct_global.vn_view->overlay_container_for_box), __struct_global.vn_view->box);
	
	//Insère dans la box la profile_pic et le character_name
	gtk_box_pack_start(GTK_BOX(__struct_global.vn_view->box), __struct_global.vn_view->profile_pic, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.vn_view->box), __struct_global.vn_view->character_name, FALSE, FALSE, 0);
	
	//Place au dessus de text_view la button_box
	gtk_overlay_add_overlay(GTK_OVERLAY(__struct_global.vn_view->overlay_container_for_background), __struct_global.vn_view->button_box);
	
	//Insère les boutons dans la button_box
	gtk_box_pack_start(GTK_BOX(__struct_global.vn_view->button_box), __struct_global.vn_view->edit_button, FALSE, FALSE , 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.vn_view->button_box), __struct_global.vn_view->add_image_button, FALSE, FALSE , 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.vn_view->button_box), __struct_global.vn_view->save_button, FALSE, FALSE , 0);
	
	//Connecte à chaque bouton du menu une fonction spécifique
	g_signal_connect(G_OBJECT(__struct_global.vn_view->edit_button), "clicked", G_CALLBACK(editButtonIsSelected), keyboard_input);
	g_signal_connect(G_OBJECT(__struct_global.vn_view->add_image_button), "clicked", G_CALLBACK(addImageButtonIsSelected), keyboard_input);
	g_signal_connect(G_OBJECT(__struct_global.vn_view->save_button), "clicked", G_CALLBACK(saveButtonIsSelected), keyboard_input);
	
	//Connecte des touches du clavier à la fenêtre pour activer certaines fonctions
	__struct_global.vn_view->accel_group=accel_group_new(keyboard_input);
	gtk_window_add_accel_group(GTK_WINDOW(__struct_global.main_window), __struct_global.vn_view->accel_group);
}

	/*Permet de signaler que l'utiisateur a appuyé sur le bouton "Edit"*/
void editButtonIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *keyboard_input=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*keyboard_input=KEY_D;
	
	(void)widget;
}

	/*Permet de signaler que l'utiisateur a appuyé sur le bouton "Addimage"*/
void addImageButtonIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *keyboard_input=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*keyboard_input=KEY_P;
	
	(void)widget;
}

	/*Permet de signaler que l'utiisateur a appuyé sur le bouton "Save"*/
void saveButtonIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *keyboard_input=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*keyboard_input=KEY_S;
	
	(void)widget;
}

	/*Permet de signaler que l'utiisateur a appuyé sur la touche gauche de son pavé directionnel*/
void leftKeyIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *keyboard_input=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*keyboard_input=KEY_LEFT;
	
	(void)widget;
}

	/*Permet de signaler que l'utiisateur a appuyé sur la touche droite de son pavé directionnel*/
void rightKeyIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *keyboard_input=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*keyboard_input=KEY_RIGHT;
	
	(void)widget;
}

	/*Permet de signaler que l'utiisateur a appuyé sur la touche "Q" de son clavier*/
void QKeyIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *keyboard_input=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*keyboard_input=KEY_Q;
	
	(void)widget;
}

	/*Permet de créer la liaison entre certaines touches du clavier et des fonctions*/
GtkAccelGroup *accel_group_new(gpointer user_data)
{
	GtkAccelGroup *accel_group=NULL;
	
	accel_group=gtk_accel_group_new();
	
	accelerator_new(accel_group, "D", G_CALLBACK(accelEdit), user_data);
	accelerator_new(accel_group, "P", G_CALLBACK(accelAddImage), user_data);
	accelerator_new(accel_group, "S", G_CALLBACK(accelSave), user_data);
	accelerator_new(accel_group, "Q", G_CALLBACK(accelQuit), user_data);
	accelerator_new(accel_group, "<Control>L", G_CALLBACK(accelBack), user_data);
	accelerator_new(accel_group, "<Control>R", G_CALLBACK(accelNext), user_data);
	
	return accel_group;
}

	/*Permet de créer une liaison entre une touche du clavier et une fonction*/
void accelerator_new(GtkAccelGroup *accel_group, const gchar *accelerator,  GCallback callback, gpointer user_data)
{
	guint key;
	GdkModifierType mods;
	GClosure *closure=NULL;
	
	gtk_accelerator_parse(accelerator, &key, &mods);
	closure=g_cclosure_new(callback, user_data, NULL);
	gtk_accel_group_connect(accel_group, key, mods, GTK_ACCEL_VISIBLE, closure);
}

	/*Permet d'activer la fonction "editButtonIsSelected"*/
gboolean accelEdit(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	editButtonIsSelected(NULL, user_data);
	
	(void)accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

	/*Permet d'activer la fonction "addImageButtonIsSelected"*/
gboolean accelAddImage(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	addImageButtonIsSelected(NULL, user_data);
	
	(void)accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

	/*Permet d'activer la fonction "saveButtonIsSelected"*/
gboolean accelSave(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	saveButtonIsSelected(NULL, user_data);
	
	(void)accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

	/*Permet d'activer la fonction "backKeyIsSelected"*/
gboolean accelBack(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	leftKeyIsSelected(NULL, user_data);
	
	(void)accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

	/*Permet d'activer la fonction "nextKeyIsSelected"*/
gboolean accelNext(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	rightKeyIsSelected(NULL, user_data);
	
	(void)accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}
	/*Permet d'activer la fonction "QKeyIsSelected"*/
gboolean accelQuit(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	QKeyIsSelected(NULL, user_data);
	
	(void)accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

	/*Affiche le menu des choix.
	choice_menu = tableau de char* ou string, champs du menu des choix.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.
	nb_choice = int, nombre de choix.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel ou "Entrée"), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur.*/
void displayChoiceMenu(char **choice_menu, int *highlight_index, const int nb_choice, int *keyboard_input)
{
	gchar* choice_str=NULL; 
	GtkWidget *choice_dialog=NULL, *content_area=NULL, *combo_box_text=NULL;
	int i=0;
	
	//Crée une boîte de dialogue pour permettre à l'utiisateur de faire un choix
	choice_dialog=gtk_dialog_new_with_buttons("Faites un choix", GTK_WINDOW(__struct_global.main_window), GTK_DIALOG_MODAL, "Return", GTK_RESPONSE_CANCEL, "Confirm", GTK_RESPONSE_ACCEPT, NULL);
	content_area=gtk_dialog_get_content_area(GTK_DIALOG(choice_dialog));
	combo_box_text=gtk_combo_box_text_new();
	
	while (i<nb_choice)
	{
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo_box_text), choice_menu[i]);
		i++;
	}
	gtk_container_add(GTK_CONTAINER(content_area), combo_box_text);

	g_signal_connect(G_OBJECT(combo_box_text), "changed", G_CALLBACK(choiceIsMade), &__struct_global.f_choice_is_made);
	
	//Affiche cette boîte de dialogue
	gtk_widget_show_all(choice_dialog);
	
	i=0;
	
	//Si l'utiisateur a appuyé sur le bouton "Confirm"
	if (gtk_dialog_run(GTK_DIALOG(choice_dialog))==GTK_RESPONSE_ACCEPT)
	{
		if (__struct_global.f_choice_is_made==TRUE)
		{
			choice_str=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box_text));
			while (strcmp(choice_menu[i], choice_str)!=0  && i<nb_choice)
			{
				i++;
			}
			*highlight_index=i;
		}
		else
		{
			leftKeyIsSelected(NULL, keyboard_input);
		}
	}
	else
	{
		leftKeyIsSelected(NULL, keyboard_input);
	}
	
	gtk_widget_destroy(choice_dialog);
}

	/*Permet de signaler que l'utiisateur a fait un choix*/
void choiceIsMade(GtkWidget *widget, gpointer user_data)
{
	gboolean *f_choice_is_made=(gboolean*)user_data;
	
	*f_choice_is_made=TRUE;
	
	(void)widget;
}
