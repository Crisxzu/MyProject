#ifndef DEF_PLAYVNMODEL
#define DEF_PLAYVNMODEL

#include "struct.h"
typedef struct dirent dirent;
#define NBMAX_DIA 9999
#define NBMAX_CONDITIONS 10
#define NBMAX_CHAR_DIA_TEXT 415
#define KEY_RIGHT 999
#define KEY_LEFT 998
//////////PUBLIC//////////

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
void loadDia(char *vn_folder_name, Dialogue *dia, char** currentRoute, int *endofVN, int *choice_is_detected, char** choice_menu, int *nb_choice, const int highlight_choice, int *flag_is_allocated, char** user_actions, int *nb_actions, const int keyboard_input);

	/*Permet d'iniatiliser un tableau de int "flag_is_allocated". Tous les champs vont être initialisé FALSE, pour signifier que pour l'heure aucune case du tableau currentRoute n'a reçu de malloc.
	flag_is_allocated = tableau de int qui sera initialisé.*/
void intFlagIsAllocated(int *flag_is_allocated);

	/*Permet de charger les cases du tableau de int "flag_is_allocated" en fonction des cases du tableau currentRoute qui ont reçu un malloc ou non.
	flag_is_allocated = tableau de int qui va subir le chargement.
	length_currentRoute = int, taille du parcours du l'utilisateur lors de sa précedente partie.*/
void loadFlagIsAllocated(int *flag_is_allocated, const int length_currentRoute);

void freeMenuForPlayVN(char** Menu, const int nb_champ_menu);

void freeDia(Dialogue *dia);

void freeCurrentRoute(Dialogue *dia, char** currentRoute, char** user_actions, const int nb_actions);

	/*Permet à l'utiisateur de sauvegarder sa partie en créeant un fichier de sauvegarde "savvn" et en y inscrivant les différentes données qui seront nécessaires plus tard pour charger la partie.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	user_actions = tableau de char* ou string, actions accomplies par l'utiisateur au cours de sa partie précedente.
	nb_actions = int, nombre d'actions accomplis par l'utiisateur au cours de sa partie précedente.
	i_save = int, index de la slot choisie par l'utiisateur pour sauvegarder sa partie.
	savegame_menu = Tableau de char* ou string, .
	vn_folder_name = string ou char* qui contient le nom du dossier du Visual Novel dans lequel le fichier "savvn" sera créé.*/
void saveGame(char** currentRoute, const int length_currentRoute, const int i_currentBranch, char** user_actions, const int nb_actions, const int i_save, char** savegame_menu, char* vn_folder_name);

	/*Permet à l'utiisateur de charger sa partie en récupérant dans le fichier de sauvegarde "savvn" choisi par l'utiisateur les différentes données nécessaires.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	user_actions = tableau de char* ou string, actions accomplies par l'utiisateur au cours de sa partie précedente.
	nb_actions = int, nombre d'actions accomplis par l'utiisateur au cours de sa partie précedente.
	i_saveslot = int, index du slot de sauvegarde choisi par l'utiisateur pour charger sa partie.
	loadgame_menu = tableau de string ou char*, champs du menu de "loadgame".
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.*/
void loadGame(char** currentRoute, int *length_currentRoute, int *i_currentBranch, char** user_actions, int *nb_actions, const int i_saveslot, char** loadgame_menu, char* vn_folder_name);

	/*Permet d'enregistrer le choix qu'à fait l'utilisateur.
	nb_actions = int, nombre d'actions accomplis par l'utiisateur.
	user_actions = tableau de char* ou string, actions accomplies par l'utiisateur au cours de sa partie.
	highlight_choice = int, index du choix fait par l'utiisateur.
	choice_menu = tableau de char* ou string, champs du menu des choix.*/
void getUserActions(int* nb_actions, char** user_actions, const int highlight_choice, char** choice_menu);

	/*Permet de modifier les cases du tableau flag_is_allocated en les mettant toutes à FALSE.
	flag_is_allocated = tableau de int qui va être modifié.*/
void setFlagIsAllocated(int *flag_is_allocated);

//////////PRIVATE//////////
	
	/*Permet de modifier la valeur de i_currentBranch en fonction de la taille du nom du fichier dia.
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
void setIndexCurrentBranch(Dialogue *dia, char** currentRoute);

	/*Permet de récuperer les choix présents dans le fichier dia.
	dia_file = variable FILE, fichier dia
	choice_menu = tableau de char* ou string, champs du menu des choix.
	nb_choice = int, nombre de choix.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.
	keyboard_input = int, touche qui a été appuyée par l'utiisateur suivant son pavé directionnel.
	choice_is_detected = int, boolean pour savoir si des choix ont été détectés dans un fichier dia.*/
void getChoice(FILE *dia_file, char** choice_menu, int *nb_choice, char** user_actions, int *nb_actions, const int keyboard_input, int *choice_is_detected);
	
	/*Permet d'obtenir le nom du fichier dia dans le cas où l'utiisateur au cours du dialogue précedent n'a pas eu à faire un choix en allant tout d'abord chercher le nom du fichier.
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	flag_is_allocated = tableau de int dont la valeur de certains cases va être initialisé en TRUE ou FALSE en fonction de si une case du tableau currentRoute a reçu un malloc ou non.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.*/
FILE *openDiaFileIfNoChoice(Dialogue *dia, char** currentRoute, int *flag_is_allocated, char** user_actions, const int nb_actions, char *vn_folder_name);

	/*Permet d'ouvrir le fichier dia dans le cas où l'utiisateur a eu au cours du dialogue précedent à faire un choix en allant tout d'abord chercher le nom du fichier.
	dia_file = variable FILE, fichier dia.
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.
	choice_is_detected = int, boolean pour savoir si des choix ont été détectés dans un fichier dia.
	nb_choice = int, nombre de choix.
	highlight_choice = int, index du choix fait par l'utiisateur.
	flag_is_allocated = tableau de int dont la valeur de certains cases va être initialisé en TRUE ou FALSE en fonction de si une case du tableau currentRoute a reçu un malloc ou non.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.*/
FILE *openDiaFileIfChoice(Dialogue *dia, char** currentRoute, int *choice_is_detected, const int nb_choice, const int highlight_choice, int *flag_is_allocated, char** user_actions, const int nb_actions, char *vn_folder_name);

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
FILE *openDiaFile(Dialogue *dia, char** currentRoute, int *choice_is_detected, const int nb_choice, const int highlight_choice, int *flag_is_allocated, const int keyboard_input, char** user_actions, const int nb_actions, char *vn_folder_name);

	/*Permet de vérifier si l'utiisateur a bel et bien rempli les conditions en vérifiant le tableau user_actions.
	previous_dia_file = variable FILE, fichier du précedent dia.
	user_actions = tableau de char* ou string, actions accomplis par l'utilisateur au cours de sa partie.
	nb_actions = int, nombre de actions accomplis par l'utiisateur au cours de sa partie.*/
int checkUserActions(FILE *fbackdia, char** user_actions, const int nb_actions);

#endif

