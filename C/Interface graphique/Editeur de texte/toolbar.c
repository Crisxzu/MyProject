#include <stdlib.h>
#include <gtk/gtk.h>
#include "toolbar.h"
#include "callback.h"

GtkToolbar *toolbar_new(gpointer user_data)
{
	GtkWidget *p_toolbar=NULL;
	
	p_toolbar=gtk_toolbar_new();
	
	toolbar_item_new(GTK_TOOLBAR(p_toolbar), "document-new", "_New", G_CALLBACK(cb_new), user_data);
	toolbar_item_new(GTK_TOOLBAR(p_toolbar), "document-open", "_Open", G_CALLBACK(cb_open), user_data);
	toolbar_item_new(GTK_TOOLBAR(p_toolbar), "document-save", "_Save", G_CALLBACK(cb_save), user_data);
	toolbar_item_new(GTK_TOOLBAR(p_toolbar), "document-save-as", "Save_As", G_CALLBACK(cb_saveas), user_data);
	toolbar_item_new(GTK_TOOLBAR(p_toolbar), "edit-delete", "_Delete", G_CALLBACK(cb_close), user_data);
	toolbar_item_new(GTK_TOOLBAR(p_toolbar), "help-about", "_About", G_CALLBACK(cb_about), user_data);
	toolbar_item_new(GTK_TOOLBAR(p_toolbar), "application-exit", "_Quit", G_CALLBACK(cb_quit), user_data);
	
	gtk_toolbar_set_style(GTK_TOOLBAR(p_toolbar), GTK_TOOLBAR_ICONS);
	return GTK_TOOLBAR(p_toolbar);
}

void toolbar_item_new(GtkToolbar *p_toolbar, const gchar *icon_name, const char *label, GCallback callback, gpointer user_data)
{
	GtkToolItem *p_tool_item=NULL;
	GtkWidget *icon_image=NULL;
	
	icon_image=gtk_image_new_from_icon_name(icon_name, GTK_ICON_SIZE_BUTTON);
	p_tool_item=gtk_tool_button_new(icon_image, label);
	g_signal_connect(G_OBJECT(p_tool_item), "clicked", callback, user_data);
	gtk_toolbar_insert(p_toolbar, p_tool_item, -1);
}
