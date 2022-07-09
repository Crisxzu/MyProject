#ifndef DEF_STRUCT
#define DEF_STRUCT

#include <gtk/gtk.h>

#define TEXT_SPEED_MAX 10
#define TEXT_SPEED_MIN 1
#define TEXT_COLOR_MAX 5
#define TEXT_COLOR_MIN 0

typedef struct
{
	/*Menu Principal*/
	GtkBox *main_menu_box;
	
	/*Menu des paramètres*/
	GtkBox *settings_menu_box;
	int text_speed;
	int text_color;
	gchar *format_text_color;
	
	/*Menu de lancement*/
	GtkBox *run_menu_box;
	
}struct_global;

extern struct_global __struct_global;

#endif

