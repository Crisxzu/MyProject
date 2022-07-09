#ifndef DEF_MENU
#define DEF_MENU

GtkMenuBar *menu_new(gpointer user_data);
void menu_item_new(GtkMenu *p_menu, const gchar *title, const gchar *accel_path, GCallback callback, gpointer user_data);

#endif

