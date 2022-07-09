#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void cb_quit(GtkWidget *widget, gpointer user_data)
{
	gtk_main_quit();
	
	(void)widget;
	(void)user_data;
}

int main (int argc, char **argv)
{
	GtkBuilder *builder=NULL;
	
	gtk_init(&argc, &argv);
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "menu.glade", NULL);
	
	gtk_builder_connect_signals(builder, NULL);
	
	gtk_main();
	return 0;
}
