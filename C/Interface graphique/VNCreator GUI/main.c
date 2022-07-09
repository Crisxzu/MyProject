#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "menuControler.h"
#include "playVNControler.h"
#include "struct.h"

struct_global __struct_global={FALSE, FALSE, NULL, FALSE, FALSE, FALSE, FALSE, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

int main (int argc, char** argv)
{
	Settings s;
	
	initializeView(argc, argv);
	initializeSettings(&s);
	
	//Permet de garder l'utilisateur dans une boucle tant qu'il n'a pas quitté le programme
	while (TRUE)
	{
		launchMenu(&s);
		playVN(&s);
	}
	return 0;
}
