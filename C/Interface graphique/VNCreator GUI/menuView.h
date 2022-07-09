#ifndef DEF_MENUVIEW
#define DEF_MENUVIEW

#include "struct.h"

#define ENTER 10

//////////PUBLIC//////////

	/*Affiche le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à afficher*/
void displayMenu(GtkWidget *menu_box);

	/*Cache le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à cacher*/
void hideMenu(GtkWidget *menu_box);

	/*Détruit le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à détruire*/
void destroyMenu(GtkWidget *menu_box);

	/*Permet de garder le menu affiché tant que l'utiisateur n'a pas appuyé sur un bouton du menu.*/
void waitInputMenu();

	/*Permet à l'utilisateur d'entrer le nom du nouveau Visual Novel qu'il souhaite créer.
	new_vn_name_directory = char* ou string, emplacement du Visual Novel que l'utilisateur souhaite créer.*/
void enterNewVNname(char* new_vn_name_directory);

	/*Initialise diverses éléments d'une structure global dont on aura besoin pour manipuler l'interface.*/
void initStructGlobal();

	/*Initialise la Vue autrement dit l'interface.*/
void initView(int argc, char** argv);

	/*Initialise la fenêtre principale du programme.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initMainWindow(int *highlight_index);

	/*Initialise les différents champs du menu principal(un champ "Play", un champ "Options" et un champ "Quit").
	main_menu = tableau de string ou char*, champs du menu principal.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initMainMenu(char** main_menu, int *highlight_index);

		/*Initialise les différents champs du menu des paramètres(un champ pour text_speed, un pour text_color et pour "Return").
	settings_menu = tableau de char* ou string, champs du menu des paramètres.
	text_speed = int, vitesse de défilement du texte des différents dialogues des Visual Novel, valeur modifiée en fonction des choix de l'utiisateur.
	text_color = int, couleur du texte des différents dialogues, valeur modifiée en fonction des choix de l'utiisateur.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initSettingsMenu(char** settings_menu, float *text_speed, int *text_color, int *highlight_index);

	/*Initialise la box du menu list_vn.
	list_vn_menu = tableau de string ou char*, champs du menu list_vn.
	nb_champ_menu = nombre total de champ que le menu list_vn aura.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initListVNMenuBox(char **list_vn_menu, const int nb_champ_menu, int *highlight_index);

//////////PRIVATE//////////

	/*Signale que l'utiisateur a appuyé sur le bouton "Play"*/
void playIsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur le bouton "Options"*/
void optionsIsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur le bouton "Quit"*/
void quitIsSelected(GtkWidget *widget, gpointer user_data);

	/*Augmente la valeur de text_speed*/
void incTextSpeed(GtkWidget *widget, gpointer user_data);

	/*Diminue la valeur de text_speed*/
void decTextSpeed(GtkWidget *widget, gpointer user_data);

	/*Augmente la valeur de text_color*/
void incTextColor(GtkWidget *widget, gpointer user_data);

	/*Diminue la valeur de text_color*/
void decTextColor(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur le bouton "Return"*/
void returnIsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a choisi un Visual Novel*/
void vnIsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur le bouton "create_vn"*/
void createVNIsSelected(GtkWidget *widget, gpointer user_data);
#endif

