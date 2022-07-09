#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "callback.h"

void cb_quit(GtkWidget *widget, gpointer user_data)
{
	gtk_main_quit();
	
	(void)widget;
	(void)user_data;
}
