#ifndef DEF_MENUVIEW
#define DEF_MENUVIEW

#define ENTER 10

//////////PUBLIC//////////

	/*Affiche les différents champs du menu qui est entré en paramètres.
	highlight_index = int, index du champ qui est actuellement selectionné par l'utilisateur, celui-ci apparaitra en vert par rapport aux autres champs.
	Menu = tableau(de string ou char*), champs du menu.
	text_color = int, couleur choisie dans les paramètres pour les différents champs(hormis celui qui se retrouve en highlight qui sera affiché en vert).
	nb_champ_menu = int, nombre total de champs du menu.*/		
void displayMenu(char** Menu, const int highlight_index, const int text_color, const int nb_champ_menu);

	/*Permet à l'utilisateur de se déplacer dans le menu via le pavé directionnel(précisément les touches "HAUT" et "BAS") et de choisir d'accéder à un champ du Menu en faisant "Entrée".
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel ou "Entrée"), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. 
	nb_champ_menu = int, nombre total de champs du menu.*/
void waitInputMenu(int *highlight_index, int *keyboard_input, const int nb_champ_menu);

	/*Permet à l'utilisateur d'entrer le nom du nouveau Visual Novel qu'il souhaite créer.
	text_color = int, couleur choisie qui va permettre à la fonction d'afficher le menu avec celle-ci.
	new_vn_name_directory = char* ou string, emplacement du Visual Novel que l'utilisateur souhaite créer.*/
void enterNewVNname(const int text_color, char* newVNName);

	/*Permet à l'utilisateur de se déplacer dans le menu et de modifier les différents paramètres via le pavé directionnel(précisément les touches "HAUT", "BAS", "GAUCHE" et "DROITE") et de choisir de retourner au menu principal en faisant "Entrée".
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.
	keyboard_input = int, touche qui sera appuyé par l'utilisateur(celles de son pavé directionnel ou "Entrée"), la valeur de keyboard_input sera modifiée en fonction des différents déplacements de l'utilisateur. 
	text_speed = int, vitesse de défilement du texte des différents dialogues des Visual Novel, sa valeur sera modifié en fonction des mouvements du pavé directionnel("GAUCHE" et "DROITE").
	text_color = int, couleur du texte des différents menus qui seront affichés*, sa valeur sera modifié en fonction des mouvements du pavé directionnel("GAUCHE" et "DROITE").
	nb_champ_menu = int, nombre total de champs du menu.*/
void waitInputSettingsMenu(int *highlight_index, int *keyboard_input, int *text_speed, int *text_color, const int nb_champ_menu);

#endif

