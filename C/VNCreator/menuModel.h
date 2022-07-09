#ifndef DEF_MENUMODEL
#define DEF_MENUMODEL

#include "struct.h"
typedef struct dirent dirent;

//////////PUBLIC//////////

	/*Modifie les valeurs par défaut qui se trouve en paramètres en fonction du choix de l'utilisateur.
	s = variable de la structure "Settings", données des paramètres.
	text_speed = int, vitesse de défilement du texte choisie par l'utiisateur.
	text_color = int, couleur de texte choisie par l'utiisateur.*/
void setSettings(Settings *s, const int text_speed, const int text_color);

	/*Initialise les paramètres(text_speed, text_color, flag_is_allocated et vn_folder_name) avec des valeurs par défaut.
	s = variable de la structure "Settings", données des paramètres.*/ 
void intSettings(Settings *s);

	/*Initialise les différents champs du menu principal(un champ "Play", un champ "Options" et un champ "Quit").
	main_menu = tableau de string ou char*, champs du menu principal.*/
void intMainMenu(char** main_menu);

	/*Initialise les différents champs du menu des paramètres(un champ pour text_speed, un pour text_color et pour "Return").
	settings_menu = tableau de char* ou string, champs du menu des paramètres.
	text_speed = int, vitesse de défilement du texte des différents dialogues des Visual Novel.
	text_color = int, couleur du texte des différents menus qui seront affichés*/
void intSettingsMenu(char** SettingsMenu, const int text_speed, const int text_color);

	/*Initialise l'interface qui va servir à afficher les différents menus du programme, et les différentes couleurs de texte.*/
void initInterface();

	/*Initialise les différents du champ du menu de "Play". Il y aura des champs qui vont former une liste des différents Visual Novel présents dans le dossier "VN", un champ "NewNV" et un champ "Retour".
	list_vn_menu = tableau de string ou char*, champs du menu list_vn.
	nb_champ_menu = nombre total de champ que le menu list_vn aura.*/
void intListVNMenu(char** ListVNMenu, int* nb_champ_menu);
	
	/*Crée un nouveau Visual Novel(concrètement un dossier qui va contenir les différentes éléments qui vont composer le Visual Novel). Au sein de celui-ci, un premier fichier texte nommé "0000.dia" sera créé, il represente le premier dialogue du Visual Novel qui sera créé où il y aura le nom du fichier qui va servir de décor, celui de la photo de profil du perso, le nom du perso et un dialogue test, un dossier "img" où seront entreposés les différents images dont on va se servir pour le décor et la photo du perso des différents dialogues et un dossier "save" qui va contenir les sauvegardes des parties de l'utilisateur.
	new_vn_name_directory = char* ou string, emplacement du Visual Novel que l'utilisateur souhaite créer.*/
void createVN(const char* newVNName);

void freeMenu(char** Menu, const int nb_champ_menu);

#endif

