#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "mainWindowView.h"
#include "manWindowControler.h"


void intStructGlobal()
{
	__struct_global.main_box=NULL;
	__struct_global.main_menu_box=NULL;
	__struct_global.settings_menu_box=NULL;
	__struct_global.format_text_color=NULL;
	__struct_global.run_menu_box=NULL;
}

void intMainWindow(GtkWidget *main_window, GtkWidget *main_box)
{
	main_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 250, 100);
	gtk_window_set_title(GTK_WINDOW(main_window), "VNCreator");
	
	main_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(main_window), main_box);
	__struct_global.main_box=main_box;
	
	g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(exitProgram), NULL);
}
