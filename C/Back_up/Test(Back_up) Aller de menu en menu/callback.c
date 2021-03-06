#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "struct.h"


void cb_quit(GtkWidget *p_widget, gpointer user_data)
{
	gtk_main_quit();
	
	(void)p_widget;
	(void)user_data;
}

void cb_run(GtkWidget *p_widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(__struct_global.main_menu_box));
	gtk_widget_show(GTK_WIDGET(__struct_global.run_menu_box));
	
	(void)p_widget;
	(void)user_data;
}

void cb_settings(GtkWidget *p_widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(__struct_global.main_menu_box));
	gtk_widget_show(GTK_WIDGET(__struct_global.settings_menu_box));
	
	(void)p_widget;
	(void)user_data;
}

void cb_return(GtkWidget *p_widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(user_data));
	gtk_widget_show(GTK_WIDGET(__struct_global.main_menu_box));
	
	(void)p_widget;
}
