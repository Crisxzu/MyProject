#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <gtk/gtk.h>
#include "playVNModel.h"

	/*Permet de récuperer les choix présents dans le fichier dia.
	dia_file = variable FILE, fichier dia
	choice_menu = tableau de char* ou string, champs du menu des choix.
	nb_choice = int, nombre de choix.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.
	keyboard_input = int, touche qui a été appuyée par l'utiisateur suivant son pavé directionnel.
	choice_is_detected = int, boolean pour savoir si des choix ont été détectés dans un fichier dia.*/
void getChoice(FILE *dia_file, char** choice_menu, int *nb_choice, char** user_actions, int *nb_actions, const int keyboard_input, int *choice_is_detected)
{
	int i_choice=0; 
	char* string_to_check=(char*) malloc(255);

	fscanf(dia_file, "%*s %d", nb_choice);
	
	//Si en explorant le fichier "dia", des choix ont été détectés alors les différents champs du menu choice_menu vont être iniatilisés avec le texte des différents choix
	if (*nb_choice>=2)
	{
		*choice_is_detected=TRUE;
		
		//Si l'utiisateur se trouve dans le cas où il effectue un retour en arrière et que le dialogue à afficher comporte des choix à faire, on se trouve alors dans un cas où l'utilisateur revient sur un choix qu'il a déjà fait par conséquent, sa dernière action sera supprimé du tableau user_actions
		if (keyboard_input==KEY_LEFT)
		{
			free(user_actions[*nb_actions-1]), user_actions[*nb_actions-1]=NULL;
			*nb_actions=*nb_actions-1;
		}
		
		//Le texte de chaque choix sera enregistré un à un dans chaque champ de choice_menu jusqu'à ce qu'ils soient tous enregistrés
		while (i_choice<*nb_choice)
		{
			choice_menu[i_choice]=(char*) malloc(255);
			
			fscanf(dia_file, "%*s %[^$]s", choice_menu[i_choice]);
			fscanf(dia_file,"%*s %s", string_to_check);
			
			//Si après avoir enregistré le texte d'un choix, la fonction détecte la présence de conditions particulières attribuées à ce choix, elle les passera pour passer au prochain choix
			if (strcmp(string_to_check, "(if")==0)
			{
				int nb_string_to_pass=0, i=0;
								
				fscanf(dia_file, "%d ", &nb_string_to_pass);
				
				//Passe le texte de chaque conditions jusqu'à les avoir tous passés
				while (i<nb_string_to_pass)
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
	
	//Si en explorant le fichier "dia", des choix n'ont pas été détectés alors les différents champs du menu choice_menu ne vont pas être iniatilisés et la fonction va directement passé à la prochaine partie du fichier pour récupérer le décor, la photo du personnage, le nom du personnage et le texte du dialogue
	else
	{
		fscanf(dia_file,"%s", string_to_check);
		
		//Si en passant à la prochaine du partie du fichier, la fonction détecte la présence de conditions particulières attribuées pour le choix du prochain fichier "dia" à consulter, elle va les passer
		if (strcmp(string_to_check, "(if")==0)
		{
			int nb_string_to_pass=0, i=0;
			
			fscanf(dia_file, "%d ", &nb_string_to_pass);
			
			//Passe le texte de chaque conditions jusqu'à les avoir tous passés
			while (i<nb_string_to_pass)
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
			
			//Si l'utiisateur se trouve au début du Visual Novel, le nom du fichier est arbitrairement 0000.dia et la fonction n'ira pas chercher le nom du fichier dans le fichier "dia" précedent
			if (dia->length_currentRoute==0)
			{
				sprintf(currentRoute[dia->length_currentRoute], "%04d", dia->length_currentRoute);
				sprintf(dia_file_directory, "VN/%s/%s.dia", vn_folder_name, currentRoute[dia->length_currentRoute]);
				dia_file=fopen(dia_file_directory, "r");
			}
			
			//Si l'utiisateur ne trouve pas au début du Visual Novel, alors la fonction ira chercher le nom du fichier dans le fichier "dia" précedent
			else if(dia->length_currentRoute>0)
			{
				FILE *previous_dia_file=NULL;
				
				sprintf(dia_file_directory, "VN/%s/%s.dia", vn_folder_name, currentRoute[dia->length_currentRoute-1]);
				previous_dia_file=fopen(dia_file_directory, "r");
				
				fscanf(previous_dia_file,"%*s %*s %s", string_to_check);
				
				//Si la fonction détecte la présence de conditions particulières, elle va les analyser
				if (strcmp(string_to_check, "(if")==0)
				{
					int requirement_is_ok=0;
					
					requirement_is_ok=checkUserActions(previous_dia_file, user_actions, nb_actions);
					
					//Si toutes les conditions ont été respectés par l'utilisateur, le nom du fichier "dia" à récupérer sera celui du cas où les conditions ont été respectés
					if (requirement_is_ok==TRUE)
					{
						fscanf(previous_dia_file, "%*s %s %*s %*s %*s", currentRoute[dia->length_currentRoute]);
					}
					
					//Si toutes les conditions n'ont pas été respectés par l'utiisateur, le nom du fichier "dia" à récupérer sera celui du cas où les conditions n'ont pas été respectés
					else
					{
						fscanf(previous_dia_file, "%*s %*s %*s %*s %s", currentRoute[dia->length_currentRoute]);
					}
				}
				
				//Si la fonction n'a pas détecté de conditions particulières, elle va récuperer le nom du fichier "dia" du dialogue à intialiser sans faire une analyse des conditions
				else
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
	
	//Si le nom du fichier "dia" suit un format XXXX, l'index de la branche sera celle du nom du fichier "dia"
	if (length_dia_file_name==4)
	{
		sscanf(currentRoute[dia->length_currentRoute], "%d", &dia->i_currentBranch);
	}
	
	//Si le nom du fichier "dia" suit un autre format, l'index de la branche sera celui de l'index qui se trouve au bout du nom du fichier
	else
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
	
	//Au cours de l'exploration du fichier "dia" du dialogue précédent, la fonction va passer différentes parties du fichier "dia" jusqu'à atteindre celle correspondant au choix fait par l'utilisateur
	while (i_choice!=highlight_choice && i_choice<nb_choice)
	{
		fscanf(previous_dia_file, "%*s %*[^$]s");
		fscanf(previous_dia_file,"%*s %s", string_to_check);
		
		//Si en passant le texte d'un choix, la fonction détecte la présence de conditions particulières attribuées à ce choix, elle va les passer aussi
		if (strcmp(string_to_check, "(if")==0)
		{
			int nb_string_to_pass=0, i=0;
			
			fscanf(previous_dia_file, "%d ", &nb_string_to_pass);
			
			//Passe le texte de chaque conditions jusqu'à les avoir toutes passés
			while (i<nb_string_to_pass)
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
	
	//Une fois arrivé à la partie du chier "dia" correspondant à celle du choix de l'utiisateur, si la fonction détecte la présence de conditions particulières, elle va les analyser
	if (strcmp(string_to_check, "(if")==0)
	{
		int requirement_is_ok=0;
		
		requirement_is_ok=checkUserActions(previous_dia_file, user_actions, nb_actions);
		
		//Si toutes les conditions ont été respectés par l'utilisateur, le nom du fichier "dia" à récupérer sera celui du cas où les conditions ont été respectés
		if (requirement_is_ok==TRUE)
		{
			fscanf(previous_dia_file, "%*s %s %*s %*s %*s", currentRoute[dia->length_currentRoute]);
		}
		
		//Si toutes les conditions n'ont pas été respectés par l'utiisateur, le nom du fichier "dia" à récupérer sera celui du cas où les conditions n'ont pas été respectés
		else
		{
			fscanf(previous_dia_file, "%*s %*s %*s %*s %s", currentRoute[dia->length_currentRoute]);
		}
	}
	
	//Si la fonction n'a pas détecté de conditions particulières, elle va récuperer le nom du fichier "dia" du dialogue à intialiser pour ce choix de l'utiisateur sans faire une analyse des conditions	
	else
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
	
	//Si des choix ont été détectés pour un dialogue et que l'utiisateur a préféré revenir en arrière(au dialogue qui le précède) et donc n'a pas fait de choix
	if (*choice_is_detected==TRUE && keyboard_input==KEY_LEFT)
	{
		*choice_is_detected=FALSE;
	}
	
	//Si au cours du dialogue précédent l'utiisateur a eu à faire un choix, la fonction va chercher le nom du fichier "dia" du dialogue à iniatiliser en fonction du choix de l'utiisateur et l'ouvrir
	if (*choice_is_detected==TRUE)
	{
		dia_file=openDiaFileIfChoice(dia, currentRoute, choice_is_detected, nb_choice, highlight_choice, flag_is_allocated, user_actions, nb_actions, vn_folder_name);
	}
	
	//Si au cours du dialogue précédent, l'utilisateur n'a pas fait de choix, la fonction va aller chercher dans le fichier "dia" précedent le nom du fichier "dia" pour iniatiliser le dialogue(sans se soucier d'un choix de l'utilisateur) et l'ouvrir
	else
	{
		dia_file=openDiaFileIfNoChoice(dia, currentRoute, flag_is_allocated, user_actions, nb_actions, vn_folder_name);
	}
	
	//Si de la mémoire RAM a été attribuée au dialogue qui vient juste après celui qui a été ouvert, alors celle-ci va être libérée(Dans ce cas précis, l'utiisateur a fait un retour arrière et en le faisant il perd aussi une partie de sa progression)
	if (flag_is_allocated[dia->length_currentRoute+1]==TRUE)
	{
		free(currentRoute[dia->length_currentRoute+1]), currentRoute[dia->length_currentRoute+1]=NULL;
		flag_is_allocated[dia->length_currentRoute+1]=FALSE;
	}
	return dia_file;
}

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
void loadDia(char *vn_folder_name, Dialogue *dia, char** currentRoute, int *endofVN, int *choice_is_detected, char** choice_menu, int *nb_choice, const int highlight_choice, int *flag_is_allocated, char** user_actions, int *nb_actions, const int keyboard_input)
{	
	FILE *dia_file=NULL;
	char* file_directory=(char*) malloc(255); char* file_name=(char*) malloc(255);
	*endofVN=FALSE;
	
	dia_file=openDiaFile(dia, currentRoute, choice_is_detected, *nb_choice, highlight_choice, flag_is_allocated, keyboard_input, user_actions, *nb_actions, vn_folder_name);

	//Si le fichier "dia" qu'il faut utiliser pour iniatiliser le dialogue existe et que la limite maximale du nombre de dialogue n'est pas dépassé(9999), la fonction va récupérer le décor, la photo du personnage, le nom du personnage et le texte du dialogue
	if (dia_file!=NULL && dia->length_currentRoute<=9999)
	{
		getChoice(dia_file, choice_menu, nb_choice, user_actions, nb_actions, keyboard_input, choice_is_detected);
		fscanf(dia_file, "%*s %s", file_name);
		sprintf(file_directory, "VN/%s/img/background/%s", vn_folder_name, file_name);
		dia->background_pixbuf=gdk_pixbuf_new_from_file_at_scale(file_directory, WINDOW_WIDTH, WINDOW_HEIGHT, FALSE, NULL);

		fscanf(dia_file, "%*s %s", file_name);
		sprintf(file_directory, "VN/%s/img/profilepic/%s", vn_folder_name, file_name);
		dia->profile_picture_pixbuf=gdk_pixbuf_new_from_file_at_scale(file_directory, PROFILE_PIC_WIDTH, PROFILE_PIC_HEIGHT, FALSE, NULL);
		__struct_global.f_image_is_loaded=TRUE;
		
		fscanf(dia_file, "%*s %s", dia->character_name);
		/*fscanf(dia_file, "%*s");
		fgets(dia->dia_text, NBMAX_CHAR_DIA_TEXT, dia_file);*/
		
		fscanf(dia_file, "%*s %[^\n]s", dia->dia_text);
		
		fclose(dia_file), dia_file=NULL;

	}
	
	//Si le fichier "dia" qu'il faut utiliser pour iniatiliser le dialogue n'existe pas ou si la limite maximale de nombre de dialogue est dépassé(9999), cela signifie que l'utilisateur est arrivé au bout du Visual Novel qu'il est en train de jouer par conséquent la phrase "THE END" sera affiché.
	else if(dia_file==NULL || dia->length_currentRoute>9999)
	{
		
		strcpy(dia->dia_text, "THE END");
		*endofVN=TRUE;
	}
	free(file_directory), file_directory=NULL;
	free(file_name), file_name=NULL;
}

	/*Permet d'iniatiliser un tableau de int "flag_is_allocated". Tous les champs vont être initialisé FALSE, pour signifier que pour l'heure aucune case du tableau currentRoute n'a reçu de malloc.
	flag_is_allocated = tableau de int qui sera initialisé.*/
void intFlagIsAllocated(int *flag_is_allocated)
{
	int i=0;
	
	//On initialise un à un toutes les cases de "flag_is_allocated" jusqu'à atteindre le nombre maximal de champ
	while (i<NBMAX_DIA)
	{
		flag_is_allocated[i]=FALSE;
		i++;
	}
}

	/*Permet de charger les cases du tableau de int "flag_is_allocated" en fonction des cases du tableau currentRoute qui ont reçu un malloc ou non.
	flag_is_allocated = tableau de int qui va subir le chargement.
	length_currentRoute = int, taille du parcours du l'utilisateur lors de sa précedente partie.*/
void loadFlagIsAllocated(int *flag_is_allocated, const int length_currentRoute)
{
	int i=0;
	
	//Initialise "TRUE" les cases du tableau "flag_is_allocated" jusqu'à dépasser length_currentRoute, l'iniatilisation se fait donc en fonction des cases du tableau currentRoute qui ont reçu un malloc celle du parcours
	while (i<=length_currentRoute)
	{
		flag_is_allocated[i]=TRUE;
		i++;
	}
	
	//Initialise "FALSE" le reste des cases de "flag_is_allocated" jusqu'à atteindre le nombre maximal de cases
	while (i<NBMAX_DIA)
	{
		flag_is_allocated[i]=FALSE;
		i++;
	}
}

void freeMenuForPlayVN(char** Menu, const int nb_champ_menu)
{
	
	int i=0;
	
	//Libère la mémoire RAM de chaque case une par une, pour chaque champ jusqu'à ce soit fait pour toutes les cases du tableau
	while (i<nb_champ_menu)
	{
		free(Menu[i]);
		Menu[i]=NULL;
		i++;
	}
}

void freeDia(Dialogue *dia)
{
	free(dia->dia_text), dia->dia_text=NULL;
	if (__struct_global.f_image_is_loaded)
	{
		g_object_unref(dia->background_pixbuf), dia->background_pixbuf=NULL;
		g_object_unref(dia->profile_picture_pixbuf), dia->profile_picture_pixbuf=NULL;
		__struct_global.f_image_is_loaded=FALSE;	
	}
	free(dia->character_name), dia->character_name=NULL;
}

void freeCurrentRoute(Dialogue *dia, char** currentRoute, char** user_actions, const int nb_actions)
{

	int i=0;
	
	//Libère la mémoire RAM attribuée pour chaque champ de currentRoute utilisé jusqu'à les avoir toutes libérés
	while (i<=dia->length_currentRoute)
	{
	   free(currentRoute[i]);
	   currentRoute[i]=NULL;
		i++;
	}
	
	i=0;
	//Libère la mémoire RAM attribuée pour chaque champ de user_actions utilisé jusqu'à les avoir toutes libérés
	while (i<nb_actions)
	{
		free(user_actions[i]);
		user_actions[i]=NULL;
		i++;
	}
}

	/*Permet de vérifier si l'utiisateur a bel et bien rempli les conditions en vérifiant le tableau user_actions.
	previous_dia_file = variable FILE, fichier du précedent dia.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.*/
int checkUserActions(FILE *previous_dia_file, char** user_actions, const int nb_actions)
{
	int i_condition=0, i_action=0, stop_to_check=FALSE, requirement_is_ok=FALSE, condition_is_ok[NBMAX_CONDITIONS], nb_conditions=0; 
	char* conditions[NBMAX_CONDITIONS];
	
	fscanf(previous_dia_file, "%d ", &nb_conditions);
	
	//La fonction va prendre chaque conditions une à une et vérifier si l'utiisateur l'a respectée ou non jusqu'à l'avoir fait pour toutes les conditions
	while (i_condition<nb_conditions)
	{
		condition_is_ok[i_condition]=FALSE;
		conditions[i_condition]=(char*) malloc(1000);

		fscanf(previous_dia_file, "%[^$]s", conditions[i_condition]);
		fscanf(previous_dia_file, "%*s");
		
		//Elle va consulter chaque action de l'utiisateur et voir s'il a bel et bien rempli cette condition. Si l'utiisateur a respecté la conditions, alors elle va arrêter de consulter les actions de l'utiisateur sinon elle continue
		for ( i_action=0; i_action < nb_actions && condition_is_ok[i_condition]==FALSE; i_action++)
		{
			//Si l'utiisateur a respecté la condition
			if (strcmp(conditions[i_condition], user_actions[i_action])==0)
			{
				condition_is_ok[i_condition]=TRUE;
			}
		}
		free(conditions[i_condition]), conditions[i_condition]=NULL;
		i_condition++;
	}
	
	i_condition=0;
	
	//Vérifie si toutes les conditions ont été respectées jusqu'à les avoir toutes vérifiées ou qu'une condition ne soit respectée
	while (i_condition<nb_conditions && stop_to_check==FALSE)
	{
		//Si une seule conditions n'a pas été respectée, elle arrête la  vérification
		if (condition_is_ok[i_condition]==FALSE)
		{
			stop_to_check=TRUE;
		}
		i_condition++;
	}
	
	//Si au cours de sa vérification, toutes les conditions ont été respectées. La fonction va retourner la valeur TRUE.(Sinon la valeur FALSE)
	if (stop_to_check==FALSE)
	{
		requirement_is_ok=TRUE;
	}
	
	return requirement_is_ok;
}

	/*Permet à l'utiisateur de sauvegarder sa partie en créeant un fichier de sauvegarde "savvn" et en y inscrivant les différentes données qui seront nécessaires plus tard pour charger la partie.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	user_actions = tableau de char* ou string, actions accomplies par l'utiisateur au cours de sa partie précedente.
	nb_actions = int, nombre d'actions accomplis par l'utiisateur au cours de sa partie précedente.
	i_save = int, index de la slot choisie par l'utiisateur pour sauvegarder sa partie.
	savegame_menu = Tableau de char* ou string, .
	vn_folder_name = string ou char* qui contient le nom du dossier du Visual Novel dans lequel le fichier "savvn" sera créé.*/
void saveGame(char** currentRoute, const int length_currentRoute, const int i_currentBranch, char** user_actions, const int nb_actions, const int i_save, char** savegame_menu, char* vn_folder_name)
{
	FILE *save_file=NULL;
	int i=0;
	char* save_file_directory=(char*) malloc(255);

	
	sprintf(save_file_directory, "VN/%s/save/Save%s.savvn", vn_folder_name, savegame_menu[i_save]);
	save_file=fopen(save_file_directory, "w");
	
	fprintf(save_file, "%d\n", length_currentRoute);
	
	//La fonction va inscrire dans le fichier "sav" le nom de tous les fichiers "dia" utilisés par l'utiisateur au cours de sa partie jusqu'à les avoir tous inscrits
	while (i<=length_currentRoute)
	{
		fprintf(save_file, "%s\n", currentRoute[i]);
		i++;
	}
	
	fprintf(save_file, "%d\n", i_currentBranch);
	fprintf(save_file, "%d\n", nb_actions);
	
	i=0;
	
	//La fonction va inscrire dans le fichier "sav" toute les actions effectuées par l'utiisateur au cours de sa partie jusqu'à les avoir toutes inscrites
	while (i<nb_actions)
	{
		fprintf(save_file, "%s\n", user_actions[i]);
		i++;
	}
	
	fclose(save_file), save_file=NULL;
	free(save_file_directory), save_file_directory=NULL;
}

	/*Permet à l'utiisateur de charger sa partie en récupérant dans le fichier de sauvegarde "savvn" choisi par l'utiisateur les différentes données nécessaires.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	user_actions = tableau de char* ou string, actions accomplies par l'utiisateur au cours de sa partie précedente.
	nb_actions = int, nombre d'actions accomplis par l'utiisateur au cours de sa partie précedente.
	i_saveslot = int, index du slot de sauvegarde choisi par l'utiisateur pour charger sa partie.
	loadgame_menu = tableau de string ou char*, champs du menu de "loadgame".
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.*/
void loadGame(char** currentRoute, int *length_currentRoute, int *i_currentBranch, char** user_actions, int *nb_actions, const int i_saveslot, char** loadgame_menu, char* vn_folder_name)
{
	FILE *save_file=NULL;
	int i=0;
	char* save_file_directory=(char*) malloc(255);

	
	sprintf(save_file_directory, "VN/%s/save/Save%s.savvn", vn_folder_name, loadgame_menu[i_saveslot]);
	save_file=fopen(save_file_directory, "r");
	
	//Si l'utiisateur a choisi une slot sur laquelle se trouve une sauvegarde
	if (save_file!=NULL)
	{
		fscanf(save_file, "%d", length_currentRoute);
		
		//Initialise une à une chaque case du tableau "currentRoute" avec le nom de tous les fichiers "dia" utilisés par l'utiisateur au cours de sa partie précedente jusqu'à l'avoir fait pour tous les fichiers
		while (i<=*length_currentRoute)
		{
			currentRoute[i]=(char*) malloc(255);
			fscanf(save_file, "%s", currentRoute[i]);
			i++;
		}
		
		fscanf(save_file, "%d", i_currentBranch);
		fscanf(save_file, "%d", nb_actions);
		
		i=0;
		
		//Initialise une à une chaque case du tableau "user_actions" avec les différentes actions effectuées par l'utiisateur au cours de sa partie précedente jusqu'à l'avoir fait pour toutes les actions
		while (i<*nb_actions)
		{
			user_actions[i]=(char*) malloc(255);
			fscanf(save_file, "%s", user_actions[i]);
			i++;
		}
		__struct_global.slot_isSelected=TRUE;
		fclose(save_file), save_file=NULL;
	}

	free(save_file_directory), save_file_directory=NULL;
}

	/*Permet d'enregistrer le choix qu'à fait l'utilisateur.
	nb_actions = int, nombre d'actions accomplis par l'utiisateur.
	user_actions = tableau de char* ou string, actions accomplies par l'utiisateur au cours de sa partie.
	highlight_choice = int, index du choix fait par l'utiisateur.
	choice_menu = tableau de char* ou string, champs du menu des choix.*/
void getUserActions(int* nb_actions, char** user_actions, const int highlight_choice, char** choice_menu)
{
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
