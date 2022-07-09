#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "menuControler.h"
#include "playVNControler.h"
#include "struct.h"

int main ()
{
	Settings s;
	
	initializeSettings(&s);
	while (TRUE)//Pour quitter le programme, il faut choisir "Quit" par le menu principal
	{
		launchMenu(&s);
		playVN(&s);
	}
	return 0;
}
