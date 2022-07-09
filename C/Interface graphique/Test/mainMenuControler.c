#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "mainMenuControler.h"
#include "mainMenuModel.h"
#include "mainMenuView.h"

void mainMenu()
{
	GtkWidget *main_menu_label=NULL, *main_menu_box=NULL, *main_menu_button_box=NULL, *main_menu_run_button=NULL, *main_menu_settings_button=NULL, *main_menu_quit_button=NULL;
	
	intMainMenu(main_menu_label, main_menu_box, main_menu_button_box, main_menu_run_button, main_menu_settings_button, main_menu_quit_button);

	
}
