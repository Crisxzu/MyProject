#include <stdlib.h>
#include <gtk/gtk.h>
#include "hotkey.h"
#include "callback.h"
#include "document.h"


GtkAccelGroup *accel_group_new(gpointer user_data)
{
	GtkAccelGroup *p_accel_group=NULL;
	
	p_accel_group=gtk_accel_group_new();
	
	accelerator_new(p_accel_group, "<Control>N", ACCEL_PATH_NEW, G_CALLBACK(accel_new), user_data);
	accelerator_new(p_accel_group, "<Control>O", ACCEL_PATH_OPEN, G_CALLBACK(accel_open), user_data);
	accelerator_new(p_accel_group, "<Control>S", ACCEL_PATH_SAVE, G_CALLBACK(accel_save), user_data);
	accelerator_new(p_accel_group, "<Control><Shift>S", ACCEL_PATH_SAVEAS, G_CALLBACK(accel_saveas), user_data);
	accelerator_new(p_accel_group, "<Control>W", ACCEL_PATH_CLOSE, G_CALLBACK(accel_close), user_data);
	accelerator_new(p_accel_group, "<Control>Q", ACCEL_PATH_QUIT, G_CALLBACK(accel_quit), user_data);
	accelerator_new(p_accel_group, "<Control>A", ACCEL_PATH_ABOUT, G_CALLBACK(accel_about), user_data);
	
	return p_accel_group;
}

void accelerator_new(GtkAccelGroup *p_accel_group, const gchar *accelerator, const gchar *accel_path,  GCallback callback, gpointer user_data)
{
	guint key;
	GdkModifierType mods;
	GClosure *closure=NULL;
	
	gtk_accelerator_parse(accelerator, &key, &mods);
	closure=g_cclosure_new(callback, user_data, NULL);
	gtk_accel_group_connect(p_accel_group, key, mods, GTK_ACCEL_VISIBLE, closure);
	gtk_accel_map_add_entry(accel_path, key, mods);
}

gboolean accel_new(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	cb_new(NULL, user_data);
	
	(void)p_accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

gboolean accel_open(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	cb_open(NULL, user_data);
	
	(void)p_accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

gboolean accel_save(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	cb_save(NULL, user_data);
	
	(void)p_accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

gboolean accel_saveas(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	cb_saveas(NULL, user_data);
	
	(void)p_accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

gboolean accel_close(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	cb_close(NULL, user_data);
	
	(void)p_accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

gboolean accel_quit(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	cb_quit(NULL, user_data);
	
	(void)p_accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}

gboolean accel_about(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
	cb_about(NULL, user_data);
	
	(void)p_accel_group;
	(void)acceleratable;
	(void)keyval;
	(void)modifier;
	return TRUE;
}
