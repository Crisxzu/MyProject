#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h> 
#include "playVNView.h"

void displayDia(char** next_prev_dia, char *vn_folder_name, Dialogue *dia, const int highlight_index, const int text_color, const int nb_champ_menu, const int endofVN, const float text_speed)
{
	/*Affiche le contenu d'un fichier dia( plus concrètement le décor, la photo de profil du personnage qui s'exprime en ce moment même, le nom du personnage et le texte du dialogue en lui-même) et les champs "Previous" et "Next".
	next_prev_dia = Tableau de char* ou string, champs "Previous" et "Next".
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.
	dia = variable de la structure "Dialogue", données d'un fichier dia 
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).
	nb_champ_menu = int, nombre total de champs du menu.
	endofVN = int marquant la fin du Visual Novel.
	text_speed = float, vitesse de défilement du texte du dialogue. P.S= Pour text_speed=1, un caractère est affiché toutes les 50ms, le calcul se fait comme suit: temps pour l'affichage d'un caractère= 50ms/valeur de text_speed.*/	
	int i_champ=0, i_char=0, can_print_next_char=FALSE;
	clock_t oldtime, current_time;
	
	if (endofVN==FALSE)//Si l'utiisateur ne se trouve pas à la fin du Visual Novel, un décor, l'image du personnage, le nom du personnage et le texte du dialogue seront affichés
	{
		attron(COLOR_PAIR(text_color));
		printw("=== %s ===\n", vn_folder_name);
		printw("%s", dia->background);
		printw("=====================================\n");
		printw("%s", dia->profile_picture);
		printw("=====================================\n");
		printw("== %s ==\n", dia->character_name);
		
		do
		{
			
			can_print_next_char=FALSE;

			addch(dia->dia_text[i_char]);
			i_char++;
			oldtime=clock();
			while (can_print_next_char==FALSE)//Tant que le temps pour l'affichage d'un caractère n'est pas passé, on ne passe pas à l'affichage du prochain caractère
			{
				current_time=clock()-oldtime;
				if (current_time>=(50000/text_speed))//Si le temps pour l'affichage d'un caractère s'est écoulé(50000=50ms) alors on peut passer à l'affichage du prochain caractère.
				{
					can_print_next_char=TRUE;
				}
			}
			refresh();
		} while (dia->dia_text[i_char]!='\0');//Le texte du dialogue est affiché caractère par caractère, suivant la vitesse de défilement
		
		printw("\n=====================================\n");
		attroff(COLOR_PAIR(text_color));
		
		for (i_champ = 0; i_champ < nb_champ_menu; i_champ++) //Affichage de chaque champ du menu en les affichant un par un
		{
			if (i_champ==highlight_index)//Si le champ affiché est aussi celui qui est selectionné actuellement par l'utilisateur, il sera affichée vert
			{
				attron(COLOR_PAIR(6));
				printw("%s", next_prev_dia[i_champ]);
				attroff(COLOR_PAIR(6));
			}
			else //Sinon, il est simplement affiché avec la couleur de texte choisie dans les paramètres
			{
				attron(COLOR_PAIR(text_color));
				printw("%s", next_prev_dia[i_champ]);
				attroff(COLOR_PAIR(text_color));
			}
			if (i_champ+1<nb_champ_menu)//Pour qu'il y ait un certain espace entre chaque champ(ceux-ci sont sur la même ligne) et ne laisser un espace que s'il reste encore un champ à afficher(si i_champ+1 est égale ou supérieure nb_champ_menu cela signifie qu'on a déjà affiché tous les champs du menu)
			{
				printw("			");
			}
		}
	}
	else////Si l'utiisateur se trouve à la fin du Visual Novel, "THE END" sera affiché marquant la fin du Visual Novel que l'utilisateur est en train de jouer
	{
		attron(COLOR_PAIR(text_color));
		printw("=== %s ===\n", vn_folder_name);
		printw("%s\n", dia->dia_text);
		attroff(COLOR_PAIR(text_color));
		
		for (i_champ = 0; i_champ < nb_champ_menu; i_champ++) //On affiche chaque champ du menu en les affichant un par un jusqu'à les avoir tous affiché
		{
			if (i_champ==highlight_index) //Si le champ affiché est aussi celui qui est selectionné actuellement par l'utilisateur, il sera affichée vert
			{
				attron(COLOR_PAIR(6));
				printw("%s", next_prev_dia[i_champ]);
				attroff(COLOR_PAIR(6));
			}
			else //Sinon, il est simplement affiché avec la couleur de texte choisie dans les paramètres
			{
				attron(COLOR_PAIR(text_color));
				printw("%s", next_prev_dia[i_champ]);
				attroff(COLOR_PAIR(text_color));
			}
			if (i_champ+1<nb_champ_menu)//S'il reste encore un champ à afficher(si i_champ+1 est égale ou supérieure nb_champ_menu cela signifie qu'on a déjà affiché tous les champs du menu), un certain espace va être insérer entre chaque champ(ceux-ci sont sur la même ligne)
			{
				printw("			");
			}
		}
	}
	
	attron(COLOR_PAIR(text_color));
	printw("\n=====================================\n");
	attroff(COLOR_PAIR(text_color));
	
	attron(COLOR_PAIR(6));
	printw("[Q] Revenir au menu principal\n[D] Editer le dialogue en cours\n[P] Créer une nouvelle photo de profil\n[B] Créer un nouveau décor\n[S] Sauvegarder sa partie sur une slot\n");
	attroff(COLOR_PAIR(6));
	
	attron(COLOR_PAIR(text_color));
	printw("=====================================\n");
	attroff(COLOR_PAIR(text_color));
	 
}

void displayMenuForPlayVN(char** Menu, const int highlight_index, const int text_color, const int nb_champ_menu, char* vn_folder_name)
{
	/*Affiche les différents champs du menu qui est entré en paramètres.
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	Menu = tableau(de string ou char*), champs du menu.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).
	nb_champ_menu = int, nombre total de champs du menu.
	vn_folder_name = string ou char*, nom du Visual Novel.*/	
	int i_champ=0;
	
	attron(COLOR_PAIR(text_color));
   printw("== %s ==\n", vn_folder_name);
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

void waitInputDia(int *highlight_index, int *keyboard_input, const int nb_champ_menu, Dialogue *dia, const int endofVN)
{
	/*Permet à l'utilisateur de passer d'un dialogue à un autre via le pavé directionnel(précisément les touches "GAUCHE" et "DROITE", les touches "HAUT" et "BAS" serviront dans le cas où le dialogue affiché est trop grand pour la fenêtre ainsi l'utilisateur pourra voir le reste du texte qui se trouve en bas ou celui qui se trouve en haut).
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. 
	nb_champ_menu = int, nombre total de champs du menu.
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	endofVN = int marquant la fin du Visual Novel.*/
   curs_set(0);
   noecho(); 
   keypad(stdscr, TRUE);
	*keyboard_input=getch();
	if (*keyboard_input==KEY_LEFT)//Si l'utilisateur appuie sur "GAUCHE", il passera au dialogue précédent
	{
		*highlight_index=0;
		dia->length_currentRoute=dia->length_currentRoute-1;
		if (dia->length_currentRoute<0)//Si l'utilisateur décide de passer au dialogue précédent alors que le dialogue qui est affiché est déjà le premier dialogue alors il n'y aura aucun changement sur la taille de la route
		{
			dia->length_currentRoute=0;
		}
		if (dia->i_currentBranch>0)//La valeur de i_currentBranch n'est diminué que si celle-ci est supérieure à 0(valeur minimale)
		{
			dia->i_currentBranch=dia->i_currentBranch-1;
		}
	}	
	else if (*keyboard_input==KEY_RIGHT)//Si l'utilisateur appuie sur "DROITE", il passera au dialogue suivant.
	{
		*highlight_index=1;
		if (endofVN!=TRUE)//Si l'utilisateur ne se trouve pas déjà à la fin du Visual Novel alors en faisant "DROITE", la taille de route va augmenter pour passer au dialogue suivant. Sinon, elle restera inchangé
		{
			dia->length_currentRoute=dia->length_currentRoute+1;
		}
		if (dia->i_currentBranch>=0)//La valeur de i_currentBranch  n'est augmenté que si celle-ci est supérieure ou égale 0(valeur minimale)
		{
			dia->i_currentBranch=dia->i_currentBranch+1;
		}
	}
	else if (*keyboard_input==KEY_UP)//Si l'utilisateur appuie sur "HAUT", il pourra voir la partie du dialogue qui se trouve en haut et qui n'est pas affiché dans la fenêtre
	{	
		scrollok(stdscr, FALSE);
	}
	else if (*keyboard_input==KEY_DOWN)//Si l'utilisateur appuie sur "BAS", il pourra voir la partie du dialogue qui se trouve en bas et qui n'est pas affiché dans la fenêtre
	{
		scrollok(stdscr, TRUE);
	}
	keypad(stdscr, FALSE);
}

void waitInputMenuForPlayVN(int *highlight_index, int *keyboard_input, const int nb_champ_menu)
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
	keypad(stdscr, FALSE);
}

void createBackground(char *vn_folder_name, const int text_color)
{
	/*Permet à l'utilisateur de créer un nouveau fichier qui va servir de décor pour un dialogue(un fichier "background").
	vn_folder_name = string ou char*, nom du Visual Novel.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).*/
	FILE *new_background_file=NULL;
	char* directory_new_background_file=(char*) malloc(255); char* background_file_name=(char*) malloc(255); char* system_command_name=malloc(255);
	
	attron(COLOR_PAIR(text_color));
	printw("== Entrez le nom que vous souhaitez attribuer à ce nouveau décor ==\n");
	curs_set(1);
	echo();
	getstr(background_file_name);
	attroff(COLOR_PAIR(text_color));
	
	sprintf(directory_new_background_file, "VN/%s/img/%s.bac", vn_folder_name, background_file_name);
	new_background_file=fopen(directory_new_background_file, "w");
	
	sprintf(system_command_name, "gedit %s", directory_new_background_file);
	system(system_command_name);
	
	fclose(new_background_file), new_background_file=NULL;
	free(system_command_name), system_command_name=NULL;
	free(directory_new_background_file), directory_new_background_file=NULL;
	free(background_file_name), background_file_name=NULL;
}

void createProfilePicture(char *vn_folder_name, const int text_color)
{
	/*Permet à l'utilisateur de créer un nouveau fichier qui va servir de photo de profil pour un dialogue(un fichier "pp").
	vn_folder_name = string ou char*, nom du Visual Novel.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).*/
	FILE *new_profile_picture_file=NULL;
	char* directory_new_profile_picture_file=(char*) malloc(255); char* profile_picture_file_name=(char*) malloc(255); char* system_command_name=malloc(255);
	
	attron(COLOR_PAIR(text_color));
	printw("== Entrez le nom que vous souhaitez attribuer à cette nouveau photo de profil ==\n");
	curs_set(1);
	echo();
	getstr(profile_picture_file_name);
	attroff(COLOR_PAIR(text_color));
	
	sprintf(directory_new_profile_picture_file, "VN/%s/img/%s.pp", vn_folder_name, profile_picture_file_name);
	new_profile_picture_file=fopen(directory_new_profile_picture_file, "w");
	
	sprintf(system_command_name, "gedit %s", directory_new_profile_picture_file);
	system(system_command_name);
	
	fclose(new_profile_picture_file), new_profile_picture_file=NULL;
	free(system_command_name), system_command_name=NULL;
	free(directory_new_profile_picture_file), directory_new_profile_picture_file=NULL;
	free(profile_picture_file_name), profile_picture_file_name=NULL;
}

void editDia(char *vn_folder_name, const int length_currentRoute, char** currentRoute, const int i_currentBranch)
{
	/*Permet à l'utilisateur d'éditer un dialogue et d'accesoirement de créer un nouveau dialogue.
	vn_folder_name = string ou char*, nom du Visual Novel.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
	FILE *dia_file=NULL;
	char* system_command_name=(char*) malloc(255); char* dia_file_name=(char*) malloc(255);
	
	sprintf(dia_file_name, "VN/%s/%s.dia", vn_folder_name, currentRoute[length_currentRoute]);
	dia_file=fopen(dia_file_name, "r");
	if (dia_file!=NULL)//Si le fichier "dia" à éditer existe
	{
		sprintf(system_command_name, "gedit %s", dia_file_name);
		system(system_command_name);
	}
	else//Si le fichier "dia" à éditer n'existe pas, il va être créer
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

void setDefaultDataInFile(FILE *dia_file, char** currentRoute, const int length_currentRoute, const int i_currentBranch)
{
	/*Permet d'insérer dans le nouveau fichier "dia" des données par défaut(Pas de choix, le nom du fichier qui devrait potentiellement le suivre, un emplacement pour insérer le nom du décor, de la photo de profil et du nom du personnage et un emplacement pour insérer un dialogue).
	dia_file = variable FILE, fichier dia.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
	int length_dia_file_name=0, i_char=0, j_char=0; 
	char* next_dia_file_name=(char*) malloc(255);
	
	length_dia_file_name=(unsigned)strlen(currentRoute[length_currentRoute]);
	i_char=length_dia_file_name-2;
	if (length_dia_file_name==4)//Si le nom du fichier "dia" qui va permettre de mettre au point le nom du prochain fichier suit un format XXXX, la fonction prendra la valeur d'i_currentBranch et l'augmentera de 1 pour avoir le nom du prochain fichier et aussi le nouvel index de fichier
	{
		sprintf(next_dia_file_name, "%04d", i_currentBranch+1);
	}
	else if(length_dia_file_name>4)//Si le nom du fichier "dia" qui va permettre de mettre au point le nom du prochain fichier suit un autre format, la fonction prendra la valeur d'i_currentBranch et l'augmentera de 1 pour avoir le nouvel index qu'il va attribuer au nom du fichier "dia" pour avoir le nom du prochain fichier
	{
		char *i_currentBranch_str=(char*) malloc(5);
		
		sprintf(i_currentBranch_str, "%02d", i_currentBranch+1);
		strcpy(next_dia_file_name, currentRoute[length_currentRoute]);
		while (next_dia_file_name[i_char]!='\0')//Attribution du nouvel index au nom du prochain fichier "dia" caractère par caractère jusqu'à ce tous les caractères soient insérés
		{
			next_dia_file_name[i_char]=i_currentBranch_str[j_char];
			j_char++; i_char++;	
		}
		free(i_currentBranch_str), i_currentBranch_str=NULL;
	}
	fprintf(dia_file, "choice= 0 (goto) %s\nbackground= Insérer le nom d'un fichier bac\nprofilepicture= Insérer le nom d'un fichier pp\ncharactername= Insérer le nom du personnage\ndialogue= Ecrire le dialogue ici\n\nFormat par défaut, veuillez modifier en fonction de vos besoins.(ce texte est à effacer)\n", next_dia_file_name);
	free(next_dia_file_name), next_dia_file_name=NULL;
}
