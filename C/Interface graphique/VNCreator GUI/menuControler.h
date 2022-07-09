#ifndef DEF_MENUCONTROLER
#define DEF_MENUCONTROLER

#include "struct.h"
#define NB_CHAMP_MENU 3
#define NBMAX_VN (100+3)

//////////PUBLIC//////////

  /*Lancement du programme en affichant le menu principal, puis elle laisse le choix à l'utilisateur de naviguer entre les différents champs(Play, Options, Quit) grâce au pavé directionnel ou sa souris et choisir d'accéder au champ qu'il veut en faisant "Entrée" ou en cliquant dessus. 
   s = variable de la structure "Settings", données des paramètres.*/
void launchMenu(Settings *s);

	/*permet d'accéder à la fonction intSettings.
	s = variable de la structure "Settings" qui va contenir les données des paramètres et qui vont être envoyés à intSettings.*/    
void initializeSettings(Settings *s);

	/*Permet d'accéder à la fonction initView, initStructGlobal et initMainWindow*/
void initializeView(int argc, char** argv);

	/*Permet de quitter le programme.*/
void exitProgram(GtkWidget *widget, gpointer user_data);

#endif

