#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <curses.h>
#include "playVNModel.h"

void getChoice(FILE *dia_file, char** choice_menu, int *nb_choice, char** user_actions, int *nb_actions, const int keyboard_input, int *choice_is_detected)
{
	/*Permet de récuperer les choix présents dans le fichier dia.
	dia_file = variable FILE, fichier dia
	choice_menu = tableau de char* ou string, champs du menu des choix.
	nb_choice = int, nombre de choix.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.
	keyboard_input = int, touche qui a été appuyée par l'utiisateur suivant son pavé directionnel.
	choice_is_detected = int, boolean pour savoir si des choix ont été détectés dans un fichier dia.*/
	int i_choice=0; 
	char* string_to_check=(char*) malloc(255);

	fscanf(dia_file, "%*s %d", nb_choice);
	if (*nb_choice>=2)//Si en explorant le fichier "dia", des choix ont été détectés alors les différents champs du menu choice_menu vont être iniatilisés avec le texte des différents choix
	{
		*choice_is_detected=TRUE;
		if (keyboard_input==KEY_LEFT)//Si l'utiisateur se trouve dans le cas où il effectue un retour en arrière et que le dialogue à afficher comporte des choix à faire, on se trouve alors dans un cas où l'utilisateur revient sur un choix qu'il a déjà fait par conséquent, sa dernière action sera supprimé du tableau user_actions
		{
			free(user_actions[*nb_actions-1]), user_actions[*nb_actions-1]=NULL;
			*nb_actions=*nb_actions-1;
		}
		while (i_choice<*nb_choice)//Le texte de chaque choix sera enregistré un à un dans chaque champ de choice_menu
		{
			choice_menu[i_choice]=(char*) malloc(255);
			
			fscanf(dia_file, "%*s %[^$]s", choice_menu[i_choice]);
			fscanf(dia_file,"%*s %s", string_to_check);
			if (strcmp(string_to_check, "(if")==0)//Si après avoir enregistré le texte d'un choix, la fonction détecte la présence de conditions particulières attribuées à ce choix, elle les passera pour passer au prochain choix
			{
				int nb_string_to_pass=0, i=0;
				
				fscanf(dia_file, "%d ", &nb_string_to_pass);
				while (i<nb_string_to_pass)//Elle passe le texte de chaque conditions
				{
					fscanf(dia_file, "%*[^$]s");
					fscanf(dia_file, "%*s");
					i++;
				}
				fscanf(dia_file, "%*s %*s %*s %*s");
			}
			fscanf(dia_file, "%*s");
			i_choice++;
		}
	}
	else//Si en explorant le fichier "dia", des choix n'ont pas été détectés alors les différents champs du menu choice_menu ne vont pas être iniatilisés et la fonction va directement passé à la prochaine partie du fichier pour récupérer le décor, la photo du personnage, le nom du personnage et le texte du dialogue
	{
		fscanf(dia_file,"%s", string_to_check);
		if (strcmp(string_to_check, "(if")==0)//Si en passant à la prochaine du partie du fichier, la fonction détecte la présence de conditions particulières attribuées pour le choix du prochain fichier "dia" à consulter, elle va les passer
		{
			int nb_string_to_pass=0, i=0;
			
			fscanf(dia_file, "%d ", &nb_string_to_pass);
			while (i<nb_string_to_pass)//Elle passe le texte de chaque conditions
			{
				fscanf(dia_file, "%*[^$]s");
				fscanf(dia_file, "%*s");
				i++;
			}
			fscanf(dia_file, "%*s %*s %*s %*s");
		}
		fscanf(dia_file, "%*s");
	}
	
	free(string_to_check), string_to_check=NULL;
}

	/*Permet d'obtenir le nom du fichier dia dans le cas où l'utiisateur au cours du dialogue précedent n'a pas eu à faire un choix en allant tout d'abord chercher le nom du fichier.
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	flag_is_allocated = tableau de int dont la valeur de certains cases va être initialisé en TRUE ou FALSE en fonction de si une case du tableau currentRoute a reçu un malloc ou non.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.*/
FILE *openDiaFileIfNoChoice(Dialogue *dia, char** currentRoute, int *flag_is_allocated, char** user_actions, const int nb_actions, char *vn_folder_name)
{
	FILE *dia_file=NULL;
	char* dia_file_directory=(char*) malloc(255); char* string_to_check=(char*) malloc(255);
	
	//Dans le cas où l'utilisateur revient en arrière, la fonction va juste récuperer le nom du fichier "dia" qui se trouve déjà dans le tableau currentRoute (Concretement si pour ce champ du tableau, de la mémoire RAM a été attribué, cela signifie qu'on se trouve dans un cas où l'utiisateur revient sur ces pas)
	if (flag_is_allocated[dia->length_currentRoute]==TRUE)
		{
			sprintf(dia_file_directory, "VN/%s/%s.dia", vn_folder_name, currentRoute[dia->length_currentRoute]);
			dia_file=fopen(dia_file_directory, "r");		
		}
		
	//Pour ce champ du tableau currentRoute, de la mémoire RAM n'a pas été attribuée, on se trouve dans un cas où l'utilisateur avance dans l'histoire, il faut donc aller chercher le nom de fichier "dia" et l'enregistrer dans le tableau
	else
		{
			currentRoute[dia->length_currentRoute]=(char*) malloc(255);
			
			flag_is_allocated[dia->length_currentRoute]=TRUE;
			if (dia->length_currentRoute==0)//Si l'utiisateur se trouve au début du Visual Novel, le nom du fichier est arbitrairement 0000.dia et la fonction n'ira pas chercher le nom du fichier dans le fichier "dia" précedent
			{
				sprintf(currentRoute[dia->length_currentRoute], "%04d", dia->length_currentRoute);
				sprintf(dia_file_directory, "VN/%s/%s.dia", vn_folder_name, currentRoute[dia->length_currentRoute]);
				dia_file=fopen(dia_file_directory, "r");
			}
			else if(dia->length_currentRoute>0)//Si l'utiisateur ne trouve pas au début du Visual Novel, alors la fonction ira chercher le nom du fichier dans le fichier "dia" précedent
			{
				FILE *previous_dia_file=NULL;
				
				sprintf(dia_file_directory, "VN/%s/%s.dia", vn_folder_name, currentRoute[dia->length_currentRoute-1]);
				previous_dia_file=fopen(dia_file_directory, "r");
				
				fscanf(previous_dia_file,"%*s %*s %s", string_to_check);
				if (strcmp(string_to_check, "(if")==0)//Si la fonction détecte la présence de conditions particulières, elle va les analyser
				{
					int requirement_is_ok=0;
					
					requirement_is_ok=checkUserActions(previous_dia_file, user_actions, nb_actions);
					if (requirement_is_ok==TRUE)//Si toutes les conditions ont été respectés par l'utilisateur, le nom du fichier "dia" à récupérer sera celui du cas où les conditions ont été respectés
					{
						fscanf(previous_dia_file, "%*s %s %*s %*s %*s", currentRoute[dia->length_currentRoute]);
					}
					else//Si toutes les conditions n'ont pas été respectés par l'utiisateur, le nom du fichier "dia" à récupérer sera celui du cas où les conditions n'ont pas été respectés
					{
						fscanf(previous_dia_file, "%*s %*s %*s %*s %s", currentRoute[dia->length_currentRoute]);
					}
				}
				else//Si la fonction n'a pas détecté de conditions particulières, elle va récuperer le nom du fichier "dia" du dialogue à intialiser sans faire une analyse des conditions
				{
					fscanf(previous_dia_file, "%s", currentRoute[dia->length_currentRoute]);
				}
				
				sprintf(dia_file_directory, "VN/%s/%s.dia", vn_folder_name, currentRoute[dia->length_currentRoute]);
				dia_file=fopen(dia_file_directory, "r");
				fclose(previous_dia_file), previous_dia_file=NULL;
			}
		}
		free(dia_file_directory), dia_file_directory=NULL;
		free(string_to_check), string_to_check=NULL;
		return dia_file;
}

	/*Permet de modifier la valeur de i_currentBranch en fonction de la taille du nom du fichier dia.
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
void setIndexCurrentBranch(Dialogue *dia, char** currentRoute)
{
	int length_dia_file_name=(unsigned)strlen(currentRoute[dia->length_currentRoute]);
	
	if (length_dia_file_name==4)//Si le nom du fichier "dia" suit un format XXXX, l'index de la branche sera celle du nom du fichier "dia"
	{
		sscanf(currentRoute[dia->length_currentRoute], "%d", &dia->i_currentBranch);
	}
	else//Si le nom du fichier "dia" suit un autre format, l'index de la branche sera celui de l'index qui se trouve au bout du nom du fichier
	{
		char* end_of_dia_file_name=(char*) malloc(5);
		
		sprintf(end_of_dia_file_name, "%c%c", currentRoute[dia->length_currentRoute][length_dia_file_name-2], currentRoute[dia->length_currentRoute][length_dia_file_name-1]);
		sscanf(end_of_dia_file_name, "%d", &dia->i_currentBranch);
		
		free(end_of_dia_file_name), end_of_dia_file_name=NULL;
	}
}

	/*Permet d'ouvrir le fichier dia dans le cas où l'utiisateur a eu au cours du dialogue précedent à faire un choix en allant tout d'abord chercher le nom du fichier.
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	choice_is_detected = int, boolean pour savoir si des choix ont été détectés dans un fichier dia.
	nb_choice = int, nombre de choix.
	highlight_choice = int, index du choix fait par l'utiisateur.
	flag_is_allocated = tableau de int dont la valeur de certains cases va être initialisé en TRUE ou FALSE en fonction de si une case du tableau currentRoute a reçu un malloc ou non.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.*/
FILE *openDiaFileIfChoice(Dialogue *dia, char** currentRoute, int *choice_is_detected, const int nb_choice, const int highlight_choice, int *flag_is_allocated, char** user_actions, const int nb_actions, char *vn_folder_name)
{
	FILE *previous_dia_file=NULL, *dia_file=NULL;
	int i_choice=0;
	char* dia_file_directory=(char*) malloc(255); char* string_to_check=(char*) malloc(255); currentRoute[dia->length_currentRoute]=(char*) malloc(255);
	
	flag_is_allocated[dia->length_currentRoute]=TRUE;
			
	sprintf(dia_file_directory, "VN/%s/%s.dia", vn_folder_name, currentRoute[dia->length_currentRoute-1]);
	previous_dia_file=fopen(dia_file_directory, "r");		
	fscanf(previous_dia_file, "%*s %*s");
	while (i_choice!=highlight_choice && i_choice<nb_choice)//Au cours de l'exploration du fichier "dia" du dialogue précédent, la fonction va passer différentes parties du fichier "dia" jusqu'à atteindre celle correspondant au choix fait par l'utilisateur
	{
		fscanf(previous_dia_file, "%*s %*[^$]s");
		fscanf(previous_dia_file,"%*s %s", string_to_check);
		if (strcmp(string_to_check, "(if")==0)//Si en passant le texte d'un choix, la fonction détecte la présence de conditions particulières attribuées à ce choix, elle va les passer aussi
		{
			int nb_string_to_pass=0, i=0;
			
			fscanf(previous_dia_file, "%d ", &nb_string_to_pass);
			while (i<nb_string_to_pass)//Elle passe le texte de chaque conditions jusqu'à les avoir toutes passés
			{
				fscanf(previous_dia_file, "%*[^$]s");
				fscanf(previous_dia_file, "%*s");
				i++;
			}
			fscanf(previous_dia_file, "%*s %*s %*s %*s");
		}
		fscanf(previous_dia_file, "%*s");
		i_choice++;
	}
	
	fscanf(previous_dia_file, "%*s %*[^$]s");
	fscanf(previous_dia_file,"%*s %s", string_to_check);
	if (strcmp(string_to_check, "(if")==0)//Une fois arrivé à la partie du chier "dia" correspondant à celle du choix de l'utiisateur, si la fonction détecte la présence de conditions particulières, elle va les analyser
	{
		int requirement_is_ok=0;
		
		requirement_is_ok=checkUserActions(previous_dia_file, user_actions, nb_actions);
		if (requirement_is_ok==TRUE)//Si toutes les conditions ont été respectés par l'utilisateur, le nom du fichier "dia" à récupérer sera celui du cas où les conditions ont été respectés
		{
			fscanf(previous_dia_file, "%*s %s %*s %*s %*s", currentRoute[dia->length_currentRoute]);
		}
		else//Si toutes les conditions n'ont pas été respectés par l'utiisateur, le nom du fichier "dia" à récupérer sera celui du cas où les conditions n'ont pas été respectés
		{
			fscanf(previous_dia_file, "%*s %*s %*s %*s %s", currentRoute[dia->length_currentRoute]);
		}
	}
	else//Si la fonction n'a pas détecté de conditions particulières, elle va récuperer le nom du fichier "dia" du dialogue à intialiser pour ce choix de l'utiisateur sans faire une analyse des conditions	
	{
		fscanf(previous_dia_file, "%s", currentRoute[dia->length_currentRoute]);
	}
	
	sprintf(dia_file_directory, "VN/%s/%s.dia", vn_folder_name, currentRoute[dia->length_currentRoute]);
	dia_file=fopen(dia_file_directory, "r");
	
	*choice_is_detected=FALSE;
	
	setIndexCurrentBranch(dia, currentRoute);
	
	fclose(previous_dia_file), previous_dia_file=NULL;
	free(dia_file_directory), dia_file_directory=NULL;
	free(string_to_check), string_to_check=NULL;
	return dia_file;
}

	/*Permet d'ouvrir le fichier "dia".
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	choice_is_detected = int, boolean pour savoir si des choix ont été détectés dans un fichier dia.
	nb_choice = int, nombre de choix.
	highlight_choice = int, index du choix fait par l'utiisateur.
	flag_is_allocated = tableau de int dont la valeur de certains cases va être initialisé en TRUE ou FALSE en fonction de si une case du tableau currentRoute a reçu un malloc ou non.
	keyboard_input = int, touche qui a été appuyée par l'utiisateur suivant son pavé directionnel.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.*/
FILE *openDiaFile(Dialogue *dia, char** currentRoute, int *choice_is_detected, const int nb_choice, const int highlight_choice, int *flag_is_allocated, const int keyboard_input, char** user_actions, const int nb_actions, char *vn_folder_name)
{
	FILE *dia_file=NULL;
	
	if (*choice_is_detected==TRUE && keyboard_input==KEY_LEFT)//Si des choix ont été détectés pour un dialogue et que l'utiisateur a préféré revenir en arrière(au dialogue qui le précède) et donc n'a pas fait de choix
	{
		*choice_is_detected=FALSE;
	}
	
	if (*choice_is_detected==TRUE)//Si au cours du dialogue précédent l'utiisateur a eu à faire un choix, la fonction va chercher le nom du fichier "dia" du dialogue à iniatiliser en fonction du choix de l'utiisateur et l'ouvrir
	{
		dia_file=openDiaFileIfChoice(dia, currentRoute, choice_is_detected, nb_choice, highlight_choice, flag_is_allocated, user_actions, nb_actions, vn_folder_name);
	}
	else//Si au cours du dialogue précédent, l'utilisateur n'a pas fait de choix, la fonction va aller chercher dans le fichier "dia" précedent le nom du fichier "dia" pour iniatiliser le dialogue(sans se soucier d'un choix de l'utilisateur) et l'ouvrir
	{
		dia_file=openDiaFileIfNoChoice(dia, currentRoute, flag_is_allocated, user_actions, nb_actions, vn_folder_name);
	}
	
	if (flag_is_allocated[dia->length_currentRoute+1]==TRUE)//Si de la mémoire RAM a été attribuée au dialogue qui vient juste après celui qui a été ouvert, alors celle-ci va être libérée(Dans ce cas précis, l'utiisateur a fait un retour arrière et en le faisant il perd aussi une partie de sa progression)
	{
		free(currentRoute[dia->length_currentRoute+1]), currentRoute[dia->length_currentRoute+1]=NULL;
		flag_is_allocated[dia->length_currentRoute+1]=FALSE;
	}
	return dia_file;
}

void loadDia(char *vn_folder_name, Dialogue *dia, char** currentRoute, int *endofVN, int *choice_is_detected, char** choice_menu, int *nb_choice, const int highlight_choice, int *flag_is_allocated, char** user_actions, int *nb_actions, const int keyboard_input)
{
	/*Permet de charger un dialogue, en allant tout d'abord ouvrir le fichier "dia" pour récupérer ensuite les différents éléments nécessaires(les différents choix, le décor, la photo de profil du personnage qui s'exprime, le nom du personnage, le texte du dialogue).
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.
	dia = variable de la structure "Dialogue", données d'un fichier dia et celle sur la partie du joueur.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	endofVN = int marquant la fin du Visual Novel, sa valeur sera modifiée en TRUE si le fichier dia qu'on cherche n'existe pas.
	choice_is_detected = int, boolean pour savoir si des choix ont été détectés dans un fichier dia.
	choice_menu = tableau de char* ou string, champs du menu des choix.
	nb_choice = int, nombre de choix.
	highlight_choice = int, index du choix fait par l'utiisateur.
	flag_is_allocated = tableau de int dont la valeur de certains cases va être initialisé en TRUE ou FALSE en fonction de si une case du tableau currentRoute a reçu un malloc ou non.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.
	keyboard_input = int, touche qui a été appuyée par l'utiisateur suivant son pavé directionnel.*/
	
	FILE *dia_file=NULL, *background_file=NULL, *profile_picture_file=NULL;
	char* file_directory=(char*) malloc(255); char* file_name=(char*) malloc(255);
	*endofVN=FALSE;
	
	dia_file=openDiaFile(dia, currentRoute, choice_is_detected, *nb_choice, highlight_choice, flag_is_allocated, keyboard_input, user_actions, *nb_actions, vn_folder_name);

	if (dia_file!=NULL && dia->length_currentRoute<=9999)//Si le fichier "dia" qu'il faut utiliser pour iniatiliser le dialogue existe et que la limite maximale du nombre de dialogue n'est pas dépassé(9999), la fonction va récupérer le décor, la photo du personnage, le nom du personnage et le texte du dialogue
	{
		getChoice(dia_file, choice_menu, nb_choice, user_actions, nb_actions, keyboard_input, choice_is_detected);
		fscanf(dia_file, "%*s %s", file_name);
		sprintf(file_directory, "VN/%s/img/%s", vn_folder_name, file_name);
		background_file=fopen(file_directory, "r");
		fgets(dia->background, 999, background_file);
		fclose(background_file), background_file=NULL;

		fscanf(dia_file, "%*s %s", file_name);
		sprintf(file_directory, "VN/%s/img/%s", vn_folder_name, file_name);
		profile_picture_file=fopen(file_directory, "r");
		fgets(dia->profile_picture, 999, profile_picture_file);
		fclose(profile_picture_file), profile_picture_file=NULL;

		fscanf(dia_file, "%*s %s", dia->character_name);

		fscanf(dia_file, "%*s %[^\n]s", dia->dia_text);
		fclose(dia_file), dia_file=NULL;

	}
	else if(dia_file==NULL || dia->length_currentRoute>9999)//Si le fichier "dia" qu'il faut utiliser pour iniatiliser le dialogue n'existe pas ou si la limite maximale de nombre de dialogue est dépassé(9999), cela signifie que l'utilisateur est arrivé au bout du Visual Novel qu'il est en train de jouer par conséquent la phrase "THE END" sera affiché.
	{
		
		background_file=NULL;
		profile_picture_file=NULL;
		strcpy(dia->dia_text, "THE END");
		*endofVN=TRUE;
	}
	free(file_directory), file_directory=NULL;
	free(file_name), file_name=NULL;
}

void intNextPrevDia(char** next_prev_dia)
{
	/*Permet d'iniatiliser les champs "Previous" et "Next" qui servent respectivement à revenir au dialogue précédent et à pour passer au dialogue suivant.
	next_prev_dia = Tableau de char* ou string, champs "Previous" et "Next".*/
	
	next_prev_dia[0]=(char*) malloc(255);
	next_prev_dia[1]=(char*) malloc(255);
	
	strcpy(next_prev_dia[0], "Previous");
	strcpy(next_prev_dia[1], "Next");
}

void intMenuInGame(char** menu_ingame)
{
	/*Permet d'iniatiliser des champs du menu ingame, les champs "Newgame" pour une nouvelle partie, "Loadgame" pour charger une partie, "Return" pour retourner au menu principal.
	menu_ingame = Tableau de char* ou string, champs du menu ingame.*/
	
	menu_ingame[0]=(char*) malloc(255);
	menu_ingame[1]=(char*) malloc(255);
	menu_ingame[2]=(char*) malloc(255);
	
	strcpy(menu_ingame[0], "Newgame");
	strcpy(menu_ingame[1], "Loadgame");
	strcpy(menu_ingame[2], "Return");
}

void intSaveGameMenu(char** savegame_menu)
{
	/*Permet d'iniatiliser des champs du menu savegame, les champs "Slot 1", "Slot 2", "Slot 3", "Slot 4", "Slot 5". 
	savegame_menu = Tableau de char* ou string, champs du menu savegame.*/
	
	savegame_menu[0]=(char*) malloc(255);
	savegame_menu[1]=(char*) malloc(255);
	savegame_menu[2]=(char*) malloc(255);
	savegame_menu[3]=(char*) malloc(255);
	savegame_menu[4]=(char*) malloc(255);
	
	strcpy(savegame_menu[0], "Slot 1");
	strcpy(savegame_menu[1], "Slot 2");
	strcpy(savegame_menu[2], "Slot 3");
	strcpy(savegame_menu[3], "Slot 4");
	strcpy(savegame_menu[4], "Slot 5");
}

void intLoadGameMenu(char** loadgame_menu, int *nb_champ_menu, char* vn_folder_name)
{
	/*Permet d'initialiser les différents du champ du menu "loadgame". Il y aura des champs qui vont former une liste des différents sauvegardes présents dans le dossier "Save" et un champ "Return".
	loadgame_menu = tableau de string ou char*, champs du menu de "loadgame".
	nb_champ_menu = int, nombre de champ du menu.
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.*/	
	DIR* save_directory_dir=NULL; dirent* save_folder=NULL;
	int i_box=0;
	char* save_directory=(char*) malloc(255);
	
	sprintf(save_directory, "VN/%s/save/", vn_folder_name);
	save_directory_dir=opendir(save_directory);
	while ((save_folder=readdir(save_directory_dir))!=NULL && i_box<=5)//On repère dans le dossier "save", un à un les différentes sauvegardes et on note leur nom dans une case du tableau et cela tant qu'on a pas fini de lister toutes les sauvegardes. Limite maximale de 5 Sauvegardes.
	{
		if (strcmp (save_folder->d_name,"..") != 0 && strcmp (save_folder->d_name,".") != 0)//On ne note le nom du dossier que si celui-ci n'a pas pour nom "." et ".."
		{	
			loadgame_menu[i_box]=(char*) malloc(255);
			strcpy(loadgame_menu[i_box], save_folder->d_name);
			i_box++;
		}
	}
	loadgame_menu[i_box]=(char*) malloc(255);
	strcpy(loadgame_menu[i_box], "Return");
	*nb_champ_menu=i_box+1;
	
	free(save_directory), save_directory=NULL;
	closedir(save_directory_dir), save_directory_dir=NULL;
}

void intFlagIsAllocated(int *flag_is_allocated)
{
	/*Permet d'iniatiliser un tableau de int "flag_is_allocated". Tous les champs vont être initialisé FALSE, pour signifier que pour l'heure aucune case du tableau currentRoute n'a reçu de malloc.
	flag_is_allocated = tableau de int qui sera initialisé.*/
	int i=0;
	
	while (i<NBMAX_DIA)//On initialise un à un toutes les cases de "flag_is_allocated" jusqu'à atteindre le nombre maximal de champ
	{
		flag_is_allocated[i]=FALSE;
		i++;
	}
}

void loadFlagIsAllocated(int *flag_is_allocated, const int length_currentRoute)
{
	/*Permet de charger les cases du tableau de int "flag_is_allocated" en fonction des cases du tableau currentRoute qui ont reçu un malloc ou non.
	flag_is_allocated = tableau de int qui va subir le chargement.
	length_currentRoute = int, taille du parcours du l'utilisateur lors de sa précedente partie.*/
	int i=0;
	
	while (i<=length_currentRoute)//On initialise "TRUE" les cases du tableau "flag_is_allocated" jusqu'à dépasser length_currentRoute, l'iniatilisation se fait donc en fonction des cases du tableau currentRoute qui ont reçu un malloc celle du parcours
	{
		flag_is_allocated[i]=TRUE;
		i++;
	}
	while (i<NBMAX_DIA)//On initialise "FALSE" le reste des cases de "flag_is_allocated" jusqu'à atteindre le nombre maximal de cases
	{
		flag_is_allocated[i]=FALSE;
		i++;
	}
}

void freeMenuForPlayVN(char** Menu, const int nb_champ_menu)
{
	
	int i=0;
	
	while (i<nb_champ_menu)//Elle libère la mémoire RAM de chaque case une par une, pour chaque champ jusqu'à ce soit fait pour toutes les cases du tableau
	{
		free(Menu[i]);
		Menu[i]=NULL;
		i++;
	}
}

void freeDia(Dialogue *dia)
{
	free(dia->dia_text), dia->dia_text=NULL;
	free(dia->background), dia->background=NULL;
	free(dia->profile_picture), dia->profile_picture=NULL;
	free(dia->character_name), dia->character_name=NULL;
}

void freeCurrentRoute(Dialogue *dia, char** currentRoute, char** user_actions, const int nb_actions)
{

	int i=0;
	
	while (i<=dia->length_currentRoute)//Elle libère la mémoire RAM attribuée pour chaque champ de currentRoute utilisé jusqu'à les avoir toutes libérés
	{
	   free(currentRoute[i]);
	   currentRoute[i]=NULL;
		i++;
	}
	
	i=0;
	while (i<nb_actions)//Elle libère la mémoire RAM attribuée pour chaque champ de user_actions utilisé jusqu'à les avoir toutes libérés
	{
		free(user_actions[i]);
		user_actions[i]=NULL;
		i++;
	}
}

int checkUserActions(FILE *previous_dia_file, char** user_actions, const int nb_actions)
{
	/*Permet de vérifier si l'utiisateur a bel et bien rempli les conditions en vérifiant le tableau user_actions.
	previous_dia_file = variable FILE, fichier du précedent dia.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.*/
	int i_condition=0, i_action=0, stop_to_check=FALSE, requirement_is_ok=FALSE, condition_is_ok[NBMAX_CONDITIONS], nb_conditions=0; 
	char* conditions[NBMAX_CONDITIONS];
	
	fscanf(previous_dia_file, "%d ", &nb_conditions);
	while (i_condition<nb_conditions)//La fonction va prendre chaque conditions une à une et vérifier si l'utiisateur l'a respectée ou non jusqu'à l'avoir fait pour toutes les conditions
	{
		condition_is_ok[i_condition]=FALSE;
		conditions[i_condition]=(char*) malloc(1000);

		fscanf(previous_dia_file, "%[^$]s", conditions[i_condition]);
		fscanf(previous_dia_file, "%*s");
		
		for ( i_action=0; i_action < nb_actions && condition_is_ok[i_condition]==FALSE; i_action++)//Elle va consulter chaque action de l'utiisateur et voir s'il a bel et bien rempli cette condition. Si l'utiisateur a respecté la conditions, alors elle va arrêter de consulter les actions de l'utiisateur sinon elle continue
		{
			if (strcmp(conditions[i_condition], user_actions[i_action])==0)//L'utiisateur a respecté la condition
			{
				condition_is_ok[i_condition]=TRUE;
			}
		}
		free(conditions[i_condition]), conditions[i_condition]=NULL;
		i_condition++;
	}
	
	i_condition=0;
	
	while (i_condition<nb_conditions && stop_to_check==FALSE)//La fonction vérifie si toutes les conditions ont été respectées
	{
		if (condition_is_ok[i_condition]==FALSE)//Si une seule conditions n'a pas été respectée, elle arrête la  vérification
		{
			stop_to_check=TRUE;
		}
		i_condition++;
	}
	if (stop_to_check==FALSE)//Si au cours de sa vérification, toutes les conditions ont été respectées. La fonction va retourner la valeur TRUE.(Sinon la valeur FALSE)
	{
		requirement_is_ok=TRUE;
	}
	
	return requirement_is_ok;
}

void saveGame(char** currentRoute, const int length_currentRoute, const int i_currentBranch, char** user_actions, const int nb_actions, const int i_save, char** savegame_menu, char* vn_folder_name)
{
	/*Permet à l'utiisateur de sauvegarder sa partie en créeant un fichier de sauvegarde "savvn" et en y inscrivant les différentes données qui seront nécessaires plus tard pour charger la partie.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	user_actions = tableau de char* ou string, actions accomplies par l'utiisateur au cours de sa partie précedente.
	nb_actions = int, nombre d'actions accomplis par l'utiisateur au cours de sa partie précedente.
	i_save = int, index de la slot choisie par l'utiisateur pour sauvegarder sa partie.
	savegame_menu = Tableau de char* ou string, .
	vn_folder_name = string ou char* qui contient le nom du dossier du Visual Novel dans lequel le fichier "savvn" sera créé.*/
	FILE *save_file=NULL;
	int i=0;
	char* save_file_directory=(char*) malloc(255);

	
	sprintf(save_file_directory, "VN/%s/save/Save%s.savvn", vn_folder_name, savegame_menu[i_save]);
	save_file=fopen(save_file_directory, "w");
	
	fprintf(save_file, "%d\n", length_currentRoute);
	while (i<=length_currentRoute)//La fonction va inscrire dans le fichier "sav" le nom de tous les fichiers "dia" utilisés par l'utiisateur au cours de sa partie jusqu'à les avoir tous inscrits
	{
		fprintf(save_file, "%s\n", currentRoute[i]);
		i++;
	}
	
	fprintf(save_file, "%d\n", i_currentBranch);
	fprintf(save_file, "%d\n", nb_actions);
	
	i=0;
	while (i<nb_actions)//La fonction va inscrire dans le fichier "sav" toute les actions effectuées par l'utiisateur au cours de sa partie jusqu'à les avoir toutes inscrites
	{
		fprintf(save_file, "%s\n", user_actions[i]);
		i++;
	}
	
	fclose(save_file), save_file=NULL;
	free(save_file_directory), save_file_directory=NULL;
}

void loadGame(char** currentRoute, int *length_currentRoute, int *i_currentBranch, char** user_actions, int *nb_actions, const int i_saveslot, char** loadgame_menu, char* vn_folder_name)
{
	/*Permet à l'utiisateur de charger sa partie en récupérant dans le fichier de sauvegarde "savvn" choisi par l'utiisateur les différentes données nécessaires.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	user_actions = tableau de char* ou string, actions accomplies par l'utiisateur au cours de sa partie précedente.
	nb_actions = int, nombre d'actions accomplis par l'utiisateur au cours de sa partie précedente.
	i_saveslot = int, index du slot de sauvegarde choisi par l'utiisateur pour charger sa partie.
	loadgame_menu = tableau de string ou char*, champs du menu de "loadgame".
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.*/
	FILE *save_file=NULL;
	int i=0;
	char* save_file_directory=(char*) malloc(255);

	
	sprintf(save_file_directory, "VN/%s/save/%s", vn_folder_name, loadgame_menu[i_saveslot]);
	save_file=fopen(save_file_directory, "r");
	
	fscanf(save_file, "%d", length_currentRoute);
	while (i<=*length_currentRoute)//La fonction va initialiser une à une chaque case du tableau "currentRoute" avec le nom de tous les fichiers "dia" utilisés par l'utiisateur au cours de sa partie précedente jusqu'à l'avoir fait pour tous les fichiers
	{
		currentRoute[i]=(char*) malloc(255);
		fscanf(save_file, "%s", currentRoute[i]);
		i++;
	}
	
	fscanf(save_file, "%d", i_currentBranch);
	fscanf(save_file, "%d", nb_actions);
	
	i=0;
	while (i<*nb_actions)//La fonction va initialisé une à une chaque case du tableau "user_actions" avec les différentes actions effectuées par l'utiisateur au cours de sa partie précedente jusqu'à l'avoir fait pour toutes les actions
	{
		user_actions[i]=(char*) malloc(255);
		fscanf(save_file, "%s", user_actions[i]);
		i++;
	}
	
	fclose(save_file), save_file=NULL;
	free(save_file_directory), save_file_directory=NULL;
}

void getUserActions(int* nb_actions, char** user_actions, const int highlight_choice, char** choice_menu)
{
	/*Permet d'enregistrer le choix qu'à fait l'utilisateur.
	nb_actions = int, nombre d'actions accomplis par l'utiisateur.
	user_actions = tableau de char* ou string, actions accomplies par l'utiisateur au cours de sa partie.
	highlight_choice = int, index du choix fait par l'utiisateur.
	choice_menu = tableau de char* ou string, champs du menu des choix.*/
	*nb_actions=*nb_actions+1;
	user_actions[*nb_actions-1]=(char*) malloc(1000);
	
	strcpy(user_actions[*nb_actions-1], choice_menu[highlight_choice]);
}

	/*Permet de modifier les cases du tableau flag_is_allocated en les mettant toutes à FALSE.
	flag_is_allocated = tableau de int qui va être modifié.*/
void setFlagIsAllocated(int *flag_is_allocated)
{
	int i=0;
	
	while (i<NBMAX_DIA)
	{
		flag_is_allocated[i]=FALSE;
		i++;
	}
}
