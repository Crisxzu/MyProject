#ifndef DEF_TOOLBAR
#define DEF_TOOLBAR

GtkToolbar *toolbar_new(gpointer user_data);

void toolbar_item_new(GtkToolbar *p_toolbar, const gchar *icon_name, const char *label, GCallback callback, gpointer user_data);

#endif

