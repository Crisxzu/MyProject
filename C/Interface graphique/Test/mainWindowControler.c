#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "mainWindowControler.h"
#include "mainWindowModel.h"
#include "mainWindowView.h"

void mainWindow()
{
	GtkWidget *main_window=NULL, *main_box=NULL;
	
	intMainWindow(mainWindow, main_box);
}

void initializeStructGlobal()
{
	intStructGlobal();
}

void exitProgram(GtkWidget *p_widget, gpointer user_data)
{
	g_free(__struct_global.format_text_color), __struct_global.format_text_color=NULL;
	gtk_main_quit();
	
	(void)p_widget;
	(void)user_data;
}
