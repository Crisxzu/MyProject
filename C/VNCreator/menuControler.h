#ifndef DEF_MENUCONTROLER
#define DEF_MENUCONTROLER

#include "struct.h"
#define NB_CHAMP_MENU 3
#define NBMAX_VN (100+2)

//////////PUBLIC//////////

   /*Lancement du programme en affichant le menu principal, puis elle laisse le choix à l'utilisateur de naviguer entre les différents champs(Play, Options, Quit) grâce au pavé directionnel et choisir d'accéder au champ qu'il veut en faisant "Entrée". 
   s = variable de la structure "Settings", données des paramètres.*/
void launchMenu(Settings *s);

	/*permet d'accéder à la fonction intSettings.
	s = variable de la structure "Settings" qui va contenir les données des paramètres et qui vont être envoyés à intSettings.*/    
void initializeSettings(Settings *s);


#endif

