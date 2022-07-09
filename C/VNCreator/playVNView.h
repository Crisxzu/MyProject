#ifndef DEF_PLAYVNVIEW
#define DEF_PLAYVNVIEW

#include "struct.h"
//////////PUBLIC//////////

	/*Affiche le contenu d'un fichier dia( plus concrètement le décor, la photo de profil du personnage qui s'exprime en ce moment même, le nom du personnage et le texte du dialogue en lui-même) et les champs "Previous" et "Next".
	next_prev_dia = Tableau de char* ou string, champs "Previous" et "Next".
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.
	dia = variable de la structure "Dialogue", données d'un fichier dia 
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).
	nb_champ_menu = int, nombre total de champs du menu.
	endofVN = int marquant la fin du Visual Novel.
	text_speed = float, vitesse de défilement du texte du dialogue. P.S= Pour text_speed=1, un caractère est affiché toutes les 50ms, le calcul se fait comme suit: temps pour l'affichage d'un caractère= 50ms/valeur de text_speed.*/	
void displayDia(char** playVNMenu, char *vn_folder_name, Dialogue *dia, const int highlight_index, const int text_color, const int nb_champ_menu, const int endofVN, const float text_speed);

	/*Affiche les différents champs du menu qui est entré en paramètres.
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	Menu = tableau(de string ou char*), champs du menu.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).
	nb_champ_menu = int, nombre total de champs du menu.
	vn_folder_name = string ou char*, nom du Visual Novel.*/			
void displayMenuForPlayVN(char** Menu, const int highlight_index, const int text_color, const int nb_champ_menu, char* vn_folder_name);

	/*Permet à l'utilisateur de passer d'un dialogue à un autre via le pavé directionnel(précisément les touches "GAUCHE" et "DROITE", les touches "HAUT" et "BAS" serviront dans le cas où le dialogue affiché est trop grand pour la fenêtre ainsi l'utilisateur pourra voir le reste du texte qui se trouve en bas ou celui qui se trouve en haut).
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. 
	nb_champ_menu = int, nombre total de champs du menu.
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	endofVN = int marquant la fin du Visual Novel.*/
void waitInputDia(int *highlight_index, int *keyboard_input, const int nb_champ_menu, Dialogue *dia, const int endofVN);

	/*Permet à l'utilisateur de se déplacer dans le menu via le pavé directionnel(précisément les touches "HAUT" et "BAS") et de choisir d'accéder à un champ du Menu en faisant "Entrée".
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel ou "Entrée"), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. 
	nb_champ_menu = int, nombre total de champs du menu.*/
void waitInputMenuForPlayVN(int *highlight_index, int *keyboard_input, const int nb_champ_menu);

	/*Permet à l'utilisateur de créer un nouveau fichier qui va servir de décor pour un dialogue(un fichier "background").
	vn_folder_name = string ou char*, nom du Visual Novel.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).*/
void createBackground(char *vn_folder_name, const int text_color);

	/*Permet à l'utilisateur de créer un nouveau fichier qui va servir de photo de profil pour un dialogue(un fichier "pp").
	vn_folder_name = string ou char*, nom du Visual Novel.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).*/
void createProfilePicture(char *vn_folder_name, const int text_color);

	/*Permet à l'utilisateur d'éditer un dialogue et d'accesoirement de créer un nouveau dialogue.
	vn_folder_name = string ou char*, nom du Visual Novel.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
void editDia(char *vn_folder_name, const int length_currentRoute, char** currentRoute, const int i_currentBranch);

//////////PRIVATE//////////

	/*Permet d'insérer dans le nouveau fichier "dia" des données par défaut(Pas de choix, le nom du fichier qui devrait potentiellement le suivre, un emplacement pour insérer le nom du décor, de la photo de profil et du nom du personnage et un emplacement pour insérer un dialogue).
	dia_file = variable FILE, fichier dia.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
void setDefaultDataInFile(FILE *dia_file, char** currentRoute, const int length_currentRoute, const int i_currentBranch);

#endif

