#ifndef DEF_STRUCT
#define DEF_STRUCT

#include <gtk/gtk.h>

typedef struct
{
	GtkBox *main_menu_box;
	GtkBox *settings_menu_box;
	GtkBox *run_menu_box;
	
}struct_global;

extern struct_global __struct_global;

#endif

