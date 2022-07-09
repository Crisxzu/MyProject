#include <stdlib.h>
#include <gtk/gtk.h>
#include "menu.h"
#include "callback.h"
#include "hotkey.h"


GtkMenuBar *menu_new(gpointer user_data)
{
	GtkWidget *p_menu_bar=NULL, *p_menu=NULL, *p_menu_item=NULL;
	
	p_menu_bar=gtk_menu_bar_new();
	p_menu=gtk_menu_new();
	
	p_menu_item=gtk_menu_item_new_with_mnemonic("_File");
	
	menu_item_new(GTK_MENU(p_menu), "_New", ACCEL_PATH_NEW, G_CALLBACK(cb_new), user_data);
	menu_item_new(GTK_MENU(p_menu), "_Open", ACCEL_PATH_OPEN, G_CALLBACK(cb_open), user_data);
	menu_item_new(GTK_MENU(p_menu), "_Save", ACCEL_PATH_SAVE, G_CALLBACK(cb_save), user_data);
	menu_item_new(GTK_MENU(p_menu), "Save _as", ACCEL_PATH_SAVEAS, G_CALLBACK(cb_saveas), user_data);
	menu_item_new(GTK_MENU(p_menu), "_Close", ACCEL_PATH_CLOSE, G_CALLBACK(cb_close), user_data);
	menu_item_new(GTK_MENU(p_menu), "_Quit", ACCEL_PATH_QUIT, G_CALLBACK(cb_quit), user_data);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(p_menu_item), p_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(p_menu_bar), p_menu_item);
	
	p_menu_item=gtk_menu_item_new_with_mnemonic("_About");
	gtk_menu_shell_append(GTK_MENU_SHELL(p_menu_bar), p_menu_item);
	g_signal_connect(G_OBJECT(p_menu_item), "activate", G_CALLBACK(cb_about), user_data);
	gtk_menu_item_set_accel_path(GTK_MENU_ITEM(p_menu_item), ACCEL_PATH_ABOUT);
	
	return GTK_MENU_BAR(p_menu_bar);
}

void menu_item_new(GtkMenu *p_menu, const gchar *title, const gchar *accel_path, GCallback callback, gpointer user_data)
{
	GtkWidget *p_menu_item=NULL;
	
	p_menu_item=gtk_menu_item_new_with_mnemonic(title);
	gtk_menu_shell_append(GTK_MENU_SHELL(p_menu), p_menu_item);
	g_signal_connect(G_OBJECT(p_menu_item), "activate", callback, user_data);
	gtk_menu_item_set_accel_path(GTK_MENU_ITEM(p_menu_item), accel_path);
}
