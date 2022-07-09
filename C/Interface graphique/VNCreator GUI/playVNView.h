#ifndef DEF_PLAYVNVIEW
#define DEF_PLAYVNVIEW

#include "struct.h"
#define KEY_RIGHT 999
#define KEY_LEFT 998
#define KEY_P 112
#define KEY_S 115
#define KEY_D 100
#define KEY_Q 113
//////////PUBLIC//////////

	/*Affiche le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à afficher*/
void displayMenuForPlayVN(GtkWidget *menu_box);

	/*Cache le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à cacher*/
void hideMenuForPlayVN(GtkWidget *menu_box);

	/*Détruit le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à détruire*/
void destroyMenuForPlayVN(GtkWidget *menu_box);

	/*Permet de garder le menu affiché tant que l'utiisateur n'a pas appuyé sur un bouton du menu.*/
void waitInputMenuForPlayVN();

	/*Affiche le contenu d'un fichier dia( plus concrètement le décor, la photo de profil du personnage qui s'exprime en ce moment même, le nom du personnage et le texte du dialogue en lui-même).
	vn_folder_name = string ou char*, nom du dossier du Visual Novel.
	dia = variable de la structure "Dialogue", données d'un fichier dia 
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).
	endofVN = int marquant la fin du Visual Novel.
	text_speed = float, vitesse de défilement du texte du dialogue. P.S= Pour text_speed=1, un caractère est affiché toutes les 50ms, le calcul se fait comme suit: temps pour l'affichage d'un caractère= 50ms/valeur de text_speed.*/
void displayDia(char *vn_folder_name, Dialogue *dia, const int highlight_index, const int text_color, const int endofVN, const float text_speed);


	/*Permet à l'utilisateur de passer d'un dialogue à un autre via le pavé directionnel(précisément les touches "GAUCHE" et "DROITE", les touches "HAUT" et "BAS" serviront dans le cas où le dialogue affiché est trop grand pour la fenêtre ainsi l'utilisateur pourra voir le reste du texte qui se trouve en bas ou celui qui se trouve en haut).
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. 
	dia = variable d'une structure "Dialogue", données sur la partie du joueur.
	endofVN = int marquant la fin du Visual Novel.*/
void waitInputDia(int *highlight_index, int *keyboard_input, Dialogue *dia, const int endofVN);

	/*Permet à l'utilisateur d'ajouter une nouvelle image que ça soit un background ou une profile_picture.
	vn_folder_name = string ou char*, nom du Visual Novel.*/
void addImage(char *vn_folder_name);

	/*Permet à l'utilisateur d'éditer un dialogue et d'accesoirement de créer un nouveau dialogue.
	vn_folder_name = string ou char*, nom du Visual Novel.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
void editDia(char *vn_folder_name, const int length_currentRoute, char** currentRoute, const int i_currentBranch);

	/*Permet d'iniatiliser des champs du menu ingame, les champs "Newgame" pour une nouvelle partie, "Loadgame" pour charger une partie, "Return" pour retourner au menu principal.
	menu_ingame = Tableau de char* ou string, champs du menu ingame.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.
	vn_folder_name = string ou char*, nom du Visual Novel.*/
void intMenuInGame(char** menu_ingame, int *highlight_index, const char *vn_folder_name);

	/*Initialise la boîte de dialogue du menu loadgame.
	loadgame_menu = tableau de string ou char*, champs du menu loadgame.
	nb_champ_menu = nombre total de champ que le menu aura.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initLoadGameMenuDialog(char **loadgame_menu, const int nb_champ_menu, int *highlight_index);

	/*Permet d'iniatiliser l'interface qui va afficher les éléments des dialogues du visual novel.
	text_color = int, couleur du texte des différents dialogues.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel ou "Entrée"), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. */
void initVNView(const int text_color, int *keyboard_input);

	/*Permet d'iniatiliser des champs du menu savegame, les champs "Slot 1", "Slot 2", "Slot 3", "Slot 4", "Slot 5". 
	savegame_menu = Tableau de char* ou string, champs du menu savegame.
	nb_champ_menu = nombre total de champ que le menu aura.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void intSaveGameMenu(char** savegame_menu, const int nb_champ_menu, int *highlight_index);

	/*Affiche le menu des choix.
	choice_menu = tableau de char* ou string, champs du menu des choix.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.
	nb_choice = int, nombre de choix.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel ou "Entrée"), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur.*/
void displayChoiceMenu(char **choice_menu, int *highlight_index, const int nb_choice, int *keyboard_input);

//////////PRIVATE//////////

	/*Permet d'insérer dans le nouveau fichier "dia" des données par défaut(Pas de choix, le nom du fichier qui devrait potentiellement le suivre, un emplacement pour insérer le nom du décor, de la photo de profil et du nom du personnage et un emplacement pour insérer un dialogue).
	dia_file = variable FILE, fichier dia.
	currentRoute = tableau de char* ou string, Tableau ordonné de tous les noms des fichiers dia.*/
void setDefaultDataInFile(FILE *dia_file, char** currentRoute, const int length_currentRoute, const int i_currentBranch);

	/*Signale que l'utiisateur a appuyé sur le bouton "Newgame"*/
void newgameIsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur le bouton "Loadgame"*/
void loadgameIsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur le bouton "Return"*/
void returnIsSelectedForPlayVN(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 1 de sauvegarde*/
void slot1IsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 2 de sauvegarde*/
void slot2IsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 3 de sauvegarde*/
void slot3IsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 4 de sauvegarde*/
void slot4IsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur un bouton de slot 5 de sauvegarde*/
void slot5IsSelected(GtkWidget *widget, gpointer user_data);

	/*Signale que l'utiisateur a appuyé sur le bouton "Return" de la boîte de dialogue*/
void returnIsSelectedForDialog(GtkWidget *widget, gpointer user_data);

	/*Permet de signaler que l'utiisateur a appuyé sur le bouton "Edit"*/
void editButtonIsSelected(GtkWidget *widget, gpointer user_data);

	/*Permet de signaler que l'utiisateur a appuyé sur le bouton "Addimage"*/
void addImageButtonIsSelected(GtkWidget *widget, gpointer user_data);

	/*Permet de signaler que l'utiisateur a appuyé sur le bouton "Save"*/
void saveButtonIsSelected(GtkWidget *widget, gpointer user_data);

	/*Permet de signaler que l'utiisateur a appuyé sur la touche gauche de son pavé directionnel*/
void leftKeyIsSelected(GtkWidget *widget, gpointer user_data);

	/*Permet de signaler que l'utiisateur a appuyé sur la touche droite de son pavé directionnel*/
void rightKeyIsSelected(GtkWidget *widget, gpointer user_data);

	/*Permet de signaler que l'utiisateur a appuyé sur la touche "Q" de son clavier*/
void QKeyIsSelected(GtkWidget *widget, gpointer user_data);

	/*Permet de créer la liaison entre certaines touches du clavier et des fonctions*/
GtkAccelGroup *accel_group_new(gpointer user_data);

	/*Permet de créer une liaison entre une touche du clavier et une fonction*/
void accelerator_new(GtkAccelGroup *accel_group, const gchar *accelerator,  GCallback callback, gpointer user_data);

	/*Permet d'activer la fonction "editButtonIsSelected"*/
gboolean accelEdit(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

	/*Permet d'activer la fonction "addImageButtonIsSelected"*/
gboolean accelAddImage(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

	/*Permet d'activer la fonction "saveButtonIsSelected"*/
gboolean accelSave(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

	/*Permet d'activer la fonction "backKeyIsSelected"*/
gboolean accelBack(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

	/*Permet d'activer la fonction "nextKeyIsSelected"*/
gboolean accelNext(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

	/*Permet d'activer la fonction "QKeyIsSelected"*/
gboolean accelQuit(GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

	/*Permet de signaler que l'utiisateur a sélectionné un fichier*/
void fileIsSelected(GtkWidget *widget, gpointer user_data);

	/*Permet de signaler que l'utiisateur a choisi un type de fichier*/
void typeFileIsSeleted(GtkWidget *widget, gpointer user_data);

	/*Permet de signaler que l'utiisateur a fait un choix*/
void choiceIsMade(GtkWidget *widget, gpointer user_data);
#endif

