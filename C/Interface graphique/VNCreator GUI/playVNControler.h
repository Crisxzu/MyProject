#ifndef DEF_PLAYVNCONTROLER
#define DEF_PLAYVNCONTROLER

#include "struct.h"
#define ENTER 10
#define NB_CHAMP_MENU_INGAME 3
#define NB_NEXT_PREV_DIA 2
#define NB_CHAMP_SAVEGAME_MENU 6
#define NBMAX_CHOICE 5
#define NBMAX_DIA 9999
#define NBMAX_ACTIONS 500
#define KEY_D 100
#define KEY_Q 113
#define KEY_B  98
#define KEY_P 112
#define KEY_S 115

//////////PUBLIC//////////

	/*Permet de jouer le Visual Novel, celui choisi par l'utilisateur en affichant un menu qui va lui permettre de choisir entre créer une nouvelle partie ou en charger une ou encore de revenir au menu principal. L'utiisateur aura aussi la possibilité au cours de sa partie d'ajouter des dialogues et de les modifier, de créer un nouveau background ou un nouvelle photo de profil pour un personnage et de faire des choix s'il y en a.
	s = variable de la structure "Settings" contenant les différentes données des paramètres ainsi que le nom du Visual Novel à jouer*/
void playVN(Settings *s);


#endif
